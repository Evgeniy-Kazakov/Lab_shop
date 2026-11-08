#pragma once
#include <memory>
#include <ostream>
#include "Order.h"
#include "Delivery.h"
#include "Discount.h"

Order&  operator+(Order& order, const Discount& discount);
bool operator<<(const std::shared_ptr<Delivery>& delivery, Order& order);
std::ostream& operator<<(std::ostream& os, const Order& order);
