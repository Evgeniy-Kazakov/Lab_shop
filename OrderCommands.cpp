#include "OrderCommands.h"
#include <sstream>
#include <utility>
#include "Operators.h"
#include "ShopFacade.h"
#include "StringUtils.h"

CreateOrderCommand::CreateOrderCommand(ShopFacade& facade, std::string customer,
    std::vector<OrderItemRequest> items, std::string deliveryType, std::shared_ptr<Discount> promotion)
    : Command(facade), customer_(std::move(customer)), items_(std::move(items)), deliveryType_(std::move(deliveryType)), promotion_(std::move(promotion)) {}

std::string CreateOrderCommand::execute() {
    std::shared_ptr<Order> order = facade_.createOrder(customer_, items_, deliveryType_, promotion_);
    std::ostringstream text;
    text << "Заказ создан:\n" << *order;
    return trimEnd(text.str());
}

CancelOrderCommand::CancelOrderCommand(ShopFacade& facade, int orderId)
    : Command(facade), orderId_(orderId) {}

std::string CancelOrderCommand::execute() {
    facade_.cancelOrder(orderId_);
    return "Заказ №" + std::to_string(orderId_) + " отменён";
}

ConfirmPaymentCommand::ConfirmPaymentCommand(ShopFacade& facade, int orderId)
    : Command(facade), orderId_(orderId) {}

std::string ConfirmPaymentCommand::execute() {
    facade_.confirmPayment(orderId_);
    return "Заказ №" + std::to_string(orderId_) + " оплачен";
}

ShipOrderCommand::ShipOrderCommand(ShopFacade& facade, int orderId)
    : Command(facade), orderId_(orderId) {}

std::string ShipOrderCommand::execute() {
    std::string info = facade_.shipOrder(orderId_);
    return "Заказ №" + std::to_string(orderId_) + " отправлен. Доставка: " + info;
}
