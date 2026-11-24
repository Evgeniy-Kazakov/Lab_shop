#pragma once
#include <map>
#include <memory>
#include <string>
#include "Product.h"
#include "ProductFactory.h"

class ShopProductFactory {
    struct FactoryInfo {
        std::unique_ptr<ProductFactory> factory;
        double defaultWeight;
    };
    std::map<std::string, FactoryInfo> factories_;
    void addType(const std::string& typeName, std::unique_ptr<ProductFactory> factory, double defaultWeight);
public:
    ShopProductFactory();
    std::unique_ptr<Product> createProduct(const std::string& type, const std::string& name, int price, int quantity);
    std::string getTypesText() const;
};
