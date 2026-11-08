#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class ProductType {
        std::string category_;
        double baseWeight_;
        int basePrice_;
        static std::unordered_map<std::string, std::shared_ptr<ProductType>> pool_;
        ProductType(std::string category, double baseWeight, int basePrice);
public:
        static std::shared_ptr<ProductType> getType(const std::string& category);
        static std::size_t getPoolSize() {return pool_.size();}

        const std::string& getCategory() const {return category_;}
        int getBasePrice()const {return basePrice_;}
        double getBaseWeight() const {return baseWeight_;}
};
