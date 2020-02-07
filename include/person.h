#include <string>
#include <vector>

#ifndef VENDINGMACHINE_PERSON_H
#define VENDINGMACHINE_PERSON_H

class Person{
private:
    std::string nfcId;
    bool auth;
public:
    Person (std::string _nfcId, bool _auth);
    bool isAuth(std::string& nfcId);
    void setAuth(bool isAuth);
    bool getAuth();
};

#endif //VENDINGMACHINE_PERSON_H