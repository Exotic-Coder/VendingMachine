#include <string>
#include <utility>
#include <iostream>
#include "include/person.h"

Person::Person(std::string _nfcId, bool _auth){
    nfcId = std::move(_nfcId);
    auth = _auth;
}

bool Person::getAuth(){
    return auth;
}

bool Person::isAuth(std::string& nfcid) {
    //authentification check
    if(nfcId == nfcid){
        auth = true;
    }
    return auth;
}

void Person::setAuth(bool isAuth){
    auth = isAuth;
}



