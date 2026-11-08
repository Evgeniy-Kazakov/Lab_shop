#pragma once
#include <string>

class Order;
class Discount {
public:
    virtual ~Discount() = default;
    virtual void apply(Order& order) const = 0;
    virtual std::string getName() const = 0;
};

class PercentDiscount : public Discount {
    double percent_;
public:
    explicit PercentDiscount(double percent);
    void apply(Order& order)const override;
    std::string getName() const override;
};

class CashbackDiscount : public Discount {
    double percent_;
public:
    explicit CashbackDiscount(double percent);
    void apply(Order& order) const override;
    std::string getName() const override;
};

class FreeDeliveryDiscount : public Discount {
public:
    void apply(Order& order) const override;
    std::string getName() const override;
};

class GiftDiscount : public Discount {
    std::string gift_;
public:
    explicit GiftDiscount(std::string gift);
    void apply(Order& order) const override;
    std::string getName() const override;
};
