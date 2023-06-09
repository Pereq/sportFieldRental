//
// Created by student on 03.06.2022.
//

#include <string>
#include "model/Rent.h"
#include "model/events/Event.h"
#include "model/Field.h"
#include "model/Client.h"
#include "model/clientTypes/ClientType.h"

Rent::Rent(int id, eventPtr event, clientPtr client, fieldPtr field, datePtr beginRentDate)
        : id(id), event(event), client(client), field(field), beginRentDate(beginRentDate) {
    if(id<1)
    {
        throw std::invalid_argument("Invalid argument ID cannot be less than 1");
    }
}

int Rent::getId() const {
    return id;
}

const datePtr &Rent::getBeginRentDate() const {
    return beginRentDate;
}

const datePtr &Rent::getEndRentDate() const {
    return endRentDate;
}

const string Rent::getEvent() const {
    return event->getEventType();
}

void Rent::setEvent(eventPtr event) {
    Rent::event = event;
}

bool Rent::isArchive() const {
    return archive;
}

void Rent::makeArchive() {
    Rent::archive = true;
}

void Rent::endRent(datePtr time) {
    if (this->isArchive()==false) {
        if (*beginRentDate>time){
            endRentDate=beginRentDate;
        }
        else{
            endRentDate = time;
        }
        makeArchive();
    }
}

const clientPtr &Rent::getClient() const {
    return client;
}

const fieldPtr &Rent::getField() const {
    return field;
}

int Rent::getRentHours() const
{
    if (isArchive())
    {
        return endRentDate->hour-beginRentDate->hour;
    }
    else
    {
        return 0;
    }
}

double Rent::getRentCost() const
{
    double result=field->getBaseCost()*getRentHours();
    double discount=0;
    discount+=client->getClientType()->getDiscount();
    discount+=event->getDiscount();
    result-=(result*discount);
    return result;
}

string Rent::getInfo() const
{
    string result="Wypożyczenie ";
    if (isArchive()) {
        result+="Zakończone\nData rozpoczęcia "+beginRentDate->getInfo()+"\nData zakonczenia "+endRentDate->getInfo();
    }
    else{
        result+="Nie zakończone\nData rozpoczęcia "+beginRentDate->getInfo();
    }
    result+="\n"+client->getInfo()+"\nWypozyczenie "+field->getInfo()+"\nWydarzenie "+event->getEventType();
    return result;
}