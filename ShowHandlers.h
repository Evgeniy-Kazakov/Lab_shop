#pragma once
#include "Handler.h"

class ShowStatisticsHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ShowProductsHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ShowOrdersHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class ShowSettingsHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};

class HelpHandler : public Handler {
public:
    using Handler::Handler;
protected:
    bool process(const std::vector<std::string>& tokens) override;
};
