#include <algorithm>
#include <iostream>
#include <memory>
#include <windows.h>
#include "Warehouse.h"
#include "ProductFactory.h"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        //Сценарий 1
        std::cout << "Сценарий 1" << std::endl;
        Warehouse warehousefirst(10);
        SmartphoneFactory phoneFactory;
        LaptopFactory laptopFactory;
        TShirtFactory tshirtFactory;

        warehousefirst.addProduct(phoneFactory.createProduct("Iphone 17", 50000, 10, 0.2));
        warehousefirst.addProduct(laptopFactory.createProduct("MacBook", 100000, 8, 1.5));
        warehousefirst.addProduct(tshirtFactory.createProduct("Calvin Klein", 5000, 40, 0.4));
        std::cout << "Содержание склада" << std::endl;
        for (Product* product : warehousefirst) {
            std::cout << "ID: " << product->getId() << " || ";
            std::cout << "Name: " << product->getName() << " || ";
            std::cout << "Category: " << product->getCategory() << " || ";
            std::cout << "Price: " << product->getPrice().getValue() << " || ";
            std::cout << "Quantity: " << product->getQuantity().getValue() << " || ";
            std::cout << "Weight: " << product->getWeight().getValue() << std::endl << std::endl;
        }

        //Сценарий 2
        std::cout << "Сценарий 2" << std::endl;
        Warehouse warehousesecond = warehousefirst;
        if (warehousesecond.begin() != warehousesecond.end()) {
            Product* firstInCopy = *warehousesecond.begin();
            firstInCopy->setPrice(Price(60000));
        }
        std::cout << "Цена первого товара в warehousefirst: " << (*warehousefirst.begin())->getPrice().getValue() << std::endl;
        std::cout << "Цена первого товара в warehousesecond: " << (*warehousesecond.begin())->getPrice().getValue() << std::endl << std::endl;

        //Сценарий 3
        std::cout << "Сценарий 3" << std::endl;
        Warehouse warehousethird = std::move(warehousesecond);
        std::cout << "Элементов в warehousethird: " << warehousethird.getCurrentSize() << std::endl;
        std::cout << "Элементов в warehousesecond: " << warehousesecond.getCurrentSize() << std::endl << std::endl;

        //Сценарий 4
        std::cout << "Сценарий 4" << std::endl;
        int searchId = (*warehousefirst.begin())->getId();
        Product* findId = warehousefirst.findById(searchId);
        if (findId != nullptr) {
            std::cout << "Найден товар с id (" << searchId << "): "<< findId->getName() << std::endl;
        }
        auto electronic = warehousefirst.findByCategory("electronics");
        std::cout << "Найдено товаров категории electronic: " << electronic.size() << std::endl;
        auto cost = warehousefirst.findByPrice(Price(100000));
        std::cout << "Найдено товаров с ценой 100000: " << cost.size() << std::endl;
        warehousefirst.removeById(searchId);
        std::cout << "Удален товар с id:" << searchId << std::endl;
        warehousefirst.removeByIndex(1);
        std::cout << "Удален товар с индексом 0" << std::endl;

        std::cout << "Оставшиеся товары в warehousefirst: " << std:: endl;
        for (const Product* product : warehousefirst) {
            std::cout << "ID: " << product->getId() << " || ";
            std::cout << "Name: " << product->getName() << std::endl << std::endl;
        }

        //Сценарий 5
        std::cout << "Сценарий 5" << std::endl;
        Warehouse warehousefourth(10);

        auto it = std::find_if(warehousethird.begin(), warehousethird.end(), [](Product* product) {
           return product->getName() == "MacBook";
        });
        if (it != warehousethird.end()) {
            Product* laptop = *it;
            bool transferred = laptop->transferTo(warehousefourth);
            if (transferred) {
                std::cout << "Товар перенесен на warehousefourth" << std::endl;
                Product* transferLaptop = *warehousefourth.begin();
                transferLaptop->setPrice(Price(90000));
                transferLaptop->changeQuantity(-2);
                std::cout << "Обновленный товар на warehousefourth: " << transferLaptop->getName() << " || ";
                std::cout << "Новая цена: " << transferLaptop->getPrice().getValue() << " || ";
                std::cout << "Остаток: " << transferLaptop->getQuantity().getValue() << std::endl;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Ошибка при выполнении программы: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
