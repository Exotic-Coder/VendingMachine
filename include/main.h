#ifndef VENDINGMACHINE_MAIN_H
#define VENDINGMACHINE_MAIN_H

#include "../include/machine.h"
#include "../include/person.h"

//Load Inventory data from input txt file.
void loadItemData(std::string &fileName, Vending_machine &m);
//Load Person data from input txt file.
void loadPersonData(std::string &fileName, std::vector<Person> & person);
//Display Inventory
void displayItems(Vending_machine &m, std::string &currencySign);
//Allows the client or employee to select an item
bool selectItem(int & userType , Vending_machine &m, std::string &currencySign, std::string &itemSelection);
//Converts canadian dollar to us collar.
double cadToUsd(double price, double convertedPrice);
//To trim last displayed digit in our price.
double trimSecondDecimal(double convertedPrice);
//Validate user item selection
bool validateItemSelection(const std::string& itemSelection, Vending_machine & m);
//User currency selection
int selectCurrency(Vending_machine &m);
//Select Machine Type, Available Machine: NA or EU
void selectMachineType(int & machineType, std::string &currencySign);
//Choose person type access
void personType(int & userType);
//Verify person access
int validateAuth(std::vector<Person> & person);
//Find indexes of the item selected in our vector
void findItemSelected(Vending_machine &m, int &xIndex, int &yIndex, std::string &itemSelection);
//Compute calculation on item to purchase.
void calculation(Vending_machine &m, std::string &currencySign, std::string &itemSelection);
//Employee's routine
bool askCoffee(std::vector<Person> & person, Vending_machine &m);
void giveCoffee();
//Success message is sent to the terminal.
void authSuccess();
//Error message is sent to the terminal.
void authError();
//Technician operation options
int technicianRoutine(int &technicianSelection);
//Technician may reset the machine with NFC auth validation
void resetMachine(Vending_machine &m);
//Technician may activate the distributor with NFC auth validation
void activateDistributor(Vending_machine &m);
//Technician may deactivate the distributor with NFC auth validation
void deactivateDistributor(Vending_machine &m);
//Removes "\r" from a string. Compatibility with UNIX system.
std::string removeBackSlashR(std::string s);

#endif //VENDINGMACHINE_MAIN_H
