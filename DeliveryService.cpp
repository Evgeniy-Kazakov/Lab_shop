#include "DeliveryService.h"
#include <stdexcept>
#include "DeliveryProxy.h"
#include "StringUtils.h"

DeliveryService::DeliveryService() {
    couriers_ = std::make_shared<DeliveryProxy>(std::make_shared<CourierDelivery>());
    pickupPoints_ = std::make_shared<DeliveryProxy>(std::make_shared<PickupDelivery>());
    postOffices_ = std::make_shared<DeliveryProxy>(std::make_shared<PostDelivery>());
}

std::shared_ptr<Delivery> DeliveryService::getDelivery(const std::string& type) const {
    std::string lowerType = toLower(type);
    if (lowerType == "courier") {
        return couriers_;
    }
    if (lowerType == "pickup") {
        return pickupPoints_;
    }
    if (lowerType == "post") {
        return postOffices_;
    }
    throw std::invalid_argument("Неизвестный способ доставки '" + type + "'. Доступные: courier, pickup, post");
}

bool DeliveryService::isAvailable(const Order& order) const {
    if (!order.getDelivery()) {
        return false;
    }
    return order.getDelivery()->isAvailable(order);
}

double DeliveryService::calculateCost(const Order& order) const {
    if (!order.getDelivery()) {
        return 0;
    }
    return order.getDelivery()->getCost(order);
}

std::string DeliveryService::scheduleDelivery(const Order& order) {
    if (!order.getDelivery()) {
        throw std::logic_error("Для заказа не выбран способ доставки");
    }
    std::string info = order.getDelivery()->getName() + ", срок: " + order.getDelivery()->getEstimatedTime();
    return info;
}

std::string DeliveryService::getDeliveryTypesText() const {
    return "courier (" + couriers_->getName() + "), pickup (" + pickupPoints_->getName()
        + "), post (" + postOffices_->getName() + ")";
}
