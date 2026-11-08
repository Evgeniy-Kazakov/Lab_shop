#include "Operators.h"

Order& operator+(Order& order, const Discount& discount) {
    order.applyDiscount(discount);
    return order;
}

bool operator<<(const std::shared_ptr<Delivery>& delivery, Order& order) {
    return order.setDelivery(delivery);
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Заказ № " << order.getId() <<" | клиент: " << order.getCustomer() << " | статус: " << orderStatusToString(order.getStatus()) << std::endl;
    for (const auto& item : order.getItems()) {
        os << "  - " << item->getName() << " | количество: " << item->getQuantity().getValue()
            << " | цена: " << item->getPrice().getValue() << std::endl;
    }
    os << "Сумма товаров: " << order.getItemsPrice() << std::endl;
    os << "Вес заказа: " << order.getTotalWeight() << " кг" << std::endl;
    if (order.getDiscountSum() > 0) {
        os << "Скидка: " << order.getDiscountSum() << std::endl;
    }
    if (order.getCashback() > 0) {
        os << "Cashback: " << order.getCashback() << std::endl;
    }
    for (const auto& gift : order.getGifts()) {
        os << "Подарок: " << gift << std::endl;
    }
    if (order.getDelivery()) {
        os << "Доставка: " << order.getDelivery()->getName() << ", стоимость " << order.getDeliverycost() << std::endl;
    }
    os << "Итого: " << order.getTotalPrice() << std::endl;
    return os;

}
