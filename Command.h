#pragma once
#include <string>

class ShopFacade;

class Command {
protected:
    ShopFacade& facade_;
public:
    explicit Command(ShopFacade& facade): facade_(facade) {}
    virtual ~Command() = default;
    virtual std::string execute() = 0;
};
