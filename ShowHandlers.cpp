#include "ShowHandlers.h"
#include "ShopFacade.h"
#include "ShowCommands.h"

bool ShowStatisticsHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "show", "statistics")) {
        return false;
    }
    checkArgumentsCount(tokens, 2, "show statistics");
    facade_.executeCommand(std::make_unique<ShowStatisticsCommand>(facade_));
    return true;
}

bool ShowProductsHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "show", "products")) {
        return false;
    }
    checkArgumentsCount(tokens, 2, "show products");
    facade_.executeCommand(std::make_unique<ShowProductsCommand>(facade_));
    return true;
}

bool ShowOrdersHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "show", "orders")) {
        return false;
    }
    checkArgumentsCount(tokens, 2, "show orders");
    facade_.executeCommand(std::make_unique<ShowOrdersCommand>(facade_));
    return true;
}

bool ShowSettingsHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "show", "settings")) {
        return false;
    }
    checkArgumentsCount(tokens, 2, "show settings");
    facade_.executeCommand(std::make_unique<ShowSettingsCommand>(facade_));
    return true;
}

bool HelpHandler::process(const std::vector<std::string>& tokens) {
    if (!matches(tokens, "help")) {
        return false;
    }
    checkArgumentsCount(tokens, 1, "help");
    facade_.executeCommand(std::make_unique<HelpCommand>(facade_));
    return true;
}
