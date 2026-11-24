#pragma once
#include <memory>
#include <string>
#include <vector>

class ShopFacade;
class Handler {
    std::unique_ptr<Handler> next_;
    bool handleTokens(const std::vector<std::string>& tokens);
protected:
    ShopFacade& facade_;

    virtual bool process(const std::vector<std::string>& tokens) = 0;

    bool matches(const std::vector<std::string>& tokens, const std::string& firstWord,
                 const std::string& secondWord = "") const;
    void checkArgumentsCount(const std::vector<std::string>& tokens, std::size_t expected,
                             const std::string& usage) const;
public:
    explicit Handler(ShopFacade& facade): facade_(facade) {}
    virtual ~Handler() = default;

    Handler* setNext(std::unique_ptr<Handler> next);
    bool handle(const std::string& input);
};
