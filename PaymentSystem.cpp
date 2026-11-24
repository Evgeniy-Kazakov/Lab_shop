#include "PaymentSystem.h"
#include <stdexcept>
#include "StringUtils.h"

double& PaymentSystem::getAccount(const std::string& customer) {
    auto it = balances_.find(customer);
    if (it == balances_.end()) {
        it = balances_.emplace(customer, startBalance_).first;
    }
    return it->second;
}

void PaymentSystem::processPayment(const std::string& customer, double amount) {
    double& balance = getAccount(customer);
    if (balance < amount) {
        throw std::runtime_error("Недостаточно средств у клиента " + customer + ": на счёте "
            + formatMoney(balance) + ", нужно " + formatMoney(amount));
    }
    balance -= amount;
}

void PaymentSystem::refund(const std::string& customer, double amount) {
    getAccount(customer) += amount;
}

double PaymentSystem::checkBalance(const std::string& customer) {
    return getAccount(customer);
}
