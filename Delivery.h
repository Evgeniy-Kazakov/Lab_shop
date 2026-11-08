#pragma once
#include <string>

class Order;
class Delivery {
public:
    virtual ~Delivery() = default;
    virtual double getCost(const Order& order) = 0;
    virtual std::string getEstimatedTime() = 0;
    virtual bool isAvailable(const Order& order) = 0;
    virtual std::string getName() = 0;
};

class CourierDelivery : public Delivery {
public:
    double getCost(const Order& order) override;
    std::string getEstimatedTime() override;
    bool isAvailable(const Order& order) override;
    std::string getName() override;
};

class PickupDelivery : public Delivery {
public:
    double getCost(const Order& order) override;
    std::string getEstimatedTime() override;
    bool isAvailable(const Order& order) override;
    std::string getName() override;
};

class PostDelivery : public Delivery {
public:
    double getCost(const Order& order) override;
    std::string getEstimatedTime() override;
    bool isAvailable(const Order& order) override;
    std::string getName() override;
};
