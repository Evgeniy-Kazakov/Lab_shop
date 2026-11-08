#include "ProductType.h"

std::unordered_map<std::string, std::shared_ptr<ProductType> > ProductType::pool_;
ProductType::ProductType(std::string category, double baseWeight, int basePrice)
    :category_(std::move(category)), baseWeight_(baseWeight), basePrice_(basePrice){}

std::shared_ptr<ProductType> ProductType::getType(const std::string& category) {
    auto it = pool_.find(category);
    if (it != pool_.end()) {
        return it->second;
    }
    double weight = 1;
    int price = 100;

    if (category == "electronics") {
        weight = 0.5;
        price = 10000;
    }
    if (category == "clothing") {
        weight = 0.3;
        price = 1000;
    }
    if (category == "food") {
        weight = 0.5;
        price = 300;
    }


    auto newType = std::shared_ptr<ProductType>(new ProductType(category, weight, price));
    pool_[category] = newType;
    return newType;
}
