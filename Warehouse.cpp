//
// Created by Пользователь on 26.09.2026.
//

#include "Warehouse.h"
#include <algorithm>
#include <utility>

Warehouse::Warehouse(std::size_t maxSize): maxSize_(maxSize) {}

Warehouse::Warehouse (const Warehouse& other): maxSize_(other.maxSize_) {
    products_.reserve(other.products_.size());
    for (const auto& prod : other.products_) {
        if (prod) {
            auto copy = prod->clone();
            copy->setWarehouse(this);
            products_.push_back(prod->clone());
        }
    }
}

Warehouse& Warehouse::operator= (const Warehouse& other) {
    if (this == &other) {
        return *this;
    }
    maxSize_ = other.maxSize_;
    products_.clear();
    products_.reserve(other.products_.size());
    for (const auto& prod : other.products_) {
        if (prod) {
            auto copy = prod->clone();
            copy->setWarehouse(this);
            products_.push_back(prod->clone());
        }
    }

    return *this;
}

Warehouse::Warehouse (Warehouse&& other) noexcept: maxSize_(other.maxSize_), products_(std::move(other.products_)) {
    for (auto& prod : products_) {
        if (prod) {
            prod->setWarehouse(this);
        }
    }
    other.maxSize_ = 0;
}

Warehouse& Warehouse::operator= (Warehouse&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    maxSize_ = other.maxSize_;
    products_ = std::move(other.products_);
    other.maxSize_ = 0;
    for (auto& prod : products_) {
        if (prod) {
            prod->setWarehouse(this);
        }
    }
    return *this;
}

bool Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (!product || products_.size() >= maxSize_) {
        return false;
    }
    product->setWarehouse(this);
    products_.push_back(std::move(product));
    return true;
}

bool Warehouse::removeById(int id) {
    auto it = std::find_if(products_.begin(), products_.end(),
        [id](const std::unique_ptr<Product>& product) {
            return product && product->getId() == id;
        });
    if (it != products_.end()) {
        products_.erase(it);
        return true;
    }
    return false;
}

bool Warehouse::removeByIndex(size_t index) {
    if (index >= products_.size()) {
        return false;
    }
    products_.erase(products_.begin() + index);
    return true;
}

Product* Warehouse::findById(int id) {
    for (const auto& prod : products_) {
        if (prod && prod->getId() == id) {
            return prod.get();
        }
    }
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) {
    std::vector<Product*> result;
    for (const auto& prod : products_) {
        if (prod && prod->getCategory() == category) {
            result.push_back(prod.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) {
    std::vector<Product*> result;
    for (const auto& prod : products_) {
        if (prod && prod->getPrice() == price) {
            result.push_back(prod.get());
        }
    }
    return result;
}
