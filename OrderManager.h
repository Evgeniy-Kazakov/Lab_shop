#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Order.h"
#include "OrderEvent.h"
#include <set>

class OrderManager : public IObserver {
    std::vector<std::shared_ptr<Order>> orders_;
    std::set<std::string> customers_;
    double turnover_;
    int maxOrders_;
    int activeOrders_;
    bool hasPaidOrders(const std::string& customer) const;
public:
    explicit OrderManager(int maxOrders);
    ~OrderManager() override;

    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;

    std::shared_ptr<Order> createOrder(const std::string& customer, const std::vector<std::shared_ptr<Product>>& items);
    bool updateStatus(int orderId, OrderStatus newStatus);
    std::shared_ptr<Order> findOrder(int orderId) const;
    int countOrders(const std::string& customer) const;

    double getTurnover() const {return turnover_;}
    int getCustomersCount() const {return static_cast<int>(customers_.size());}
    int getActiveOrders() const {return activeOrders_;}

    void onOrderEvent(const OrderEvent& event) override;
};
