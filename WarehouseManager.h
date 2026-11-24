#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Warehouse.h"
#include "Product.h"

class WarehouseManager {
    std::vector<std::unique_ptr<Warehouse>> warehouses_;
public:
    int addWarehouse(std::size_t maxSize);
    int getWarehousesCount() const {return static_cast<int>(warehouses_.size());}
    Warehouse& getWarehouse(int warehouseId);

    int addProduct(std::unique_ptr<Product> product);
    Product* findProduct(int productId);
    void removeProduct(int productId);
    void changePrice(int productId, int newPrice);
    void changeQuantity(int productId, int delta);
    void moveProduct(int productId, int newWarehouseId);

    std::string getProductsText() const;
    std::string getLoadText() const;
};
