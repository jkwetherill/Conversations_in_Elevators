#include "Floor.h"
#include "Building.h"
#include <iostream>

Floor::Floor()
{

}

Floor::~Floor()
{

}

void Floor::moveElevatorHere(std::unique_ptr<Elevator>&& pElevator)
{
    std::unique_lock<std::mutex> lock(pBuilding->ElevatorMutexes[pElevator->shaftIdx]);
    unsigned int shaftIdx = pElevator->shaftIdx;
    elevators[shaftIdx] = std::move(pElevator);
    elevators[shaftIdx]->setLevel(level);

    // allow people to enter & exit
    elevators[shaftIdx]->messageQueue->send(std::move(level));

}

void Floor::pressUpButton(unsigned int shaft_idx)
{
    upButtons[shaft_idx] = true;
}
void Floor::pressDownButton(unsigned int shaft_idx)
{
    downButtons[shaft_idx] = true;
}

void Floor::releaseUpButton(unsigned int shaft_idx)
{
    upButtons[shaft_idx] = false;
}

void Floor::releaseDownButton(unsigned int shaft_idx)
{
    downButtons[shaft_idx] = false;
}