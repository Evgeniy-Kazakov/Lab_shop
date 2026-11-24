#pragma once
#include <map>
#include <string>

class PaymentSystem {
    std::map<std::string, double> balances_;
    double startBalance_ = 1000000;
    double& getAccount(const std::string& customer);
public:
    void processPayment(const std::string& customer, double amount);
    void refund(const std::string& customer, double amount);
    double checkBalance(const std::string& customer);
};
