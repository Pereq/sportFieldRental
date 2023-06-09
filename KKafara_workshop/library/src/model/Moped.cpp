//
// Created by student on 17.04.2022.
//

#include "model/Moped.h"

Moped::Moped(const string &plateNumber, unsigned int basePrice, unsigned int engineDisplacement) : MotorVehicle(
        plateNumber, basePrice, engineDisplacement) {}

double Moped::getActualRentalPrice() const {
    return MotorVehicle::getActualRentalPrice();
}

string Moped::getVehicleInfo() const {
    return MotorVehicle::getVehicleInfo();
}

Moped::~Moped() {}
