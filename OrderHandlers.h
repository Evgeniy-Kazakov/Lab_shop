#pragma once
#include "Handler.h"

class CreateOrderHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class CancelOrderHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ConfirmPaymentHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ShipOrderHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};
