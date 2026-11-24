#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Command.h"
#include "Discount.h"
#include "StringUtils.h"

class CreateOrderCommand : public Command {
    std::string customer_;
    std::vector<OrderItemRequest> items_;
    std::string deliveryType_;
    std::shared_ptr<Discount> promotion_;
public:
    CreateOrderCommand(ShopFacade& facade, std::string customer, std::vector<OrderItemRequest> items,
        std::string deliveryType, std::shared_ptr<Discount> promotion);
    std::string execute() override;
};

class CancelOrderCommand : public Command {
    int orderId_;
public:
    CancelOrderCommand(ShopFacade& facade, int orderId);
    std::string execute() override;
};

class ConfirmPaymentCommand : public Command {
    int orderId_;
public:
    ConfirmPaymentCommand(ShopFacade& facade, int orderId);
    std::string execute() override;
};

class ShipOrderCommand : public Command {
    int orderId_;
public:
    ShipOrderCommand(ShopFacade& facade, int orderId);
    std::string execute() override;
};
