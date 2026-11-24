#include "OrderHandlers.h"
#include "OrderCommands.h"
#include "ShopFacade.h"
#include "StringUtils.h"
#include <memory>
#include <stdexcept>
#include "Discount.h"

static std::shared_ptr<Discount> parsePromotion(const std::vector<std::string>& tokens) {
    if (tokens.size() == 5) {
        return nullptr;
    }
    std::string name = toLower(tokens[5]);
    if (name != "percent" && name != "cashback" && name != "freedelivery" && name != "gift") {
        throw std::invalid_argument("Неизвестная акция '" + tokens[5]
            + "'. Доступные: percent <N>, cashback <N>, freedelivery, gift <название>");
    }

    if (name == "freedelivery") {
        if (tokens.size() != 6) {
            throw std::invalid_argument("Акция freedelivery пишется без значения");
        }
        return std::make_shared<FreeDeliveryDiscount>();
    }

    if (tokens.size() != 7) {
        throw std::invalid_argument("Для акции " + name + " нужно указать значение");
    }
    if (name == "gift") {
        return std::make_shared<GiftDiscount>(tokens[6]);
    }

    int percent = parseInt(tokens[6], "процент");
    if (percent <= 0 || percent > 100) {
        throw std::invalid_argument("Процент должен быть целым числом от 1 до 100");
    }
    if (name == "percent") {
        return std::make_shared<PercentDiscount>(percent);
    }
    return std::make_shared<CashbackDiscount>(percent);
}

bool CreateOrderHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "create", "order")) {
        return false;
    }
    if (tokens.size() < 5 || tokens.size() > 7) {
        throw std::invalid_argument("Неверный формат команды. Правильно: "
            "create order <customer> <items> <deliveryType> [<promotion>]");
    }
    std::string customer = tokens[2];
    std::vector<OrderItemRequest> items = parseOrderItems(tokens[3]);
    std::string deliveryType = tokens[4];
    std::shared_ptr<Discount> promotion = parsePromotion(tokens);
    facade_.executeCommand(std::make_unique<CreateOrderCommand>(facade_, customer, items, deliveryType,  promotion));
    return true;
}

bool CancelOrderHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "cancel", "order")) {
        return false;
    }
    checkArgumentsCount(tokens, 3, "cancel order <id>");
    int orderId = parseInt(tokens[2], "id");
    facade_.executeCommand(std::make_unique<CancelOrderCommand>(facade_, orderId));
    return true;
}

bool ConfirmPaymentHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "confirm", "payment")) {
        return false;
    }
    checkArgumentsCount(tokens, 3, "confirm payment <id>");
    int orderId = parseInt(tokens[2], "id");
    facade_.executeCommand(std::make_unique<ConfirmPaymentCommand>(facade_, orderId));
    return true;
}

bool ShipOrderHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "ship", "order")) {
        return false;
    }
    checkArgumentsCount(tokens, 3, "ship order <id>");
    int orderId = parseInt(tokens[2], "id");
    facade_.executeCommand(std::make_unique<ShipOrderCommand>(facade_, orderId));
    return true;
}
