#include "ShowCommands.h"
#include "ShopFacade.h"

std::string ShowStatisticsCommand::execute() {
    return facade_.getStatistics();
}

std::string ShowProductsCommand::execute() {
    return facade_.listProducts();
}

std::string ShowOrdersCommand::execute() {
    return facade_.listOrders();
}

std::string ShowSettingsCommand::execute() {
    return facade_.getSettings();
}

std::string HelpCommand::execute() {
    return "Доступные команды (текст с пробелами пишите в кавычках):\n"
           "  add product <type> <name> <price> <quantity>  - добавить товар\n"
           "      type: Smartphone, Laptop, TShirt, Jacket, Milk, Bread\n"
           "  change price <id> <newPrice>                   - изменить цену (рубли без копеек)\n"
           "  change quantity <id> <delta>                   - изменить остаток (+/-)\n"
           "  move product <id> to <warehouseId>             - переместить на другой склад\n"
           "  remove product <id>                            - удалить товар\n"
           "  create order <customer> <items> <deliveryType> [<promotion>] - создать заказ\n"
           "      items: 1,2 или 1:3,2 (id или id:количество)\n"
           "      deliveryType: courier, pickup, post\n"
           "  cancel order <id>                              - отменить заказ\n"
           "  confirm payment <id>                           - подтвердить оплату\n"
           "  ship order <id>                                - отправить заказ\n"
           "  show products | show orders | show statistics | show settings\n"
           "  help                                           - этот список\n"
           "  exit                                           - выход";
}
