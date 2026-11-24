#include "Handler.h"
#include <stdexcept>
#include <utility>
#include "StringUtils.h"

Handler* Handler::setNext(std::unique_ptr<Handler> next) {
    next_ = std::move(next);
    return next_.get();
}

bool Handler::handle(const std::string& input) {
    return handleTokens(splitTokens(input));
}

bool Handler::handleTokens(const std::vector<std::string>& tokens) {
    if (process(tokens)) {
        return true;
    }
    if (next_) {
        return next_->handleTokens(tokens);
    }
    return false;
}

bool Handler::matches(const std::vector<std::string>& tokens, const std::string& firstWord,
                      const std::string& secondWord) const {
    if (tokens.empty() || toLower(tokens[0]) != firstWord) {
        return false;
    }
    if (secondWord.empty()) {
        return true;
    }
    return tokens.size() >= 2 && toLower(tokens[1]) == secondWord;
}

void Handler::checkArgumentsCount(const std::vector<std::string>& tokens, std::size_t expected,
                                  const std::string& usage) const {
    if (tokens.size() != expected) {
        throw std::invalid_argument("Неверный формат команды. Правильно: " + usage);
    }
}
