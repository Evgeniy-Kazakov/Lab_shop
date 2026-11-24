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
        DeliveryProxy.cpp
        DeliveryProxy.h
        OrderEvent.h
        OrderManager.cpp
        OrderManager.h
        Operators.cpp
        Operators.h
        StringUtils.cpp
        StringUtils.h
        ShopProductFactory.cpp
        ShopProductFactory.h
        WarehouseManager.cpp
        WarehouseManager.h
        PaymentSystem.cpp
        PaymentSystem.h
        DeliveryService.cpp
        DeliveryService.h
        ShopMediator.cpp
        ShopMediator.h
        Command.h
        CommandHistory.h
        ShopFacade.cpp
        ShopFacade.h
        ProductCommands.cpp
        ProductCommands.h
        OrderCommands.cpp
        OrderCommands.h
        ShowCommands.cpp
        ShowCommands.h
        Handler.cpp
        Handler.h
        ProductHandlers.cpp
        ProductHandlers.h
        OrderHandlers.cpp
        OrderHandlers.h
        ShowHandlers.cpp
        ShowHandlers.h)
