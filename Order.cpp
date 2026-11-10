#include "Order.h"
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <ctime>

int Order::nextId_ = 1;
Order::Order(const std::string& customer)
    :id_(nextId_++), customer_(customer), status_(OrderStatus::Pending), discountSum_(0), cashback_(0),freeDelivery_(false) {
    if (customer.empty()) {
        throw std::invalid_argument("Customer must not be empty");
    }
}

Order::Order(const Order& other): id_(other.id_), customer_(other.customer_), status_(other.status_),
    delivery_(other.delivery_), discounts_(other.discounts_), discountSum_(other.discountSum_),cashback_(other.cashback_),
    freeDelivery_(other.freeDelivery_), gifts_(other.gifts_) {
    for (const auto& item : other.items_) {
        if (item) {
            items_.push_back(item->clone());
        }
    }
}

Order& Order::operator=(const Order& other) {
    if (this == &other) {
        return *this;
    }
    id_ = other.id_;
    customer_ = other.customer_;
    status_ = other.status_;
    delivery_ = other.delivery_;
    discounts_ = other.discounts_;
    discountSum_ = other.discountSum_;
    cashback_ = other.cashback_;
    freeDelivery_ = other.freeDelivery_;
    gifts_ = other.gifts_;
    items_.clear();
    for (const auto& item : other.items_) {
        if (item) {
            items_.push_back(item->clone());
        }
    }
    return *this;
}

void Order::checkTable() const {
    if (status_ != OrderStatus::Pending) {
        throw std::logic_error("Order status is not pending");
    }
}

void Order::checkItemsEditable() const {
    checkTable();
    if (delivery_ || !discounts_.empty()) {
        throw std::logic_error("Items can't be changed after delivery or discount is applied");
    }
}

void Order::addItem(std::shared_ptr<Product> item) {
    checkItemsEditable();
    if (!item) {
        throw std::invalid_argument("Item mustn't be null");
    }
    if (item->getQuantity().getValue() <= 0) {
        throw std::invalid_argument("Item quantity must be greater than zero");
    }
    for (auto& existing : items_) {
        if (existing->getId() == item->getId()) {
            existing->changeQuantity(item->getQuantity().getValue());
            return;
        }
    }
    items_.push_back(item);
}

bool Order::removeItem(int productId) {
    checkItemsEditable();
    auto it = std::find_if(items_.begin(), items_.end(),
        [productId](const std::shared_ptr<Product>& item) {
            return item->getId() == productId;});
    if (it != items_.end()) {
        items_.erase(it);
        return true;
    }
    return false;
}

double Order::getTotalWeight() const {
    double total = 0;
    for (const auto& item : items_) {
        total += item->getWeight().getValue() * item->getQuantity().getValue();
    }
    return total;
}

double Order::getItemsPrice() const {
    double total = 0;
    for (const auto& item : items_) {
        total += item->getPrice().getValue() * item->getQuantity().getValue();
    }
    return total;
}
double Order::getDeliverycost() const {
    if (!delivery_ || freeDelivery_) {
        return 0;
    }
    return delivery_->getCost(*this);
}

double Order::getTotalPrice() const {
    double total = getItemsPrice() - discountSum_ + getDeliverycost();
    if (total < 0) {
        total = 0;
    }
    return total;
}

static bool canChangeStatus(OrderStatus oldStatus, OrderStatus newStatus) {
    if (oldStatus == OrderStatus::Pending) {
        return newStatus == OrderStatus::Paid || newStatus == OrderStatus::Cancelled;
    }
    if (oldStatus == OrderStatus::Paid) {
        return newStatus == OrderStatus::Shipped || newStatus == OrderStatus::Cancelled;
    }
    if (oldStatus == OrderStatus::Shipped) {
        return newStatus == OrderStatus::Delivered;
    }
    return false;
}

void Order::setStatus(OrderStatus newStatus) {
    if (!canChangeStatus(status_, newStatus)) {
        throw std::invalid_argument("Invalid status change");
    }
    OrderEvent event {id_, status_, newStatus, std::time(nullptr)};
    status_ = newStatus;
    notify(event);
}

bool Order::setDelivery(std::shared_ptr<Delivery> delivery) {
    checkTable();
    if (!delivery || !delivery->isAvailable(*this)) {
        return false;
    }
    delivery_ = std::move(delivery);
    return true;
}

void Order::applyDiscount(const Discount& discount) {
    checkTable();
    discount.apply(*this);
    discounts_.push_back(discount.getName());
}
