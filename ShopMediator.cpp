#include "ShopMediator.h"
#include <map>
#include <stdexcept>
#include "Operators.h"
#include "StringUtils.h"

ShopMediator::ShopMediator(WarehouseManager& warehouses, OrderManager& orderManager,
                           PaymentSystem& paymentSystem, DeliveryService& deliveryService)
    : warehouses_(warehouses), orderManager_(orderManager), paymentSystem_(paymentSystem),
      deliveryService_(deliveryService) {}

std::shared_ptr<Order> ShopMediator::getOrder(int orderId) const {
    std::shared_ptr<Order> order = orderManager_.findOrder(orderId);
    if (!order) {
        throw std::invalid_argument("Заказ №" + std::to_string(orderId) + " не найден");
    }
    return order;
}

void ShopMediator::releaseItems(const std::vector<std::shared_ptr<Product>>& items) {
    for (const auto& item : items) {
        if (warehouses_.findProduct(item->getId())) {
            warehouses_.changeQuantity(item->getId(), item->getQuantity().getValue());
        }
    }
}

std::shared_ptr<Order> ShopMediator::createOrder(const std::string& customer, const std::vector<OrderItemRequest>& requests,
    const std::string& deliveryType, const std::shared_ptr<Discount>& promotion) {
    if (requests.empty()) {
        throw std::invalid_argument("Заказ не может быть пустым");
    }
    std::shared_ptr<Delivery> delivery = deliveryService_.getDelivery(deliveryType);


    std::map<int, int> wanted;
    for (const OrderItemRequest& request : requests) {
        if (request.quantity <= 0) {
            throw std::invalid_argument("Количество товара в заказе должно быть больше нуля");
        }
        wanted[request.productId] += request.quantity;
    }
    for (const auto& pair : wanted) {
        Product* product = warehouses_.findProduct(pair.first);
        if (!product) {
            throw std::invalid_argument("Товар №" + std::to_string(pair.first) + " не найден");
        }
        if (product->getQuantity().getValue() < pair.second) {
            throw std::runtime_error("Товара №" + std::to_string(pair.first) + " не хватает на складе: нужно "
                + std::to_string(pair.second) + ", есть " + std::to_string(product->getQuantity().getValue()));
        }
    }


    std::vector<std::shared_ptr<Product>> items;
    for (const auto& pair : wanted) {
        Product* product = warehouses_.findProduct(pair.first);
        std::shared_ptr<Product> item = product->clone();
        item->setWarehouse(nullptr);
        item->setQuantity(pair.second);
        warehouses_.changeQuantity(pair.first, -pair.second);
        items.push_back(item);
    }


    std::shared_ptr<Order> order;
    try {
        order = orderManager_.createOrder(customer, items);
    }
    catch (...) {
        releaseItems(items);
        throw;
    }


    if (!order->setDelivery(delivery)) {
        orderManager_.updateStatus(order->getId(), OrderStatus::Cancelled);
        releaseItems(items);
        throw std::runtime_error("Заказ №" + std::to_string(order->getId())
            + " отменён: доставка '" + deliveryType + "' недоступна для этого заказа");
    }

    if (promotion) {
        *order + *promotion;
    }


    if (order->getItemsPrice() >= freeDeliveryLimit_) {
        FreeDeliveryDiscount freeDelivery;
        *order + freeDelivery;
    }
    return order;
}

void ShopMediator::confirmPayment(int orderId) {
    std::shared_ptr<Order> order = getOrder(orderId);
    if (order->getStatus() != OrderStatus::Pending) {
        throw std::logic_error("Оплатить можно только заказ в статусе pending, а сейчас: "
            + orderStatusToString(order->getStatus()));
    }
    paymentSystem_.processPayment(order->getCustomer(), order->getTotalPrice());
    orderManager_.updateStatus(orderId, OrderStatus::Paid);
}

std::string ShopMediator::shipOrder(int orderId) {
    std::shared_ptr<Order> order = getOrder(orderId);
    if (order->getStatus() != OrderStatus::Paid) {
        throw std::logic_error("Отправить можно только оплаченный заказ, а сейчас: "
            + orderStatusToString(order->getStatus()));
    }
    if (!deliveryService_.isAvailable(*order)) {
        throw std::runtime_error("Доставка для заказа №" + std::to_string(orderId) + " недоступна");
    }
    std::string info = deliveryService_.scheduleDelivery(*order);
    orderManager_.updateStatus(orderId, OrderStatus::Shipped);
    return info;
}

void ShopMediator::cancelOrder(int orderId) {
    std::shared_ptr<Order> order = getOrder(orderId);
    OrderStatus status = order->getStatus();
    if (status != OrderStatus::Pending && status != OrderStatus::Paid) {
        throw std::logic_error("Нельзя отменить заказ в статусе " + orderStatusToString(status));
    }
    if (status == OrderStatus::Paid) {
        paymentSystem_.refund(order->getCustomer(), order->getTotalPrice());
    }
    orderManager_.updateStatus(orderId, OrderStatus::Cancelled);
    releaseItems(order->getItems());
}

std::string ShopMediator::getStatistics() const {
    std::string text;
    text += "Всего заказов: " + std::to_string(orderManager_.getOrders().size()) + "\n";
    text += "Активных заказов: " + std::to_string(orderManager_.getActiveOrders()) + "\n";
    text += "Оборот: " + formatMoney(orderManager_.getTurnover()) + "\n";
    text += "Клиентов с оплаченными заказами: " + std::to_string(orderManager_.getCustomersCount()) + "\n";
    text += "Загруженность складов:\n" + warehouses_.getLoadText();
    return text;
}

void ShopMediator::onProductRemoved(int productId) {
    for (const auto& order : orderManager_.getOrders()) {
        OrderStatus status = order->getStatus();
        if (status == OrderStatus::Delivered || status == OrderStatus::Cancelled) {
            continue;
        }
        for (const auto& item : order->getItems()) {
            if (item->getId() == productId) {
                throw std::logic_error("Товар №" + std::to_string(productId)
                    + " нельзя удалить: он зарезервирован в заказе №" + std::to_string(order->getId()));
            }
        }
    }
}

std::string ShopMediator::getPromotionsText() const {
    return "на выбор при создании заказа: percent, cashback, freedelivery, gift; "
           "автоматически: бесплатная доставка при сумме заказа от " + std::to_string(freeDeliveryLimit_);
}
