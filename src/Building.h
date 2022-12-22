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

    std::shared_ptr<Floor> Floors[NFLOORS];
    std::mutex ElevatorMutexes[NELEVATORS];

    bool readInPeople(const std::string& inputDir, std::string& errorMsg, std::vector<std::future<void>>& talkingFutures, std::vector<std::future<void>>& travelingFutures);

    void launchElevators();
};

#endif

