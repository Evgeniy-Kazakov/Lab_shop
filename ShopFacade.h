#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Command.h"
#include "CommandHistory.h"
#include "DeliveryService.h"
#include "Handler.h"
#include "StringUtils.h"
#include "OrderManager.h"
#include "PaymentSystem.h"
#include "ShopMediator.h"
#include "ShopProductFactory.h"
#include "WarehouseManager.h"

class ShopFacade {
    WarehouseManager warehouses_;
    OrderManager orderManager_;
    PaymentSystem paymentSystem_;
    DeliveryService deliveryService_;
    ShopMediator mediator_;
    ShopProductFactory productFactory_;
    CommandHistory history_;
    std::unique_ptr<Handler> chain_;
    void buildChain();
public:
    ShopFacade();

    ShopFacade(const ShopFacade&) = delete;
    ShopFacade& operator=(const ShopFacade&) = delete;

    int addProduct(const std::string& type, const std::string& name, int price, int quantity);
    void changePrice(int productId, int newPrice);
    void changeQuantity(int productId, int delta);
    void moveProduct(int productId, int newWarehouseId);
    void removeProduct(int productId);

    std::shared_ptr<Order> createOrder(const std::string& customer, const std::vector<OrderItemRequest>& items,
        const std::string& deliveryType, const std::shared_ptr<Discount>& promotion);
    void cancelOrder(int orderId);
    void confirmPayment(int orderId);
    std::string shipOrder(int orderId);

    std::string getStatistics() const;
    std::string listProducts() const;
    std::string listOrders() const;
    std::string getSettings() const;

    void executeCommand(std::unique_ptr<Command> command);
    bool processInput(const std::string& input);
};
