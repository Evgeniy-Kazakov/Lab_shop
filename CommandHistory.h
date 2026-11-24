#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "Command.h"

class CommandHistory {
    std::vector<std::unique_ptr<Command>> commands_;
public:
    void push(std::unique_ptr<Command> command) {
        commands_.push_back(std::move(command));
    }
    const Command* getLastCommand() const {
        if (commands_.empty()) {
            return nullptr;
        }
        return commands_.back().get();
    }
};
