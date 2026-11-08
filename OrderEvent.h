#pragma once
#include <vector>
#include <algorithm>
#include <ctime>
#include "OrderStatus.h"

struct OrderEvent {
    int orderId;
    OrderStatus oldStatus;
    OrderStatus newStatus;
    std::time_t timeStamp;
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onOrderEvent(const OrderEvent& event) = 0;
};

class IObservable {
  std::vector<IObserver*> observers_;
public:
    virtual ~IObservable() = default;
    void subscribe(IObserver* observer) {
        if (observer == nullptr) {
            return;
        }
        if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
            observers_.push_back(observer);
        }
    }
    void unsubscribe(IObserver* observer) {
        auto it = std::find(observers_.begin(), observers_.end(), observer);
        if (it != observers_.end()) {
            observers_.erase(it);
        }
    }
    void notify(const OrderEvent& event) {
        for (IObserver* observer : observers_) {
            observer->onOrderEvent(event);
        }
    }
};
