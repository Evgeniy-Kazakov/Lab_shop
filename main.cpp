#include <iostream>
#include <string>
#include <windows.h>
#include "ShopFacade.h"

void runCommand(ShopFacade& facade, const std::string& line) {
    std::cout << "> " << line << std::endl;
    try {
        if (!facade.processInput(line)) {
            std::cout << "Неизвестная команда. Введите help" << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    ShopFacade facade;

    std::cout << "Сценарий 1" << std::endl;
    runCommand(facade, "add product Smartphone \"iPhone 15\" 100000 5");
    runCommand(facade, "add product Laptop \"MacBook Pro\" 200000 3");
    runCommand(facade, "show products");

    std::cout << std::endl << "Сценарий 2" << std::endl;
    runCommand(facade, "create order \"Иван\" 1,2 courier");
    runCommand(facade, "confirm payment 1");
    runCommand(facade, "show orders");

    std::cout << std::endl << "Сценарий 3" << std::endl;
    runCommand(facade, "change price 1 90000");
    runCommand(facade, "change quantity 1 -2");
    runCommand(facade, "show products");

    std::cout << std::endl << "Сценарий 4" << std::endl;
    runCommand(facade, "create order \"Пётр\" 2 post");
    runCommand(facade, "cancel order 2");
    runCommand(facade, "ship order 1");
    runCommand(facade, "show statistics");

    std::cout << std::endl << "Сценарий 5" << std::endl;
    runCommand(facade, "add product Milk \"Молоко\" 100 20");
    runCommand(facade, "create order \"Анна\" 3:5 pickup");
    runCommand(facade, "show products");
    runCommand(facade, "remove product 3");
    runCommand(facade, "cancel order 3");
    runCommand(facade, "remove product 3");
    runCommand(facade, "show statistics");

    std::cout << std::endl << "Введите команду (help - список команд, exit - выход)" << std::endl;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "exit") {
            break;
        }
        if (!line.empty()) {
            runCommand(facade, line);
        }
    }
    return 0;
}
