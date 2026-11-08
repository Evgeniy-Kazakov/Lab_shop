#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Product.h"
#include "OrderStatus.h"
#include "Delivery.h"
#include "Discount.h"
#include "OrderEvent.h"

class Order : public IObservable {
    static int nextId_;
    int id_;
    std::string customer_;
    std::vector<std::shared_ptr<Product>> items_;
    OrderStatus status_;
    std::shared_ptr<Delivery> delivery_;
    std::vector<std::string> discounts_;
    double discountSum_;
    double cashback_;
    bool freeDelivery_;
    std::vector<std::string> gifts_;
    void checkTable() const;
    void checkItemsEditable() const;
public:
    explicit Order(const std::string& customer);

    Order(const Order& other);
    Order& operator=(const Order& other);
    Order(Order&& other) = default;
    Order& operator=(Order&& other) = default;
    ~Order() = default;

    void addItem(std::shared_ptr<Product> item);
    bool removeItem(int productId);

    void setStatus(OrderStatus newStatus);
    bool setDelivery(std::shared_ptr<Delivery> delivery);
    void applyDiscount(const Discount& discount);

    double getTotalWeight() const;
    double getItemsPrice() const;
    double getDeliverycost() const;
    double getTotalPrice() const;

    void addDiscountSum(double amount) {discountSum_ += amount;}
    void addCashback(double amount) {cashback_ += amount;}
    void setFreeDelivery(bool value) {freeDelivery_ = value;}
    void addGift(const std::string& giftName) {gifts_.push_back(giftName);}

    int getId() const {return id_;}
    const std::string& getCustomer() const {return customer_;}
    OrderStatus getStatus() const {return status_;}
    const std::vector<std::shared_ptr<Product>>& getItems() const {return items_;}
    std::shared_ptr<Delivery> getDelivery() const {return delivery_;}
    const std::vector<std::string>& getDiscounts() const {return discounts_;}
    double getDiscountSum() const {return discountSum_;}
    double getCashback() const {return cashback_;}
    bool getFreeDelivery() const {return freeDelivery_;}
    const std::vector<std::string>& getGifts() const {return gifts_;}
};
