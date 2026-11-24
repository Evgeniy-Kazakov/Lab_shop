#include "WarehouseManager.h"
#include <stdexcept>
#include <utility>

int WarehouseManager::addWarehouse(std::size_t maxSize) {
    warehouses_.push_back(std::make_unique<Warehouse>(maxSize));
    return static_cast<int>(warehouses_.size());
}

Warehouse& WarehouseManager::getWarehouse(int warehouseId) {
    if (warehouseId < 1 || warehouseId > static_cast<int>(warehouses_.size())) {
        throw std::invalid_argument("Склад №" + std::to_string(warehouseId) + " не найден");
    }
    return *(warehouses_[warehouseId - 1]);
}

int WarehouseManager::addProduct(std::unique_ptr<Product> product) {
    if (!product) {
        throw std::invalid_argument("Товар не создан");
    }
    int productId = product->getId();
    for (auto& warehouse : warehouses_) {
        if (warehouse->canAdd(productId)) {
            warehouse->addProduct(std::move(product));
            return productId;
        }
    }
    throw std::runtime_error("Все склады заполнены");
}

Product* WarehouseManager::findProduct(int productId) {
    for (auto& warehouse : warehouses_) {
        Product* product = warehouse->findById(productId);
        if (product) {
            return product;
        }
    }
    return nullptr;
}

void WarehouseManager::removeProduct(int productId) {
    Product* product = findProduct(productId);
    if (!product) {
        throw std::invalid_argument("Товар №" + std::to_string(productId) + " не найден");
    }
    product->getWarehouse()->removeById(productId);
}

void WarehouseManager::changePrice(int productId, int newPrice) {
    Product* product = findProduct(productId);
    if (!product) {
        throw std::invalid_argument("Товар №" + std::to_string(productId) + " не найден");
    }
    if (newPrice <= 0) {
        throw std::invalid_argument("Цена должна быть больше нуля");
    }
    product->setPrice(Price(newPrice));
}

void WarehouseManager::changeQuantity(int productId, int delta) {
    Product* product = findProduct(productId);
    if (!product) {
        throw std::invalid_argument("Товар №" + std::to_string(productId) + " не найден");
    }
    int current = product->getQuantity().getValue();
    if (current + delta < 0) {
        throw std::invalid_argument("Остаток не может стать отрицательным (сейчас " + std::to_string(current) + ")");
    }
    product->changeQuantity(delta);
}

void WarehouseManager::moveProduct(int productId, int newWarehouseId) {
    Product* product = findProduct(productId);
    if (!product) {
        throw std::invalid_argument("Товар №" + std::to_string(productId) + " не найден");
    }
    Warehouse& target = getWarehouse(newWarehouseId);
    if (product->getWarehouse() == &target) {
        throw std::logic_error("Товар уже находится на складе №" + std::to_string(newWarehouseId));
    }
    if (!product->transferTo(target)) {
        throw std::runtime_error("Не удалось переместить товар: на складе №" + std::to_string(newWarehouseId) + " нет места");
    }
}

std::string WarehouseManager::getProductsText() const {
    std::string text;
    for (std::size_t i = 0; i < warehouses_.size(); i++) {
        if (!text.empty()) {
            text += "\n";
        }
        text += "Склад №" + std::to_string(i + 1) + ":";
        bool isEmpty = true;
        for (Product* product : *(warehouses_[i])) {
            isEmpty = false;
            text += "\n  №" + std::to_string(product->getId()) + " " + product->getName()
                 + " | цена: " + std::to_string(product->getPrice().getValue())
                 + " | остаток: " + std::to_string(product->getQuantity().getValue());
        }
        if (isEmpty) {
            text += " пусто";
        }
    }
    return text;
}

std::string WarehouseManager::getLoadText() const {
    std::string text;
    for (std::size_t i = 0; i < warehouses_.size(); i++) {
        if (i > 0) {
            text += "\n";
        }
        std::size_t current = warehouses_[i]->getCurrentSize();
        std::size_t maxSize = warehouses_[i]->getMaxSize();
        text += "  Склад №" + std::to_string(i + 1) + ": " + std::to_string(current)
             + " из " + std::to_string(maxSize) + " позиций ( склад заполнен на" + std::to_string(current * 100 / maxSize) + "%)";
    }
    return text;
}
