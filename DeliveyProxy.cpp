#include "DeliveyProxy.h"
#include <stdexcept>
#include <utility>
#include "Order.h"

DeliveryProxy::DeliveryProxy(std::shared_ptr<Delivery> realDelivery): realDelivery_(std::move(realDelivery)) {
    if (!realDelivery_) {
        throw std::invalid_argument("null Delivery object");
    }
}

double DeliveryProxy::getCost(const Order& order) {
    auto it = costDev_.find(order.getId());
    if (it != costDev_.end()) {
        return it->second;
    }
    double cost = realDelivery_->getCost(order);
    costDev_[order.getId()] = cost;
    return cost;
}

std::string DeliveryProxy::getEstimatedTime() {
    return realDelivery_->getEstimatedTime();
}

bool DeliveryProxy::isAvailable(const Order& order) {
    if (order.getItems().empty()) {
        return false;
    }
    bool available = realDelivery_->isAvailable(order);
    return available;
}

std::string DeliveryProxy::getName() {
    return realDelivery_->getName();
}
