#pragma once
#include <string>
#include <vector>


std::vector<std::string> splitTokens(const std::string& input);

struct OrderItemRequest {
    int productId;
    int quantity;
};

std::vector<OrderItemRequest> parseOrderItems(const std::string& text);
std::string toLower(const std::string& text);
int parseInt(const std::string& text, const std::string& fieldName);
std::string formatMoney(double value);
std::string trimEnd(const std::string& text);
