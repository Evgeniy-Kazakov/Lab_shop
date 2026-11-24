#pragma once
#include <map>
#include <memory>
#include <string>
#include "Delivery.h"
#include "Order.h"

class DeliveryService {
    std::shared_ptr<Delivery> couriers_;
    std::shared_ptr<Delivery> pickupPoints_;
    std::shared_ptr<Delivery> postOffices_;
public:
    DeliveryService();

    std::shared_ptr<Delivery> getDelivery(const std::string& type) const;
    bool isAvailable(const Order& order) const;
    double calculateCost(const Order& order) const;
    std::string scheduleDelivery(const Order& order);
    std::string getDeliveryTypesText() const;
};
