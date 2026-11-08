#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <stdexcept>
#include "Warehouse.h"
#include "Product.h"
#include "ProductFactory.h"
#include "Order.h"
#include "OrderManager.h"
#include "Delivery.h"
#include "DeliveyProxy.h"
#include "Discount.h"
#include "Operators.h"

std::shared_ptr<Product> makeOrderItem(Warehouse& warehouse, const std::string& name, int amount) {
    for (Product* product : warehouse) {
        if (product->getName() == name) {
            product->changeQuantity(-amount);
            std::shared_ptr<Product> item = product->clone();
            item->setWarehouse(nullptr);
            item->setQuantity(amount);
            return item;
        }
    }
    throw std::invalid_argument("Product not found: " + name);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try {
        Warehouse warehouse(10);
        SmartphoneFactory phoneFactory;
        LaptopFactory laptopFactory;
        TShirtFactory tShirtFactory;
        warehouse.addProduct(phoneFactory.createProduct("Iphone 17", 50000, 10, 0.2));
        warehouse.addProduct(laptopFactory.createProduct("MacBook", 100000, 8, 1.5));
        warehouse.addProduct(tShirtFactory.createProduct("Calvin Klein", 5000, 40, 0.4));

        //Сценарий 1
        std::cout << "Сценарий 1" << std::endl;
        OrderManager manager(3);
        std::vector<std::shared_ptr<Product>> itemsFirst;
        itemsFirst.push_back(makeOrderItem(warehouse, "Iphone 17", 2));
        itemsFirst.push_back(makeOrderItem(warehouse, "Calvin Klein", 3));
        std::shared_ptr<Order> orderFirst = manager.createOrder("Ivan", itemsFirst);
        PercentDiscount percent10(10);
        *orderFirst + percent10;
        std::cout << *orderFirst;

        //Сценарий 2
        std::cout << std::endl << "Сценарий 2" << std::endl;
        std::vector<std::shared_ptr<Product>> itemsSecond;
        itemsSecond.push_back(makeOrderItem(warehouse, "MacBook", 7));
        std::shared_ptr<Order> orderSecond = manager.createOrder("Petr", itemsSecond);
        std::shared_ptr<Delivery> postDelivery = std::make_shared<DeliveryProxy>(std::make_shared<PostDelivery>());
        std::shared_ptr<Delivery> courierDelivery = std::make_shared<DeliveryProxy>(std::make_shared<CourierDelivery>());
        std::shared_ptr<Delivery> pickupDelivery = std::make_shared<DeliveryProxy>(std::make_shared<PickupDelivery>());
        if (postDelivery << *orderSecond) {
            std::cout << "Почта выбрана" << std::endl;
            std::cout << "Срок: " << postDelivery-> getEstimatedTime() << std::endl;
        }
        else if (courierDelivery << *orderSecond) {
            std::cout << "Выбрана доставка курьером" << std::endl;
            std::cout << "Срок: " << courierDelivery-> getEstimatedTime() << std::endl;
        }
        else if (pickupDelivery << *orderSecond) {
            std::cout << "Выбран самовывоз" << std::endl;
        }
        std::cout << "Стоимость доставки: " << orderSecond->getDeliverycost() << std::endl;

        //Сценарий 3
        std::cout << std::endl << "Сценарий 3" << std::endl;
        manager.updateStatus(orderFirst->getId(), OrderStatus::Paid);
        manager.updateStatus(orderSecond->getId(), OrderStatus::Paid);
        std::cout << "Оборот: " << manager.getTurnover() << std::endl;
        std::cout << "Клиентов: " << manager.getCustomersCount() << std::endl;
        try {
            manager.updateStatus(orderFirst->getId(), OrderStatus::Pending);
        }
        catch (std::exception& e) {
            std::cout << "Ошибка смены статуса: " << e.what() << std::endl;
        }

        //Сценарий 4
        std::cout << std::endl << "Сценарий 4" << std::endl;
        std::vector<std::shared_ptr<Product>> itemsThird;
        itemsThird.push_back(makeOrderItem(warehouse, "Iphone 17", 1));
        itemsThird.push_back(makeOrderItem(warehouse, "Calvin Klein", 5));
        std::shared_ptr<Order> orderThird = manager.createOrder("Anna", itemsThird);
        courierDelivery << *orderThird;
        CashbackDiscount cashback5(5);
        FreeDeliveryDiscount freeDelivery;
        GiftDiscount mugGift("Кружка");
        *orderThird + percent10;
        *orderThird + cashback5;
        *orderThird + freeDelivery;
        *orderThird + mugGift;
        std::cout << *orderThird;

        //Сценарий 5
        std::cout << std::endl << "Сценарий 5" << std::endl;
        std::shared_ptr<Order> orderFourth = manager.createOrder("Ivan", {makeOrderItem(warehouse, "Calvin Klein", 5)});
        std::shared_ptr<Order> orderFifth = manager.createOrder("Ivan", {makeOrderItem(warehouse, "Iphone 17", 1)});
        std::cout << "Активных заказов у Ivan: " << manager.countOrders("Ivan") << std::endl;
        auto extraItem = makeOrderItem(warehouse, "Calvin Klein", 1);
        try {
            manager.createOrder("Ivan", {extraItem});
        }
        catch (std::exception& e) {
            std::cout << "Не удалось создать заказ: " << e.what() << std::endl;
            warehouse.findById(extraItem->getId())->changeQuantity(1);
        }
        manager.updateStatus(orderFifth->getId(), OrderStatus::Cancelled);
        std::cout << "Активных заказов у Ivan после отмены: " << manager.countOrders("Ivan") << std::endl;

        std::cout << "Оборот до отмены оплаченного заказа: " << manager.getTurnover() << std::endl;
        manager.updateStatus(orderSecond->getId(), OrderStatus::Cancelled);
        std::cout << "Оборот после отмены оплаченного заказа Petr: " << manager.getTurnover() << std::endl;

        std::cout << "Клиентов: " << manager.getCustomersCount() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr <<"Ошибка программы: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
