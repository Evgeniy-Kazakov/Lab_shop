#include "Discount.h"
#include "Order.h"
#include <string>
#include <stdexcept>
#include <utility>
#include <sstream>

static std::string formatPercent(double percent) {
    std::ostringstream stream;
    stream << percent;
    return stream.str();
}

PercentDiscount::PercentDiscount(double percent):percent_(percent) {
    if (percent <= 0 || percent > 100) {
        throw std::invalid_argument("percent must be between 0 and 100");
    }
}
void PercentDiscount::apply(Order& order) const {
    double amount = order.getItemsPrice() * percent_/100;
    order.addDiscountSum(amount);
}
std::string PercentDiscount::getName() const {
    return "Скидка " + formatPercent(percent_) + "%";
}

CashbackDiscount::CashbackDiscount(double percent): percent_(percent) {
    if (percent <= 0 || percent > 100) {
        throw std::invalid_argument("percent must be between 0 and 100");
    }
}
void CashbackDiscount::apply(Order& order) const {
    double amount = (order.getItemsPrice() - order.getDiscountSum()) * percent_/100;
    order.addCashback(amount);
}
std::string CashbackDiscount::getName() const {
    return "Cashback " + formatPercent(percent_) + "%";
}

void FreeDeliveryDiscount::apply(Order& order) const {
    order.setFreeDelivery(true);
}
std::string FreeDeliveryDiscount::getName() const {
    return "Доставка бесплатная";
}

GiftDiscount::GiftDiscount(std::string gift) : gift_(std::move(gift)) {}
void GiftDiscount::apply(Order& order) const {
    order.addGift(gift_);
}
std::string GiftDiscount::getName() const {
    return "Подарок: " + gift_;
}
