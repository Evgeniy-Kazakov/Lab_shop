#pragma once
#include <vector>
#include <string>
#include <memory>
#include <cstddef>
#include "Product.h"
#include "WarehouseIterator.h"
#include "Attributes.h"

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
    bool canAdd(int id) const;
    std::unique_ptr<Product> extractById(int id);
    bool removeByIndex(std::size_t index);

    Product* findById(int id);
    std::vector<Product*> findByCategory(const std::string& category);
    std::vector<Product*> findByPrice(const Price& price);

    std::size_t getMaxSize() const {return maxSize_;}
    std::size_t getCurrentSize() const {return products_.size();}

    WarehouseIterator begin() {
        return WarehouseIterator(products_.begin(), products_.end());
    }
    WarehouseIterator end() {
        return WarehouseIterator(products_.end(), products_.end());
    }
    WarehouseConstIterator begin() const {
        return WarehouseConstIterator(products_.cbegin(), products_.cend());
    }
    WarehouseConstIterator end() const {
        return WarehouseConstIterator(products_.cend(), products_.cend());
    }
};
