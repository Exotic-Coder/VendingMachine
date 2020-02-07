#include <iostream>
#include <limits>
#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cfloat>
#include "../include/main.h"
#include "../include/machine.h"
#include "../include/person.h"
#include "../include/items.h"

#define YES 1
#define NO 2

//main routine
int main() {
    Vending_machine mNa;
    Vending_machine mEu;
    std::vector<Person> emp;
    std::vector<Person> tech;
    MachineState currentState = INIT;

    int restart = 0;
    int userType = 0;
    int inputQuit = 0;
    int machineType = 0;
    int technicianSelection = 0;
    bool isCoffee;
    bool isBuy = false;
    bool isAuth = false;
    bool isFirstUse = false;
    std::string item;
    std::string fileName;
    std::string currencySign;
    std::string itemSelection;
    std::string fileNameEmp = "employee.txt";
    std::string fileNameTech = "technician.txt";
    std::string fileNameMachineNA = "machineNA.txt";
    std::string fileNameMachineEU = "machineEU.txt";

    do {
        switch (currentState) {
            case INIT:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : INIT                          |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;

                loadPersonData(fileNameEmp, emp);
                loadPersonData(fileNameTech, tech);
                loadItemData(fileNameMachineNA, mNa);
                loadItemData(fileNameMachineEU, mEu);
                mNa.setName("DISTRIBUTOR NA");
                mEu.setName("DISTRIBUTOR EU");

                isFirstUse = true;
                currentState = START;
                break;
            case START:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : START                         |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                selectMachineType(machineType, currencySign);
                currentState = ACCESS;
                break;
            case ACCESS:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : ACCESS                        |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                personType(userType);
                if (userType == 1) {
                    currentState = TECHNICIAN;
                }
                else if (userType == 2) {
                    currentState = EMPLOYEE;
                }
                else if (userType == 3) {
                    currentState = SELECT;
                }
                break;
            case SELECT:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : SELECT                        |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1) {
                    isBuy = selectItem(userType, mEu, currencySign, itemSelection);
                }
                else if (machineType == 2) {
                    isBuy = selectItem(userType, mNa, currencySign, itemSelection);
                }
                if (isBuy) {
                    currentState = CALCULATE;
                }
                else {
                    currentState = START;
                }
                break;
            case CALCULATE:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : CALCULATE                     |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1)
                    calculation(mEu, currencySign, itemSelection);
                else if (machineType == 2) {
                    calculation(mNa, currencySign, itemSelection);
                }
                currentState = START;
                break;
            case EMPLOYEE:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : EMPLOYEE                      |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1)
                    isCoffee = askCoffee(emp, mEu);
                if (machineType == 2)
                    isCoffee = askCoffee(emp, mNa);
                if (isCoffee) {
                    currentState = VALIDATE;
                }
                else {
                    currentState = SELECT;
                }
                break;
            case TECHNICIAN:
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : TECHNICIAN                    |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;

                if (!technicianSelection) {
                    technicianRoutine(technicianSelection);
                    isAuth = false;
                }

                if (isAuth) {
                    if (technicianSelection == 1) {
                        currentState = RESET;
                        technicianSelection = 0;
                        isAuth = false;
                    }
                    else if (technicianSelection == 2) {
                        currentState = ACTIVATE;
                        technicianSelection = 0;
                        isAuth = false;
                    }
                    else if (technicianSelection == 3) {
                        currentState = DEACTIVATE;
                        technicianSelection = 0;
                        isAuth = false;
                    }
                }
                else if (technicianSelection == 4) {
                    technicianSelection = 0;
                    currentState = START;
                }
                else {
                    currentState = VALIDATE;
                }
                break;
            case VALIDATE:
                std::cout << std::endl;
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : VALIDATE                      |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (userType == 1) {
                    isAuth = validateAuth(tech);
                    if (isAuth) {
                        currentState = TECHNICIAN;
                    }
                }
                else if (userType == 2) {
                    isAuth = validateAuth(emp);
                    if (isAuth) {
                        giveCoffee();
                        currentState = SELECT;
                    }
                }
                if (!isAuth) {
                    currentState = START;
                }
                break;
            case ACTIVATE:
                std::cout << std::endl;
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : ACTIVATE                      |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1) {
                    activateDistributor(mEu);
                }
                else if (machineType == 2) {
                    activateDistributor(mNa);
                }
                currentState = TECHNICIAN;
                break;
            case DEACTIVATE:
                std::cout << std::endl;
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : DEACTIVATE                    |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1) {
                    deactivateDistributor(mEu);
                }
                else if (machineType == 2) {
                    deactivateDistributor(mNa);
                }
                currentState = TECHNICIAN;
                break;
            case RESET:
                std::cout << std::endl;
                std::cout << "-----------------------------------------------------------------------  \n";
                std::cout << "|                       CURRENT STATE : RESET                         |  \n";
                std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
                if (machineType == 1) {
                    resetMachine(mEu);
                }
                else if (machineType == 2) {
                    resetMachine(mNa);
                }
                currentState = TECHNICIAN;
                break;
            default:
                std::cout << "ERROR! INVALID" << std::endl;
        }
        if (currentState == START && !isFirstUse) {
            std::cout << std::endl;
            std::cout << "****************** Do you want to close the program ? *****************  \n" << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                   YES (1)                  NO (2)                   |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;
            do {
                std::cin >> inputQuit;
                if (std::cin.fail() || (inputQuit != YES && inputQuit != NO)) {
                    std::cout << "invalid selection!" << std::endl;
                    std::cout << "Please try again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                }
            } while (inputQuit != YES && inputQuit != NO);
        }
        isFirstUse = false;
    } while (inputQuit != YES);
}

bool askCoffee(std::vector<Person>& person, Vending_machine& m) {
    int employeeInput = 0;
    bool isFreeCoffee = false;

    if (m.distributorStatus()) {

        std::cout << std::endl;
        std::cout << "******************* Do you want a free coffee *************************  \n" << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|                 YES (1)                  NO (2)                     |  \n";
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << std::endl;

        do {
            std::cin >> employeeInput;

            if (std::cin.fail() || (employeeInput != YES && employeeInput != NO)) {
                std::cout << "invalid selection!" << std::endl;
                std::cout << "Please try again." << std::endl;

                std::cin.clear();

                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }

        } while (employeeInput != YES && employeeInput != NO);

        if (employeeInput == YES) {
            isFreeCoffee = true;
        }
        return isFreeCoffee;
    }
    else {
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|            Please try again later. " << m.getName() << " is inactive.       |  \n";
        std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
        std::cout << std::endl;

        return false;
    }
}

void giveCoffee() {
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                       Enjoy your free coffee!                       |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;
}

void selectMachineType(int& machineType, std::string& currencySign) {
    std::cout << std::endl;
    std::cout << "**************** Please select a distributor to continue **************  \n" << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|          Distributor EU (1)             Distributor NA (2)          |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;

    do {
        std::cin >> machineType;

        if (std::cin.fail() || (machineType != 1 && machineType != 2))
        {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

    } while (machineType != 1 && machineType != 2);

    if (machineType == 1) {
#ifdef WIN32
        currencySign = char(128);
#else
        currencySign = "€";
#endif

    }
    if (machineType == 2) {
        currencySign = "$";
    }
}

void loadItemData(std::string& fileName, Vending_machine& m) {
    std::string description;
    std::string itemId;
    std::string machineName;
    double price = 0;
    std::string money;
    int index = 0;
    int row = 0;
    int itemRow = 0;
    int q = 0;
    double p = 0;

    std::string path = "data/";
    std::string line = "";
    std::ifstream in;

    in.open(path + fileName, std::ios::in);

    if (!in) {
        perror("File error: ");
        exit(EXIT_FAILURE);
    }

    in >> row >> itemRow;

    // discards the input buffer
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    m.Items.resize(row);

    getline(in, line);

    std::stringstream ss(line);

    while (ss >> money)
    {
        money = removeBackSlashR(money);
        m.setAcceptedCurrency(money);
        ++index;
    }

    m.initMoney(index);

    for (int j = 0; j < row; ++j) {
        for (int i = 0; i < itemRow; ++i) {
            getline(in, line);
            line = removeBackSlashR(line);
            itemId = line;
            getline(in, line);
            line = removeBackSlashR(line);
            description = line;
            getline(in, line);
            p = stod(line);
            price = p;

            m.Items[j].push_back(Inventory(itemId, description, price));
        }
    }
    in.close();
}

void loadPersonData(std::string& fileName, std::vector<Person>& person) {
    int i = 0;
    std::string path = "data/";
    std::string line;
    std::string nfcId;
    bool isAuth = false;
    int nbOfPerson = 0;

    std::ifstream in;
    // Opening file in input mode
    in.open(path + fileName, std::ios::in);

    if (!in) {
        // discards the input buffer
        perror("File error: ");
        exit(EXIT_FAILURE);
    }

    in >> nbOfPerson;
    // discards the input buffer
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < nbOfPerson; ++i) {
        getline(in, line);
        line = removeBackSlashR(line);
        nfcId = line;
        person.push_back(Person(nfcId, isAuth));
    }
    in.close();
}

void personType(int& userType) {
    std::cout << std::endl;
    std::cout << "*************** Please select an option to continue *******************  \n" << std::endl;;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|        Technician (1)        Employee (2)        Client (3)         |  \n";
    std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
    std::cout << std::endl;

    do {
        std::cin >> userType;

        if (std::cin.fail() || (userType != 1 && userType != 2 && userType != 3))
        {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (userType != 1 && userType != 2 && userType != 3);
}

void displayItems(Vending_machine& m, std::string& currencySign) {
    int nbOfRow;
    int itemPerRow;
    nbOfRow = m.Items.size();
    itemPerRow = m.Items[0].size();

    for (int i = 0; i < nbOfRow; ++i) {
        for (int j = 0; j < itemPerRow; ++j) {
            m.Items[i][j].display(currencySign);
        }
        std::cout << std::endl;
    }
}

bool selectItem(int& userType, Vending_machine& m, std::string& currencySign, std::string& itemSelection) {
    bool validSelection = false;
    int input = 0;

    if (m.distributorStatus()) {

        std::cout << std::endl;
        std::cout << "****************** Do you want to purchase an item ? ******************  \n" << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|                   YES (1)                  NO (2)                   |  \n";
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << std::endl;

        do {
            std::cin >> input;

            if (std::cin.fail() || (input != YES && input != NO)) {
                std::cout << "invalid selection!" << std::endl;
                std::cout << "Please try again." << std::endl;

                std::cin.clear();

                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }
        } while (input != YES && input != NO);


        if (input == YES) {

            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Please select an item.                        |  \n";
            std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
            std::cout << std::endl;

            displayItems(m, currencySign);

            std::cout << std::endl;

            do {
                std::cin >> itemSelection;

                validSelection = validateItemSelection(itemSelection, m);

                if (std::cin.fail() || !validSelection) {
                    std::cout << "invalid selection!" << std::endl;
                    std::cout << "Please try again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                }
            } while (!validSelection);
            return true;
        }
        return false;
    }
    else {
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|            Please try again later. " << m.getName() << " is inactive.          |  \n";
        std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
        std::cout << std::endl;

        return false;
    }
}

void calculation(Vending_machine& m, std::string& currencySign, std::string& itemSelection) {
    int xIndex = 0;
    int yIndex = 0;
    int amountToBuy = 0;
    int money = 0;
    std::string name;
    std::string currency;
    double convertedPrice = 0;
    double returnedChange = 0;
    double price = 0.0;
    double change = 0;
    int index = 0;

    index = selectCurrency(m);

    findItemSelected(m, xIndex, yIndex, itemSelection);

    price = m.Items[yIndex][xIndex].getPrice();

    currency = m.getCurrentCurrency(index);

    if (currency == "USD") { //we are dealing with USD
        convertedPrice = cadToUsd(price, convertedPrice);
        convertedPrice = trimSecondDecimal(convertedPrice);
        price = convertedPrice;
    }

    m.Items[yIndex][xIndex].displayItemSelected(currencySign);
    std::cout << std::endl;
    std::cout << "How many do you want ?" << std::endl;

    std::cin >> amountToBuy;

    price *= amountToBuy;

    std::cout << std::endl;
    std::cout << "The total cost is " << currencySign << std::fixed << std::setprecision(2) << price << " " << currency << std::endl;
    std::cout << std::endl;
    std::cout << "Please select an option to pay." << std::endl;
    std::cout << std::endl;

    std::cout << "1. 5 CENTS" << std::endl;
    std::cout << "2. 10 CENTS" << std::endl;
    std::cout << "3. 25 CENTS" << std::endl;
    std::cout << "4. 50 CENTS" << std::endl;
    std::cout << "5. 1 DOLLAR" << std::endl;
    std::cout << "6. 2 DOLLARS" << std::endl;
    std::cout << std::endl;

    while (price > DBL_MIN) {
        do {
            std::cin >> money;

            if (std::cin.fail() || money != 1 && money != 2 && money != 3 && money != 4 && money != 5 && money != 6)
            {
                std::cout << "invalid selection!" << std::endl;
                std::cout << "Please try again." << std::endl;
                std::cin.clear();

                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }
        } while (money != 1 && money != 2 && money != 3 && money != 4 && money != 5 && money != 6);

        switch (money) {
            case 1:
                change = 0.05;
                break;
            case 2:
                change = 0.10;
                break;
            case 3:
                change = 0.25;
                break;
            case 4:
                change = 0.50;
                break;
            case 5:
                change = 1.00;
                break;
            case 6:
                change = 2.00;
                break;
            default:
                break;
        }
        price -= change;
        m.setMoneyIn(change, index);
        if (price > DBL_MIN)
            std::cout << "Remaining to pay: " << currencySign <<  std::fixed << std::setprecision(2) << price << std::endl;
    }
    returnedChange = std::abs(price);

    std::cout << std::endl;
    std::cout << "Thank you for your purchase." << std::endl;
    if (returnedChange > 0.01)
        std::cout << "Your change: " << currencySign << std::fixed << std::setprecision(2)  << returnedChange << std::endl;

    m.setMoneyOut(returnedChange, index);
    m.addItemSold(amountToBuy);
    std::cout << std::endl;
}

void findItemSelected(Vending_machine& m, int& xIndex, int& yIndex, std::string& itemSelection) {
    int nbRow = m.Items.size();
    int itemPerRow = m.Items[0].size();

    for (int i = 0; i < nbRow; ++i) {
        for (int j = 0; j < itemPerRow; ++j) {
            if (itemSelection == m.Items[i][j].getItemId()) {
                xIndex = j;
                yIndex = i;
                break;
            }
        }
    }

}

double cadToUsd(double price, double convertedPrice) {
    double rate = 1.3;
    convertedPrice = price * rate;
    return convertedPrice;
}

double trimSecondDecimal(double convertedPrice) {
    int tempPrice = 0;

    tempPrice = convertedPrice * 10;
    convertedPrice = (double)tempPrice / 10;

    return convertedPrice;
}

bool validateItemSelection(const std::string& itemSelection, Vending_machine& m) {
    int nbOfRow = m.Items.size();
    int itemPerRow = m.Items[0].size();

    for (int i = 0; i < nbOfRow; ++i) {
        for (int j = 0; j < itemPerRow; ++j) {
            if (itemSelection == m.Items[i][j].getItemId())
                return true;
        }
    }
    return false;
}

int selectCurrency(Vending_machine& m) {
    std::string name;
    std::string selectedCurrency;
    int currencyIndex;
    std::vector<std::string> currency;
    int nbOfCurrency = 0;
    nbOfCurrency = m.getNbCurrency();
    currency.resize(nbOfCurrency);
    currency = m.getAcceptedCurrency();

    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                       Please select a currency.                     |  \n";
    std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < currency.size(); ++i) {
        if (i == 0) {
            std::cout << i + 1 << ". " << currency[i] << " [DEFAULT]" << std::endl;
            selectedCurrency = currency[i];
        }
        else {
            std::cout << i + 1 << ". " << currency[i] << std::endl;
            selectedCurrency = currency[i];
        }
    }

    std::cout << std::endl;

    do {
        std::cin >> currencyIndex;

        if (std::cin.fail() || currencyIndex < 1 || currencyIndex > nbOfCurrency)
        {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (currencyIndex < 1 || currencyIndex > nbOfCurrency);

    return currencyIndex - 1;
}

int validateAuth(std::vector<Person>& person) {
    int attempt = 3;
    std::string userInputNfc;
    int nbOfPerson = 0;
    int auth = 0;
    int index = 0;

    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                       Please authenticate yourself.                 |  \n";
    std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
    std::cout << std::endl;

    while (attempt != 0) {
        std::cout << "Please enter your NFC ID" << std::endl;
        std::cin >> userInputNfc;
        nbOfPerson = person.size();
        for (int i = 0; i < nbOfPerson; ++i) {
            auth = person[i].isAuth(userInputNfc);
            if (auth) {
                person[i].setAuth(auth);
                index = i;
                break;
            }
        }
        if (!auth) {
            --attempt;
            std::cout << "Attempt remaining: " << attempt << std::endl;
        }
        else {
            person[index].setAuth(auth);
            break;
        }
    }

    if (auth) {
        authSuccess();
    }
    else {
        authError();
    }

    return auth;
}

int technicianRoutine(int& technicianSelection) {
    std::cout << std::endl;
    std::cout << "****************** Please select an option to continue ****************  \n" << std::endl;;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|    RESET (1)      ACTIVATE (2)      DEACTIVATE (3)      QUIT (4)    |  \n";
    std::cout << "-----------------------------------------------------------------------  \n" << std::endl;
    std::cout << std::endl;

    do {
        std::cin >> technicianSelection;

        if (std::cin.fail() || (technicianSelection != 1 && technicianSelection != 2 && technicianSelection != 3 && technicianSelection != 4))
        {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (technicianSelection != 1 && technicianSelection != 2 && technicianSelection != 3 && technicianSelection != 4);

    return technicianSelection;
}

void deactivateDistributor(Vending_machine &m) {
    int input = 0;

    std::cout << std::endl;
    std::cout << "************* Do you want to to deactivate the distributor ? **********  \n" << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                   YES (1)                  NO (2)                   |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;

    do {
        std::cin >> input;

        if (std::cin.fail() || (input != YES && input != NO)) {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (input != YES && input != NO);

    if (input == 1) {
        if (m.distributorStatus()) {
            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Dectivation process has started.              |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;

            m.deactivateDistributor();

            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Distributor is Deactivated.                   |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;
        }
        else {
            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Distributor is already Deactivated.           |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;
        }
    }
}

void activateDistributor(Vending_machine& m) {
    int input = 0;

    std::cout << std::endl;
    std::cout << "************* Do you want to to activate the distributor ? ************  \n" << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                   YES (1)                  NO (2)                   |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;

    do {
        std::cin >> input;

        if (std::cin.fail() || (input != YES && input != NO)) {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (input != YES && input != NO);

    if (input == YES) {
        if (!m.distributorStatus()) {
            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Activation process has started.             |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;

            m.activateDistributor();

            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Distributor is Activated.                     |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;
        }
        else {
            std::cout << std::endl;
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << "|                       Distributor is already Activated.             |  \n";
            std::cout << "-----------------------------------------------------------------------  \n";
            std::cout << std::endl;
        }
    }
}

void resetMachine(Vending_machine& m) {
    int input = 0;

    m.displayMachineInfo();

    std::cout << std::endl;
    std::cout << "**************** Do you want to to reset the machine ? ****************  \n" << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                   YES (1)                  NO (2)                   |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;

    do {
        std::cin >> input;

        if (std::cin.fail() || (input != YES && input != NO)) {
            std::cout << "invalid selection!" << std::endl;
            std::cout << "Please try again." << std::endl;

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    } while (input != 1 && input != 2);

    if (input == 1) {
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|                       Reset process has started.                    |  \n";
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << std::endl;

        m.resetMachine();

        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << "|                       Reset completed.                              |  \n";
        std::cout << "-----------------------------------------------------------------------  \n";
        std::cout << std::endl;

        m.displayMachineInfo();

        std::cout << std::endl;
    }
}

void authError() {
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                       Authentication Failed.                        |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;
}

void authSuccess() {
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << "|                       Authentication Success.                       |  \n";
    std::cout << "-----------------------------------------------------------------------  \n";
    std::cout << std::endl;
}

std::string removeBackSlashR(std::string s){
    if (!s.empty() && s[s.size() - 1] == '\r')
        s.erase(s.size() - 1);
    return s;
}