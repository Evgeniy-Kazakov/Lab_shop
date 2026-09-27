//
// Created by Пользователь on 26.09.2026.
//

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <cstddef>
#include "Product.h"

class Warehouse {
    std::size_t maxSize_;
    std::vector<std::unique_ptr<Product>> products_;
public:
    explicit Warehouse(std::size_t maxSize);

    ~Warehouse() = default;
    Warehouse (const Warehouse& other);
    Warehouse& operator= (const Warehouse& other);
    Warehouse (Warehouse&& other) noexcept;
    Warehouse& operator= (Warehouse&& other) noexcept;

    bool addProduct(std::unique_ptr<Product> product);
    bool removeById(int id);
    bool removeByIndex(size_t index);

    Product* findById(int id);
    std::vector<Product*> findByCategory(const std::string& category);
    std::vector<Product*> findByPrice(const Price& price);

    std::size_t getMaxSize() const {return maxSize_;}
    std::size_t getCurrentSize() const {return products_.size();}
};
