//
// Created by Пользователь on 24.09.2026.
//

#pragma once
#include <stdexcept>

class Price {
    int value_;
public:
    explicit Price(int val): value_(val) {
        if (val < 0) throw std::invalid_argument("Price must be greater than zero");
    }
    int getValue() const  {return value_ ;}
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Price must be greater than zero");
        value_= newVal;
    }
};

class Quantity {
    int value_;
public:
    explicit Quantity(int val): value_(val) {
        if (val < 0) throw std::invalid_argument("Quantity must be greater than zero");
    }
    int getValue() const  {return value_;}
    void setValue(int newVal) {
        if (newVal < 0) throw std::invalid_argument("Quantity must be greater than zero");
        value_ = newVal;
    }
    void change(int delta) {
        if (value_ + delta < 0) throw std::invalid_argument("Not enough quantity"); {}
        value_ += delta;
    }
};

class Weight {
    double value_;
public:
    explicit Weight(double val): value_(val) {
        if (val < 0) throw std::invalid_argument("Weight must be greater than zero");
    }
    double getValue() const  {return value_;}
    void setValue(double newVal) {
        if (newVal < 0) throw std::invalid_argument("Weight must be greater than zero");
        value_ = newVal;
    }
};
