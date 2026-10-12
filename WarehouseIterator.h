#pragma once
#include <vector>
#include <memory>
#include "Product.h"

class WarehouseIterator {
  std::vector<std::unique_ptr<Product>>::iterator current_;
  std::vector<std::unique_ptr<Product>>::iterator end_;
public:
  WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator start,
    std::vector<std::unique_ptr<Product>>::iterator finish): current_(start), end_(finish) {}

  Product* operator*() const {
    return current_->get();
  }

  WarehouseIterator& operator++() {
    if (current_ != end_) {
      ++current_;
    }
    return *this;
  }

  WarehouseIterator operator++(int) {
    WarehouseIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const WarehouseIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const WarehouseIterator& other) const {
    return current_ != other.current_;
  }
};

class WarehouseConstIterator {
  std::vector<std::unique_ptr<Product>>::const_iterator current_;
  std::vector<std::unique_ptr<Product>>::const_iterator end_;
public:
  WarehouseConstIterator(std::vector<std::unique_ptr<Product>>::const_iterator start,
    std::vector<std::unique_ptr<Product>>::const_iterator finish): current_(start), end_(finish) {}

  const Product* operator*() const {
    return current_->get();
  }

  WarehouseConstIterator& operator++() {
    if (current_ != end_) {
      ++current_;
    }
    return *this;
  }

  WarehouseConstIterator operator++(int) {
    WarehouseConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const WarehouseConstIterator& other) const {
    return current_ == other.current_;
  }

  bool operator!=(const WarehouseConstIterator& other) const {
    return current_ != other.current_;
  }
};
