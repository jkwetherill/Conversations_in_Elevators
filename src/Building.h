#ifndef BUILDING_H
#define BUILDING_H


#include "Constants.h"
#include "Floor.h"
#include "Elevator.h"

class Building
{
private:
    /* data */
    

public:

    Building();
    ~Building();

    Floor Floors[NFLOORS];

    bool readInPeople(const std::string& inputDir, std::string& errorMsg);

    void launchElevators();
};

#endif

