#include "Delivery.h"
#include "Order.h"

double CourierDelivery::getCost(const Order &order) {
    return 500;
}
std::string CourierDelivery::getEstimatedTime() {
    return "1-2 дня";
}
bool CourierDelivery::isAvailable(const Order& order) {
    return order.getTotalWeight() <= 20;
}
std::string CourierDelivery::getName() {
    return "Курьер";
}

double PickupDelivery::getCost(const Order &order) {
    return 0;
}
std::string PickupDelivery::getEstimatedTime() {
    return "1-3 дня";
}
bool PickupDelivery::isAvailable(const Order& order) {
    return true;
}
std::string PickupDelivery::getName() {
    return "Самовывоз";
}

double PostDelivery::getCost(const Order &order) {
    return 200;
}
std::string PostDelivery::getEstimatedTime() {
    return "5-10 дней";
}
bool PostDelivery::isAvailable(const Order& order) {
    return order.getTotalWeight() <= 10;
}
std::string PostDelivery::getName() {
    return "Почта";
}
