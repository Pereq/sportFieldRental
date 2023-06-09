#include <iostream>
#include "typedefs.h"
#include "model/managers/Manager.h"
#include "model/managers/ClientManager.h"
#include "model/repositories/ClientRepository.h"
#include "model/clientTypes/School.h"
#include "model/clientTypes/LeagueA.h"
#include "model/clientTypes/LeagueB.h"
#include "model/clientTypes/LeagueC.h"
#include "model/clientTypes/LeagueD.h"
#include "model/clientTypes/Club.h"
#include "model/managers/FieldManager.h"
#include "model/repositories/FieldRepository.h"
#include "model/repositories/RentRepository.h"
#include "model/managers/RentManager.h"
#include "model/Field.h"
#include "model/events/Training.h"
#include "model/events/Tournament.h"
#include "model/events/FriendlyMatch.h"
#include "model/Date.h"
#include "model/Client.h"
#include "model/Rent.h"

using namespace std;

datePtr getDate() {
    int year, month, day, hour, minute;
    cout << "Prosze podac rok: "; cin >> year;
    cout << "Prosze podac miesiac: "; cin >> month;
    cout << "Prosze podac dzien: "; cin >> day;
    cout << "Prosze podac godzine: "; cin >> hour;
    cout << "Prosze podac minute: "; cin >> minute;
    datePtr date = make_shared<Date>(year, month, day, hour, minute);
    return date;
}

void addClient(Manager *manager, string city, string street, string number) {
    int id = manager->getClientManager()->getClientRepository()->getClients().size() + 1;
    string phoneNumber, name;
    cout << "Prosze podac nazwe: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, name);
    int type, league;
    cout << "Prosze podac numer telefonu: "; cin >> phoneNumber;
    cout << "Prosze podac typ(1-Szkola, 2-Klub): "; cin >> type;
    if(type == 2) {
        cout << "Prosze podac lige(1-Liga A, 2-Liga B, 3-Liga C, 4-Liga D): "; cin >> league;
        if(league == 1) {
            leaguePtr league1  = make_shared<LeagueA>();
            clientTypePtr type1 = make_shared<Club>(league1);
            try {
                manager->addClient(id, name, phoneNumber, city, street, number, type1);
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
        } else if(league == 2) {
            leaguePtr league1  = make_shared<LeagueB>();
            clientTypePtr type1 = make_shared<Club>(league1);
            try{
                manager->addClient(id, name, phoneNumber, city, street, number, type1);
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
        } else if(league == 3) {
            leaguePtr league1  = make_shared<LeagueC>();
            clientTypePtr type1 = make_shared<Club>(league1);
            try{
                manager->addClient(id, name, phoneNumber, city, street, number, type1);
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
        } else if(league == 4) {
            leaguePtr league1  = make_shared<LeagueD>();
            clientTypePtr type1 = make_shared<Club>(league1);
            try {
                manager->addClient(id, name, phoneNumber, city, street, number, type1);
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
        } else {
            cout << "Nie ma takiej opcji!" << endl;
            cout << "Nie udalo sie dodac klienta!" << endl;
        }
    } else if(type == 1) {
        clientTypePtr type1 = make_shared<School>();
        manager->addClient(id, name, phoneNumber, city, street, number, type1);
        cout<<"Pomyslnie dodano klienta"<<endl;
    } else {
        cout << "Nie ma takiej opcji!" << endl;
        cout << "Nie udalo sie dodac klienta" << endl;
    }
}

void registerClient(Manager *manager) {
    string city, street, number;
    cout << "Miasto: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, city);
    cout << "Ulica: "; getline(cin, street);
    cout << "Numer domu: "; cin >> number;
    addClient(manager, city, street, number);
}

void addField(Manager *manager) {
    unsigned int id = manager->getFieldManager()->getFieldRepository()->getFields().size() + 1;
    int tribuneCapacity;
    double cost;
    string city, street, number;
    cout << "Prosze podac adres." << endl;
    cout << "Miasto: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, city);
    cout << "Ulica: "; getline(cin, street);
    cout << "Numer domu: "; getline(cin, number);
    cout << "Pojemnosc trybun: "; cin >> tribuneCapacity;
    cout << "Koszt za godzine: "; cin >> cost;
    try {
        manager->addField(id, city, street, number, tribuneCapacity, cost);
    }
    catch(std::invalid_argument& e){
        cerr<<e.what()<<endl;
    };
    cout<<"Pomyslnie dodano boisko"<<endl;
}

void startRent(Manager *manager) {
    int id = manager->getRentManager()->getRentRepository()->getRents().size() +
             manager->getRentManager()->getRentRepository()->getArchiveRents().size() + 1;
    int fieldId, eventId;
    string city, street, number;
    cout << "Prosze podac swoj adres." << endl;
    cout << "Miasto: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, city);
    cout << "Ulica: "; getline(cin, street);
    cout << "Numer domu: "; cin >> number;
    clientPtr cl = manager->getClientManager()->getClientByAddress(city, street, number);
    if(cl == nullptr) {
        addClient(manager, city, street, number);
        cl = manager->getClientManager()->getClientByAddress(city, street, number);
    }
    if(manager->getFieldManager()->getFieldRepository()->getFields().size()==0)
    {
        cout<<"Brak dostepnych boisk"<<endl;
        return;
    }
    for(auto field : manager->getFieldManager()->getFieldRepository()->getFields()) {
        cout << field->getInfo() << endl;
    }
    cout << "Prosze wybrac boisko: "; cin >> fieldId;
    fieldPtr field = manager->getFieldById(fieldId);
    cout << "Prosze podac do czego zostanie wykorzystane boisko(1-Trening, 2-Turniej, 3-Mecz towarzyski): "; cin >> eventId;
    eventPtr ev;
    switch (eventId) {
        case 1:
            ev = make_shared<Training>();
            try {
                manager->startRent(id, ev, field, cl, getDate());
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
            break;
        case 2:
            ev = make_shared<Tournament>();
            try {
                manager->startRent(id, ev, field, cl, getDate());
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
            break;
        case 3:
            ev = make_shared<FriendlyMatch>();
            try {
                manager->startRent(id, ev, field, cl, getDate());
            }
            catch(std::invalid_argument& e){
                cerr<<e.what()<<endl;
            };
            break;
        default:
            cout << "Nie ma takiej opcji." << endl;
            return;
    }
    cout << "Id Pana/Pani wypozyczenia: " << id << endl;
}

void endRent(Manager *manager) {
    int id; datePtr date;
    try {
        cout << "Prosze podac id swojego wypozyczenia: ";
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            throw std::invalid_argument("Invalid argument id should be integer");
        }
    }
    catch(std::invalid_argument& e){
        cerr<<e.what()<<endl;
    };
    if (manager->getRentManager()->getRentRepository()->get(id)==nullptr)
    {
        cout<<"Takie wypozyczenie nie istnieje"<<endl;
        return;
    }
    if (manager->getRentManager()->getRentRepository()->get(id)->isArchive())
    {
        cout<<"To wypozyczenie jest juz zakonczone"<<endl;
        return;
    }
    cout << "Prosze podac date zakonczenia wypozyczenia: "; date = getDate();
    manager->endRent(id, date);
    cout << "Koszt wypozycznia: " << manager->getRentManager()->getRentRepository()->get(id)->getRentCost() << endl;
    cout<<"Wypozyczenie zakonczono pomyslnie"<<endl;
}

void getInfoAboutClient(Manager *manager) {
    string city, street, number;
    cout << "Prosze podac miasto: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, city);
    cout << "Prosze podac ulice: ";
    getline(cin, street);
    cout << "Prosze podac numer domu: ";
    getline(cin, number);
    if (manager->getClientByAddress(city, street, number) == nullptr) {
        cout << "Taki klient nie istnieje" << endl;
    } else {
        cout << manager->getClientByAddress(city, street, number)->getInfo() << endl;
    }
}

void getInfoAboutField(Manager *manager) {
    int id;
    try {
        cout << "Podaj id boiska: ";
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            throw std::invalid_argument("Invalid argument id should be integer");
        }
    }
    catch(std::invalid_argument& e){
        cerr<<e.what()<<endl;
    };
    if(manager->getFieldById(id) == nullptr) {
        cout << "Takie boisko nie istnieje" << endl;
    } else {
        cout << manager->getFieldById(id)->getInfo() << endl;
    }
}

void getInfoAboutRentsForField(Manager *manager) {
    int id;
    try{
    cout << "Podaj id boiska: "; cin >> id;
        if (cin.fail()) {
            cin.clear();
            throw std::invalid_argument("Invalid argument id should be integer");
        }
    }
    catch(std::invalid_argument& e){
        cerr<<e.what()<<endl;
    };
    for(auto r : manager->getAllRentsForField(id)) {
        cout << r->getInfo() << endl;
    }
}

void getInfoAboutRentsForClient(Manager *manager) {
    string city, street, number;
    cout << "Prosze podac miasto: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, city);
    cout << "Prosze podac ulice: "; getline(cin, street);
    cout << "Prosze podac numer domu: "; getline(cin, number);
    for(auto r : manager->getAllRentsForClient(city, street, number)) {
        cout << r->getInfo() << endl;
    }
}

void changePhoneNumber(Manager *manager) {
    string city, street, number, newNumber;
    cout << "Prosze podac adres." << endl;
    cout << "Miasto: "; cin.ignore( numeric_limits < streamsize >::max(), '\n' ); getline(cin, city);
    cout << "Ulica: "; getline(cin, street);
    cout << "Numer: "; getline(cin, number);
    if (manager->getClientByAddress(city,street,number))
    {
        cout << "Prosze podac nowy numer telefonu: "; cin >> newNumber;
        manager->changeClientPhoneNumber(newNumber, city, street, number);
    }
    else
    {
        cout<<"Taki klient nie istnieje w naszej bazie"<<endl;
    }
}

void menu() {
    cout << "----MENU----" << endl;
    cout << "1.  Dodaj klienta" << endl;
    cout << "2.  Dodaj orlik" << endl;
    cout << "3.  Rozpocznij wypozyczenie" << endl;
    cout << "4.  Zakoncz wypozyczenie" << endl;
    cout << "5.  Uzyskaj informacje o kliencie" << endl;
    cout << "6.  Uzyskaj informacje o boisku" << endl;
    cout << "7.  Zmien numer telefonu" << endl;
    cout << "8.  Wyswietl informacje o wypozyczeniach klienta" << endl;
    cout << "9.  Wyswietl informacje o wypozyczniach danego boiska" << endl;
    cout << "10. Zakoncz program" << endl;
    cout << "Co chcesz zrobic: ";
}

int main() {
    Manager *manager = new Manager;
    int running = 0;
    int choice;
    while(!running) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1:
                registerClient(manager);
                break;
            case 2:
                addField(manager);
                break;
            case 3:
                startRent(manager);
                break;
            case 4:
                endRent(manager);
                break;
            case 5:
                getInfoAboutClient(manager);
                break;
            case 6:
                getInfoAboutField(manager);
                break;
            case 7:
                changePhoneNumber(manager);
                break;
            case 8:
                getInfoAboutRentsForClient(manager);
                break;
            case 9:
                getInfoAboutRentsForField(manager);
                break;
            default:
                running = 1;
                break;
        }
    }
    delete manager;
    return 0;
}