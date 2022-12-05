#include "Floor.h"


void Floor::moveElevatorHere(std::unique_ptr<Elevator>&& pElevator)
{
    _elevators[pElevator->shaftIdx] = std::move(pElevator);
    _elevators[pElevator->shaftIdx]->setLevel(this->level);
    _elevators[pElevator->shaftIdx]->setFloor(this);
}

void Floor::pressUpButton(unsigned int shaft_idx)
{
    _upButtons[shaft_idx] = true;
}
void Floor::pressDownButton(unsigned int shaft_idx)
{
    _downButtons[shaft_idx] = true;
}

void Floor::releaseUpButton(unsigned int shaft_idx)
{
    _upButtons[shaft_idx] = false;
}

void Floor::releaseDownButton(unsigned int shaft_idx)
{
    _downButtons[shaft_idx] = false;
}