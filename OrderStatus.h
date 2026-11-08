#pragma once
#include <string>

enum class OrderStatus {
    Pending, Paid, Shipped, Delivered, Cancelled
};
inline std::string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending: return "pending";
        case OrderStatus::Paid: return "paid";
        case OrderStatus::Shipped: return "shipped";
        case OrderStatus::Delivered: return "delivered";
        case OrderStatus::Cancelled: return "cancelled";
    }
    return "unknown";
}
