#include <iostream>
#include <string>
#include <iomanip>
#include <utility>
#include "include/machine.h"

Vending_machine::Vending_machine() {
    distributor = true;
    name = "";
    quantitySold = 0;
    acceptedCurrency.clear();
    moneyIn.clear();
    moneyOut.clear();
}

void Vending_machine::setName(std::string _name){
    name = std::move(_name);
}

std::string Vending_machine::getName(){
	return name;
}

double Vending_machine::getMoneyIn(int index){
	return moneyIn[index];
}

double Vending_machine::getMoneyOut(int index){
	return moneyOut[index];
}

bool Vending_machine::distributorStatus(){
    return distributor;
}

void Vending_machine::setAcceptedCurrency(std::string& currency){
    acceptedCurrency.push_back(currency);
}

void Vending_machine::initMoney(int size){
    moneyIn.resize(size);
    moneyOut.resize(size);
}

void::Vending_machine::activateDistributor() {
    distributor = true;
}

void::Vending_machine::deactivateDistributor() {
    distributor = false;
}

std::vector<std::string> Vending_machine::getAcceptedCurrency(){
    return acceptedCurrency;
}

void Vending_machine::setMoneyIn(double change, int index) {
    moneyIn[index] += change;
}

void Vending_machine::setMoneyOut(double change, int index) {
    moneyOut[index] += change;
}

int Vending_machine::getNbCurrency(){
    return acceptedCurrency.size();
}

std::string Vending_machine::getCurrentCurrency(int index){
    return acceptedCurrency[index];
}

void Vending_machine::addItemSold(int nbOfItem) {
    quantitySold += nbOfItem;
}

int Vending_machine::getQuantitySold(){
	return quantitySold;
}

void Vending_machine::resetMachine() {
    int size = 0;
    size = moneyIn.size();
    distributor = true;
    for (int i = 0; i < size; ++i) {
        moneyIn[i] = 0;
        moneyOut[i] = 0;
    }
    quantitySold = 0;
}