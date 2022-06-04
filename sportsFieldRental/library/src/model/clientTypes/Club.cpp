//
// Created by student on 02.06.2022.
//

#include "model/clientTypes/Club.h"
#include "model/clientTypes/League.h"

string Club::getType() {
    return "Club";
}

Club::Club() {

}

Club::Club(const leaguePtr &league) : league(league) {}

string Club::getInfo() {
    return "Typ: Klub, Liga: " + league->getLeague();
}