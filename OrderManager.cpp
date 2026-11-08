#include "OrderManager.h"
#include <stdexcept>

OrderManager::OrderManager(int maxOrders): turnover_(0), maxOrders_(maxOrders), activeOrders_(0) {
    if (maxOrders_ <= 0) {
        throw std::invalid_argument("maxOrders must be greater than 0");
    }
}

OrderManager::~OrderManager() {
    for (auto& order : orders_) {
        order->unsubscribe(this);
    }
}

std::shared_ptr<Order> OrderManager::createOrder(const std::string& customer, const std::vector<std::shared_ptr<Product>>& items) {
    if (items.empty()) {
        throw std::invalid_argument("Order cannot be empty");
    }
    if (countOrders(customer) >= maxOrders_) {
        throw std::runtime_error("Too many orders from this customer");
    }
    auto order = std::make_shared<Order>(customer);
    for (const auto& item : items) {
        order->addItem(item);
    }
    order->subscribe(this);
    orders_.push_back(order);
    activeOrders_++;
    return order;
}

bool OrderManager::updateStatus(int orderId, OrderStatus newStatus) {
    auto order = findOrder(orderId);
    if (!order) {
        return false;
    }
    order->setStatus(newStatus);
    return true;
}

std::shared_ptr<Order> OrderManager::findOrder(int orderId) const {
    for (const auto& order : orders_) {
        if (order->getId() == orderId) {
            return order;
        }
    }
    return nullptr;
}

int OrderManager::countOrders(const std::string& customer) const {
    int count = 0;
    for (const auto& order : orders_) {
        if (order->getCustomer() == customer) {
            OrderStatus status = order->getStatus();
            if (status != OrderStatus::Delivered && status != OrderStatus::Cancelled) {
                count++;
            }
        }
    }
    return count;
}

bool OrderManager::hasPaidOrders(const std::string& customer) const {
    for (const auto& order : orders_) {
        if (order->getCustomer() == customer) {
            OrderStatus status = order->getStatus();
            if (status == OrderStatus::Paid || status == OrderStatus::Shipped || status == OrderStatus::Delivered) {
                return true;
            }
        }
    }
    return false;
}

void OrderManager::onOrderEvent(const OrderEvent& event) {
    auto order = findOrder(event.orderId);
    if (!order) {
        return;
    }
     if (event.newStatus == OrderStatus::Paid) {
         turnover_ += order->getTotalPrice();
         customers_.insert(order->getCustomer());
     }
    else if (event.newStatus == OrderStatus::Cancelled) {
        if (event.oldStatus == OrderStatus::Paid) {
            turnover_ -= order->getTotalPrice();
        }
        activeOrders_--;
        if (event.oldStatus == OrderStatus::Paid && !hasPaidOrders(order->getCustomer())) {
            customers_.erase(order->getCustomer());
        }
    }
    else if (event.newStatus == OrderStatus::Delivered) {
        activeOrders_--;
    }
}
