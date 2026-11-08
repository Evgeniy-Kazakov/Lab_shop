cmake_minimum_required(VERSION 4.3)
project(Lab_shop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_executable(Lab_shop main.cpp
        Attributes.h
        Product.cpp
        Product.h
        Warehouse.cpp
        Warehouse.h
        ProductFactory.h
        WarehouseIterator.h
        ProductType.cpp
        ProductType.h
        Order.cpp
        Order.h
        OrderStatus.h
        Delivery.cpp
        Delivery.h
        Discount.cpp
        Discount.h
        DeliveyProxy.cpp
        DeliveyProxy.h
        OrderEvent.h
        OrderManager.cpp
        OrderManager.h
        Operators.cpp
        Operators.h)
