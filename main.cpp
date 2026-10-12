#include <algorithm>
#include <iostream>
#include <windows.h>
#include <utility>
#include <exception>
#include "Warehouse.h"
#include "Product.h"
#include "ProductFactory.h"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        //Сценарий 1
        std::cout << "Сценарий 1" << std::endl;
        Warehouse warehouseFirst(10);
        SmartphoneFactory phoneFactory;
        LaptopFactory laptopFactory;
        TShirtFactory tShirtFactory;

        if (!warehouseFirst.addProduct(phoneFactory.createProduct("Iphone 17", 50000, 10, 0.2))) {
            std::cout << "Не удалось добавить товар Iphone 17" << std::endl;
        }
        else {
            std::cout << "Товар 'Iphone 17' успешно добавлен." << std::endl;
        }
        if (!warehouseFirst.addProduct(laptopFactory.createProduct("MacBook", 100000, 8, 1.5))) {
            std::cout << "Не удалось добавить товар MacBook" << std::endl;
        }
        else {
            std::cout << "Товар 'MacBook' успешно добавлен." << std::endl;
        }
        if (!warehouseFirst.addProduct(tShirtFactory.createProduct("Calvin Klein", 5000, 40, 0.4))) {
            std::cout << "Не удалось добавить товар Calvin Klein" << std::endl;
        }
        else {
            std::cout << "Товар 'Calvin Klein' успешно добавлен." << std::endl;
        }

        std::cout << "Содержание склада" << std::endl;
        for (Product* product : warehouseFirst) {
            std::cout << "ID: " << product->getId() << " || ";
            std::cout << "Name: " << product->getName() << " || ";
            std::cout << "Category: " << product->getCategory() << " || ";
            std::cout << "Price: " << product->getPrice().getValue() << " || ";
            std::cout << "Quantity: " << product->getQuantity().getValue() << " || ";
            std::cout << "Weight: " << product->getWeight().getValue() << std::endl;
        }

        //Сценарий 2
        std::cout << std::endl << "Сценарий 2" << std::endl;
        Warehouse warehouseSecond = warehouseFirst;
        if (warehouseSecond.begin() != warehouseSecond.end()) {
            Product* firstInCopy = *warehouseSecond.begin();
            firstInCopy->setPrice(Price(60000));
        }
        std::cout << "Цена первого товара в warehouseFirst: " << (*warehouseFirst.begin())->getPrice().getValue() << std::endl;
        std::cout << "Цена первого товара в warehouseSecond: " << (*warehouseSecond.begin())->getPrice().getValue() << std::endl << std::endl;

        //Сценарий 3
        std::cout << "Сценарий 3" << std::endl;
        Warehouse warehouseThird = std::move(warehouseSecond);
        std::cout << "Элементов в warehouseThird после перемещения: " << warehouseThird.getCurrentSize() << std::endl;
        std::cout << "Элементов в warehouseSecond после перемещения: " << warehouseSecond.getCurrentSize() << std::endl << std::endl;

        //Сценарий 4
        std::cout << "Сценарий 4" << std::endl;
        int searchId = (*warehouseFirst.begin())->getId();
        Product* foundId = warehouseFirst.findById(searchId);
        if (foundId != nullptr) {
            std::cout << "Найден товар с id (" << searchId << "): "<< foundId->getName() << std::endl;
        }
        else {
            std::cout << "Товар с id (" << searchId << ") не найден!" << std::endl;
        }

        auto electronics = warehouseFirst.findByCategory("electronics");
        std::cout << "Найдено товаров категории electronicss: " << electronics.size() << std::endl;

        auto productsPrice = warehouseFirst.findByPrice(Price(100000));
        std::cout << "Найдено товаров с ценой 100000: " << productsPrice.size() << std::endl;

        warehouseFirst.removeById(searchId);
        std::cout << "Удален товар с id:" << searchId << std::endl;
        warehouseFirst.removeByIndex(1);
        std::cout << "Удален товар с индексом 1" << std::endl;

        std::cout << "Оставшиеся товары в warehouseFirst: " << std::endl;
        for (const Product* product : warehouseFirst) {
            std::cout << "ID: " << product->getId() << " || ";
            std::cout << "Name: " << product->getName() << std::endl << std::endl;
        }

        //Сценарий 5
        std::cout << "Сценарий 5" << std::endl;
        Warehouse warehouseFourth(10);
        auto it = std::find_if(warehouseThird.begin(), warehouseThird.end(), [](Product* product) {
           return product->getName() == "MacBook";
        });
        if (it != warehouseThird.end()) {
            Product* laptop = *it;
            bool isTransferred = laptop->transferTo(warehouseFourth);
            if (isTransferred) {
                std::cout << "Товар перенесен на warehouseFourth" << std::endl;
                Product* transferLaptop = *warehouseFourth.begin();
                transferLaptop->setPrice(Price(90000));
                transferLaptop->changeQuantity(-2);
                std::cout << "Обновленный товар на warehouseFourth: " << transferLaptop->getName() << " || ";
                std::cout << "Новая цена: " << transferLaptop->getPrice().getValue() << " || ";
                std::cout << "Остаток: " << transferLaptop->getQuantity().getValue() << std::endl;
            }
            else {
                std::cout << "Не удалось перенести товар" << std::endl;
            }
        }
        else {
            std::cout << "Товар 'MacBook' не найден в warehouseThird" << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Ошибка при выполнении программы: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
