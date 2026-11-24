#include "ShopProductFactory.h"
#include <stdexcept>
#include <utility>
#include "StringUtils.h"

ShopProductFactory::ShopProductFactory() {
    addType("smartphone", std::make_unique<SmartphoneFactory>(), 0.2);
    addType("laptop", std::make_unique<LaptopFactory>(), 1.5);
    addType("tshirt", std::make_unique<TShirtFactory>(), 0.3);
    addType("jacket", std::make_unique<JacketFactory>(), 0.8);
    addType("milk", std::make_unique<MilkFactory>(), 1.0);
    addType("bread", std::make_unique<BreadFactory>(), 0.5);
}

void ShopProductFactory::addType(const std::string& typeName, std::unique_ptr<ProductFactory> factory, double defaultWeight) {
    FactoryInfo info;
    info.factory = std::move(factory);
    info.defaultWeight = defaultWeight;
    factories_[typeName] = std::move(info);
}

std::unique_ptr<Product> ShopProductFactory::createProduct(const std::string& type, const std::string& name, int price, int quantity) {
    auto it = factories_.find(toLower(type));
    if (it == factories_.end()) {
        throw std::invalid_argument("Неизвестный тип товара '" + type + "'. Доступные типы: " + getTypesText());
    }
    if (price <= 0) {
        throw std::invalid_argument("Цена должна быть больше нуля");
    }
    if (quantity < 0) {
        throw std::invalid_argument("Количество не может быть отрицательным");
    }
    return it->second.factory->createProduct(name, price, quantity, it->second.defaultWeight);
}

std::string ShopProductFactory::getTypesText() const {
    std::string text;
    for (const auto& pair : factories_) {
        if (!text.empty()) {
            text += ", ";
        }
        text += pair.first;
    }
    return text;
}
