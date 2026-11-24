#include "ProductCommands.h"
#include <utility>
#include "ShopFacade.h"

AddProductCommand::AddProductCommand(ShopFacade& facade, std::string type, std::string name, int price, int quantity)
    : Command(facade), type_(std::move(type)), name_(std::move(name)), price_(price), quantity_(quantity) {}

std::string AddProductCommand::execute() {
    int productId = facade_.addProduct(type_, name_, price_, quantity_);
    return "Товар добавлен: №" + std::to_string(productId) + " " + name_
        + ", цена " + std::to_string(price_) + ", количество " + std::to_string(quantity_);
}

ChangePriceCommand::ChangePriceCommand(ShopFacade& facade, int productId, int newPrice)
    : Command(facade), productId_(productId), newPrice_(newPrice) {}

std::string ChangePriceCommand::execute() {
    facade_.changePrice(productId_, newPrice_);
    return "Цена товара №" + std::to_string(productId_) + " изменена на " + std::to_string(newPrice_);
}

ChangeQuantityCommand::ChangeQuantityCommand(ShopFacade& facade, int productId, int delta)
    : Command(facade), productId_(productId), delta_(delta) {}

std::string ChangeQuantityCommand::execute() {
    facade_.changeQuantity(productId_, delta_);
    return "Остаток товара №" + std::to_string(productId_) + " изменён на " + std::to_string(delta_);
}

MoveProductCommand::MoveProductCommand(ShopFacade& facade, int productId, int newWarehouseId)
    : Command(facade), productId_(productId), newWarehouseId_(newWarehouseId) {}

std::string MoveProductCommand::execute() {
    facade_.moveProduct(productId_, newWarehouseId_);
    return "Товар №" + std::to_string(productId_) + " перемещён на склад №" + std::to_string(newWarehouseId_);
}

RemoveProductCommand::RemoveProductCommand(ShopFacade& facade, int productId)
    : Command(facade), productId_(productId) {}

std::string RemoveProductCommand::execute() {
    facade_.removeProduct(productId_);
    return "Товар №" + std::to_string(productId_) + " удалён со склада";
}
