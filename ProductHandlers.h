#pragma once
#include "Handler.h"

class AddProductHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ChangePriceHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ChangeQuantityHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class MoveProductHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class RemoveProductHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};
