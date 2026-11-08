#pragma once
#include <memory>
#include <string>
#include <utility>
#include "Attributes.h"
#include "ProductType.h"

class Warehouse;
class Product {
    int id_;
    std::string name_;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::shared_ptr<ProductType> type_;
    static int nextId_;
    Warehouse* owner_ = nullptr;
public:
    Product(std::string name, Price price, Quantity quantity, Weight weight, std::string category);
    virtual ~Product() = default;
    virtual std::unique_ptr<Product> clone() const = 0;

    int getId() const {return id_;}
    const std::string& getName() const {return name_;}
    const Price& getPrice() const {return price_;}
    const Quantity& getQuantity() const {return quantity_;}
    const Weight& getWeight() const {return weight_;}
    const std::string& getCategory() const {return type_->getCategory();}
    std::shared_ptr<ProductType> getType() const {return type_;}

    void setWarehouse(Warehouse* warehouse) {owner_ = warehouse;}
    Warehouse* getWarehouse() const {return owner_;}

    void setPrice(const Price& newPrice);
    void changeQuantity(int delta);
    void setQuantity(int newQuantity);
    bool transferTo(Warehouse& other);
};

class Electronics : public Product {
public:
    Electronics(std::string name, Price price, Quantity quantity, Weight weight):
    Product(std::move(name), price, quantity, weight, "electronics") {}
};
class Clothing : public Product {
public:
    Clothing(std::string name, Price price, Quantity quantity, Weight weight):
    Product(std::move(name), price, quantity, weight, "clothing") {}
};
class Food : public Product {
public:
    Food(std::string name, Price price, Quantity quantity, Weight weight):
    Product(std::move(name), price, quantity, weight, "food") {}
};

class Smartphone : public Electronics {
public:
    using Electronics::Electronics;
    std::unique_ptr<Product> clone() const override;
};
class Laptop : public Electronics {
public:
    using Electronics::Electronics;
    std::unique_ptr<Product> clone() const override;
};
class TShirt : public Clothing {
public:
    using Clothing::Clothing;
    std::unique_ptr<Product> clone() const override;
};

class Jacket : public Clothing {
public:
    using Clothing::Clothing;
    std::unique_ptr<Product> clone() const override;
};

class Milk : public Food {
public:
    using Food::Food;
    std::unique_ptr<Product> clone() const override;
};

class Bread : public Food {
public:
    using Food::Food;
    std::unique_ptr<Product> clone() const override;
};
