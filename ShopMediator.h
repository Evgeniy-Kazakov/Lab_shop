#pragma once
#include <memory>
#include <string>
#include <vector>
#include "WarehouseManager.h"
#include "OrderManager.h"
#include "PaymentSystem.h"
#include "DeliveryService.h"
#include "StringUtils.h"

class ShopMediator {
    WarehouseManager& warehouses_;
    OrderManager& orderManager_;
    PaymentSystem& paymentSystem_;
    DeliveryService& deliveryService_;
    int freeDeliveryLimit_ = 500000;

    std::shared_ptr<Order> getOrder(int orderId) const;
    void releaseItems(const std::vector<std::shared_ptr<Product>>& items);
public:
    ShopMediator(WarehouseManager& warehouses, OrderManager& orderManager,
                 PaymentSystem& paymentSystem, DeliveryService& deliveryService);

    std::shared_ptr<Order> createOrder(const std::string& customer, const std::vector<OrderItemRequest>& requests,
        const std::string& deliveryType, const std::shared_ptr<Discount>& promotion);
    void confirmPayment(int orderId);
    std::string shipOrder(int orderId);
    void cancelOrder(int orderId);
    std::string getStatistics() const;

    void onProductRemoved(int productId);

    std::string getPromotionsText() const;
};
