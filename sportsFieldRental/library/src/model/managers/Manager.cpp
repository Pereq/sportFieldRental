//
// Created by student on 06.06.2022.
//

#include "model/managers/Manager.h"
#include "model/managers/ClientManager.h"
#include "model/managers/FieldManager.h"
#include "model/managers/RentManager.h"
#include "model/Client.h"
#include "model/Rent.h"
#include "model/Field.h"
#include "model/Address.h"
#include "model/repositories/ClientRepository.h"

Manager::Manager() {
    clientManager = make_shared<ClientManager>();
    fieldManager = make_shared<FieldManager>();
    rentManager = make_shared<RentManager>();
}

void Manager::addClient(int id, string name, string phoneNumber, string city, string street, string number, clientTypePtr clientType) {
    addressPtr address = make_shared<Address>(city, street, number);
    clientPtr client = make_shared<Client>(id, name, phoneNumber, address, clientType);
    clientManager->add(client);
}

void Manager::removeClient(string city, string street, string number) {
    clientManager->remove(city, street, number);
}

void Manager::changeClientPhoneNumber(string phoneNumber, string city, string street, string number) {
    clientManager->changePhoneNumber(phoneNumber, city, street, number);
}

void Manager::startRent(int id, eventPtr event, fieldPtr field, clientPtr client, datePtr beginRentDate) {
    rentManager->begin(id, event, field, client, beginRentDate);
}

void Manager::endRent(int id, datePtr endRentDate) {
    rentManager->end(id, endRentDate);
}

vector<rentPtr> Manager::getAllRentsForField(int fieldId) {
    return rentManager->getAllRentsForField(fieldId);
}

vector<rentPtr> Manager::getAllRentsForClient(string city, string street, string number) {
    return rentManager->getAllRentsForClient(city, street, number);
}

void Manager::addField(int id, string city, string street, string number, int tribuneCapacity, double cost) {
    addressPtr address = make_shared<Address>(city, street, number);
    fieldPtr field = make_shared<Field>(id, tribuneCapacity, cost, address);
    fieldManager->add(field);
}

void Manager::removeField(int id) {
    fieldManager->remove(id);
}

fieldPtr Manager::getFieldById(int id) {
    return fieldManager->getFieldById(id);
}

clientPtr Manager::getClientByAddress(string city, string street, string number) {
    return clientManager->getClientByAddress(city, street, number);
}

const clientManagerPtr &Manager::getClientManager() const {
    return clientManager;
}

const fieldManagerPtr &Manager::getFieldManager() const {
    return fieldManager;
}

const rentManagerPtr &Manager::getRentManager() const {
    return rentManager;
}