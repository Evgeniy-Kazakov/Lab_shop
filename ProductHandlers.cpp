#include "ProductHandlers.h"
#include <stdexcept>
#include "ProductCommands.h"
#include "ShopFacade.h"
#include "StringUtils.h"

bool AddProductHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "add", "product")) {
        return false;
    }
    checkArgumentsCount(tokens, 6, "add product <type> <name> <price> <quantity>");
    std::string type = tokens[2];
    std::string name = tokens[3];
    int price = parseInt(tokens[4], "price");
    int quantity = parseInt(tokens[5], "quantity");
    facade_.executeCommand(std::make_unique<AddProductCommand>(facade_, type, name, price, quantity));
    return true;
}

bool ChangePriceHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "change", "price")) {
        return false;
    }
    checkArgumentsCount(tokens, 4, "change price <id> <newPrice>");
    int productId = parseInt(tokens[2], "id");
    int newPrice = parseInt(tokens[3], "newPrice");
    facade_.executeCommand(std::make_unique<ChangePriceCommand>(facade_, productId, newPrice));
    return true;
}

bool ChangeQuantityHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "change", "quantity")) {
        return false;
    }
    checkArgumentsCount(tokens, 4, "change quantity <id> <delta>");
    int productId = parseInt(tokens[2], "id");
    int delta = parseInt(tokens[3], "delta");
    facade_.executeCommand(std::make_unique<ChangeQuantityCommand>(facade_, productId, delta));
    return true;
}

bool MoveProductHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "move", "product")) {
        return false;
    }
    checkArgumentsCount(tokens, 5, "move product <id> to <warehouseId>");
    if (tokens[3] != "to") {
        throw std::invalid_argument("Неверный формат команды. Правильно: move product <id> to <warehouseId>");
    }
    int productId = parseInt(tokens[2], "id");
    int warehouseId = parseInt(tokens[4], "warehouseId");
    facade_.executeCommand(std::make_unique<MoveProductCommand>(facade_, productId, warehouseId));
    return true;
}

bool RemoveProductHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "remove", "product")) {
        return false;
    }
    checkArgumentsCount(tokens, 3, "remove product <id>");
    int productId = parseInt(tokens[2], "id");
    facade_.executeCommand(std::make_unique<RemoveProductCommand>(facade_, productId));
    return true;
}
