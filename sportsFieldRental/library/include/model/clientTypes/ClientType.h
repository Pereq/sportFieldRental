//
// Created by student on 02.06.2022.
//

#ifndef SPORTSFIELDRENTAL_CLIENTTYPE_H
#define SPORTSFIELDRENTAL_CLIENTTYPE_H
#include <string>

using std::string;

class ClientType {
private:
    double discount = 0;
public:
    virtual string getType() = 0;
    virtual double getDiscount();
    virtual string getLeague();
    virtual string getInfo() = 0;
    virtual string getInfoForWriteToFile() = 0;
};


#endif //SPORTSFIELDRENTAL_CLIENTTYPE_H
