//
// Created by Пользователь on 25.09.2026.
//

#include "Product.h"

int Product::nextId = 1;
Product::Product(std::string name, Price price, Quantity quantity, Weight weight, std::string category):
    id(nextId++), name(std::move(name)), price_(price), quantity_(quantity), weight_(weight), category(std::move(category)) {}

void Product::changeQuantity(int delta) {
    quantity_.change(delta);
}

void Product::setPrice(const Price& newPrice) {
    price_ = newPrice;
}

void Product::transferTo(Warehouse& other) { // надо дописать

}

std::unique_ptr<Product> Smartphone::clone() const {
    return std::make_unique<Smartphone>(*this);
}

std::unique_ptr<Product> Laptop::clone() const {
    return std::make_unique<Laptop>(*this);
}

std::unique_ptr<Product> TShirt::clone() const {
    return std::make_unique<TShirt>(*this);
}

std::unique_ptr<Product> Jacket::clone() const {
    return std::make_unique<Jacket>(*this);
}

std::unique_ptr<Product> Milk::clone() const {
    return std::make_unique<Milk>(*this);
}

std::unique_ptr<Product> Bread::clone() const {
    return std::make_unique<Bread>(*this);
}
