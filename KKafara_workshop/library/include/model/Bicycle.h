//
// Created by student on 17.04.2022.
//

#ifndef CARRENTAL_BICYCLE_H
#define CARRENTAL_BICYCLE_H

#include "Vehicle.h"

class Bicycle : public Vehicle {
public:
    Bicycle(const string &plateNumber, unsigned int basePrice);
    virtual double getActualRentalPrice() const;
    virtual string getVehicleInfo() const;
    virtual ~Bicycle();
};


#endif //CARRENTAL_BICYCLE_H
