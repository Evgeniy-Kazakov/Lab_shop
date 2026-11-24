#include "StringUtils.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::vector<std::string> splitTokens(const std::string& input) {
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;
    bool hasToken = false;

    for (char symbol : input) {
        if (symbol == '"') {
            inQuotes = !inQuotes;
            hasToken = true;
        }
        else if (std::isspace(static_cast<unsigned char>(symbol)) && !inQuotes) {
            if (hasToken) {
                tokens.push_back(current);
                current.clear();
                hasToken = false;
            }
        }
        else {
            current += symbol;
            hasToken = true;
        }
    }
    if (inQuotes) {
        throw std::invalid_argument("Не закрыты кавычки");
    }
    if (hasToken) {
        tokens.push_back(current);
    }
    return tokens;
}

std::string toLower(const std::string& text) {
    std::string result = text;
    for (char& symbol : result) {
        symbol = static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
    }
    return result;
}

int parseInt(const std::string& text, const std::string& fieldName) {
    try {
        std::size_t position = 0;
        int value = std::stoi(text, &position);
        if (position != text.size()) {
            throw std::invalid_argument("extra symbols");
        }
        return value;
    }
    catch (const std::exception&) {
        throw std::invalid_argument("Поле '" + fieldName + "' должно быть целым числом, а получено: '" + text + "'");
    }
}

std::vector<OrderItemRequest> parseOrderItems(const std::string& text) {
    std::vector<OrderItemRequest> result;
    std::stringstream stream(text);
    std::string part;
    while (std::getline(stream, part, ',')) {
        OrderItemRequest request{0, 1};
        std::size_t colonPosition = part.find(':');
        if (colonPosition == std::string::npos) {
            request.productId = parseInt(part, "id товара");
        }
        else {
            request.productId = parseInt(part.substr(0, colonPosition), "id товара");
            request.quantity = parseInt(part.substr(colonPosition + 1), "количество");
        }
        result.push_back(request);
    }
    return result;
}

std::string formatMoney(double value) {
    std::ostringstream stream;
    stream << std::setprecision(10) << value;
    return stream.str();
}

std::string trimEnd(const std::string& text) {
    std::string result = text;
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r' || result.back() == ' ')) {
        result.pop_back();
    }
    return result;
}
