#include "ShopFacade.h"
#include <iostream>
#include <utility>
#include "OrderHandlers.h"
#include "ProductHandlers.h"
#include "ShowHandlers.h"


ShopFacade::ShopFacade() : orderManager_(3),mediator_(warehouses_, orderManager_, paymentSystem_, deliveryService_) {
    warehouses_.addWarehouse(10);
    warehouses_.addWarehouse(10);
    buildChain();
}

void ShopFacade::buildChain() {
    chain_ = std::make_unique<AddProductHandler>(*this);
    Handler* last = chain_.get();
    last = last->setNext(std::make_unique<ChangePriceHandler>(*this));
    last = last->setNext(std::make_unique<ChangeQuantityHandler>(*this));
    last = last->setNext(std::make_unique<MoveProductHandler>(*this));
    last = last->setNext(std::make_unique<RemoveProductHandler>(*this));
    last = last->setNext(std::make_unique<CreateOrderHandler>(*this));
    last = last->setNext(std::make_unique<CancelOrderHandler>(*this));
    last = last->setNext(std::make_unique<ConfirmPaymentHandler>(*this));
    last = last->setNext(std::make_unique<ShipOrderHandler>(*this));
    last = last->setNext(std::make_unique<ShowStatisticsHandler>(*this));
    last = last->setNext(std::make_unique<ShowProductsHandler>(*this));
    last = last->setNext(std::make_unique<ShowOrdersHandler>(*this));
    last = last->setNext(std::make_unique<ShowSettingsHandler>(*this));
    last->setNext(std::make_unique<HelpHandler>(*this));
}

int ShopFacade::addProduct(const std::string& type, const std::string& name, int price, int quantity) {
    std::unique_ptr<Product> product = productFactory_.createProduct(type, name, price, quantity);
    int productId = warehouses_.addProduct(std::move(product));
    return productId;
}

void ShopFacade::changePrice(int productId, int newPrice) {
    warehouses_.changePrice(productId, newPrice);;
}

void ShopFacade::changeQuantity(int productId, int delta) {
    warehouses_.changeQuantity(productId, delta);
}

void ShopFacade::moveProduct(int productId, int newWarehouseId) {
    warehouses_.moveProduct(productId, newWarehouseId);
}

void ShopFacade::removeProduct(int productId) {
    mediator_.onProductRemoved(productId);
    warehouses_.removeProduct(productId);
}

std::shared_ptr<Order> ShopFacade::createOrder(const std::string& customer, const std::vector<OrderItemRequest>& items,
    const std::string& deliveryType, const std::shared_ptr<Discount>& promotion) {
    return mediator_.createOrder(customer, items, deliveryType, promotion);
}

void ShopFacade::cancelOrder(int orderId) {
    mediator_.cancelOrder(orderId);
}

void ShopFacade::confirmPayment(int orderId) {
    mediator_.confirmPayment(orderId);
}

std::string ShopFacade::shipOrder(int orderId) {
    return mediator_.shipOrder(orderId);
}

std::string ShopFacade::getStatistics() const {
    return mediator_.getStatistics();
}

std::string ShopFacade::listProducts() const {
    return warehouses_.getProductsText();
}

std::string ShopFacade::listOrders() const {
    return orderManager_.getActiveOrdersText();
}

std::string ShopFacade::getSettings() const {
    return "Складов: " + std::to_string(warehouses_.getWarehousesCount()) + "\n"
        + "Лимит активных заказов на одного клиента: " + std::to_string(orderManager_.getMaxOrders()) + "\n"
        + "Способы доставки: " + deliveryService_.getDeliveryTypesText() + "\n"
        + "Активные акции: " + mediator_.getPromotionsText();
}

void ShopFacade::executeCommand(std::unique_ptr<Command> command) {
    std::string result = command->execute();
    std::cout << result << std::endl;
    history_.push(std::move(command));
}

bool ShopFacade::processInput(const std::string& input) {
    return chain_->handle(input);
}
