#pragma once
#include <memory>
#include <string>
#include <map>
#include "Delivery.h"

class DeliveryProxy: public Delivery {
    std::shared_ptr<Delivery> realDelivery_;
    std::map<int, double> costDev_;
public:
    explicit DeliveryProxy(std::shared_ptr<Delivery> realDelivery);
    double getCost(const Order& order) override;
    std::string getEstimatedTime() override;
    bool isAvailable(const Order& order) override;
    std::string getName() override;
};
