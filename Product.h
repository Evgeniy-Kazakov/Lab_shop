//
// Created by Пользователь on 25.09.2026.
//

#pragma once
#include <memory>
#include <string>
#include <utility>
#include "Attributes.h"

class Warehouse;
class Product {
protected:
    int id;
    std::string name;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category;
    static int nextId;
public:
    Product(std::string name, Price price, Quantity quantity, Weight weight, std::string category);
    virtual ~Product() = default;
    virtual std::unique_ptr<Product> clone() const = 0;

    int getId() const {return id;}
    std::string getName() const {return name;}
    Price getPrice() const {return price_;}
    Quantity getQuantity() const {return quantity_;}
    Weight getWeight() const {return weight_;}
    std::string getCategory() const {return category;}

    void setPrice(const Price& newPrice);
    void changeQuantity(int delta);
    void transferTo(Warehouse& other);
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
