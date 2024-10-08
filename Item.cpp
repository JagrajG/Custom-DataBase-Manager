#include "Item.h"

Item::Item(int BarCode, const std::string &itemName, double priceOfItem, const std::string &currentPromotions, int stockCount)
{
    this->BarCode = BarCode;
    this->itemName = itemName;
    this->priceOfItem = priceOfItem;
    this->currentPromotions = currentPromotions;
    this->stockCount = stockCount;
}

void Item::displayItemInfo() const
{
    std::cout << "The price of " << itemName << " is $" << priceOfItem
              << ", it has " << currentPromotions
              << ", and the stock count is " << stockCount << std::endl;
}

int Item::getBarCode() const
{
    return BarCode;
}

std::string Item::getItemName() const
{
    return itemName;
}

double Item::getPrice() const
{
    return priceOfItem;
}

std::string Item::getPromotions() const
{
    return currentPromotions;
}

int Item::getStockCount() const
{
    return stockCount;
}

void Item::setStockCount(int newStockCount)
{
    stockCount = newStockCount;
}
