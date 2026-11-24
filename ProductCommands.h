#pragma once
#include <string>
#include "Command.h"

class AddProductCommand : public Command {
    std::string type_;
    std::string name_;
    int price_;
    int quantity_;
public:
    AddProductCommand(ShopFacade& facade, std::string type, std::string name, int price, int quantity);
    std::string execute() override;
};

class ChangePriceCommand : public Command {
    int productId_;
    int newPrice_;
public:
    ChangePriceCommand(ShopFacade& facade, int productId, int newPrice);
    std::string execute() override;
};

class ChangeQuantityCommand : public Command {
    int productId_;
    int delta_;
public:
    ChangeQuantityCommand(ShopFacade& facade, int productId, int delta);
    std::string execute() override;
};

class MoveProductCommand : public Command {
    int productId_;
    int newWarehouseId_;
public:
    MoveProductCommand(ShopFacade& facade, int productId, int newWarehouseId);
    std::string execute() override;
};

class RemoveProductCommand : public Command {
    int productId_;
public:
    RemoveProductCommand(ShopFacade& facade, int productId);
    std::string execute() override;
};
