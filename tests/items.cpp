#include <iostream>
#include <iomanip>
#include <utility>
#include "include/items.h"

Inventory::Inventory(std::string _itemId, std::string _description, double _price){
    itemId = std::move(_itemId);
    description = std::move(_description);
    price = _price;
}

std::string Inventory::getItemId() {
    if (!itemId.empty() && itemId[itemId.size() - 1] == '\r')
        itemId.erase(itemId.size() - 1);
    return itemId;
}

double Inventory::getPrice() {
    return price;
}

std::string Inventory::getDescription() {
    return description;
}

void Inventory::sellItem() {
    std::cout << "Thank you for your purchase!" << std::endl;
}

void Inventory::display(std::string& currencySign){
    if (!itemId.empty() && itemId[itemId.size() - 1] == '\r')
        itemId.erase(itemId.size() - 1);
    std::cout << std::setw(6) << itemId << std::setw(2) << "|" << std::fixed << std::setprecision(2) << std::setw(2) << currencySign << price;
}

void Inventory::displayItemSelected(std::string& currencySign){
    std::cout << "Item: " << itemId << std::endl;
    std::cout << "Price: " << currencySign << price << std::endl;
    std::cout << "Description: " << description << std::endl;
}
