//
// Created by student on 16.03.2022.
//

#include "model/Client.h"
#include "model/Address.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

Client::~Client() {
//    delete address;
}

Client::Client(string fn, string ln, string id, Address *address) : firstName(fn), lastName(ln), personalID(id), address(address){}

string Client::getClientInfo() {
    return "Client: " + firstName + " " + lastName + " " + personalID + " " + address->getAddressInfo();
}

const string &Client::getFirstName() const {
    return firstName;
}

const string &Client::getLastName() const {
    return lastName;
}

const string &Client::getPersonalId() const {
    return personalID;
}

void Client::setFirstName(const string &firstName) {
    if(firstName != "")
        Client::firstName = firstName;
}

void Client::setLastName(const string &lastName) {
    if(lastName != "")
        Client::lastName = lastName;
}

Address *Client::getAddress() const {
    return address;
}

void Client::setAddress(Address *address) {
    if(address)
        Client::address = address;
};
