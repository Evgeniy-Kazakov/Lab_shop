#pragma once
#include <string>
#include "Command.h"

class ShowStatisticsCommand : public Command {
public:
    using Command::Command;
    std::string execute() override;
};

class ShowProductsCommand : public Command {
public:
    using Command::Command;
    std::string execute() override;
};

class ShowOrdersCommand : public Command {
public:
    using Command::Command;
    std::string execute() override;
};

class ShowSettingsCommand : public Command {
public:
    using Command::Command;
    std::string execute() override;
};

class HelpCommand : public Command {
public:
    using Command::Command;
    std::string execute() override;
};
