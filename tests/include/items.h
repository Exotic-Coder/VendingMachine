#include <string>
#include <vector>

#ifndef VENDINGMACHINE_ITEMS_H
#define VENDINGMACHINE_ITEMS_H

class Inventory {
private:
    std::string itemId;
    double price;
    std::string description;
public:
    Inventory(std::string _itemId, std::string _description, double _price);
    static void sellItem();
    std::string getItemId();
    double getPrice();
    std::string getDescription();
    void display(std::string& currencySign);
    void displayItemSelected(std::string& currencySign);
};

#endif //VENDINGMACHINE_ITEMS_H