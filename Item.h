#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
    private:
        int BarCode;
        std::string itemName;
        double priceOfItem;
        std::string currentPromotions;
        int stockCount;

    public:
        // Constructor: use const reference for strings
        Item(int BarCode, const std::string& itemName, double priceOfItem, const std::string& currentPromotions, int stockCount);

        void displayItemInfo() const;

        // Getters
        int getBarCode() const;
        std::string getItemName() const;
        double getPrice() const;
        std::string getPromotions() const;
        int getStockCount() const;

        // Setter
        void setStockCount(int newStockCount);
};

#endif // ITEM_H
