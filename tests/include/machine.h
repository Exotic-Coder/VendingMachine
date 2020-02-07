#include <cstddef>
#include "items.h"
#include "person.h"

#ifndef VENDINGMACHINE_MACHINE_H
#define VENDINGMACHINE_MACHINE_H

class Vending_machine{
private:
    std::string name;
    std::vector<std::string> acceptedCurrency;
    bool distributor;
    int quantitySold;
    std::vector<double> moneyOut; //Keeping track of all different currency going out of the machine.
    std::vector<double> moneyIn; //Keeping track of all different currency going in the the machine.
public:
    std::vector<std::vector<Inventory>> Items;
    Vending_machine();   // This is the constructor: declaration
    void setName(std::string name);
    std::string getName();
    void addItemSold(int quantitySold);
    int getQuantitySold();
    void initMoney(int size);
    void activateDistributor();
    void deactivateDistributor();
    bool distributorStatus();
    void resetMachine();
    void setMoneyIn(double change, int index);
    double getMoneyIn(int index);
    void setMoneyOut(double change, int index);
    double getMoneyOut(int index);
    void setAcceptedCurrency(std::string& currency);
    std::vector<std::string> getAcceptedCurrency();
    std::string getCurrentCurrency(int index);
    int getNbCurrency();
};

#endif //VENDINGMACHINE_MACHINE_H
