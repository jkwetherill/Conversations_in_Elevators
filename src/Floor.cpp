#include "Floor.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

void Floor::moveElevatorHere(std::unique_ptr<Elevator>&& pElevator)
{
    elevators[pElevator->shaftIdx] = std::move(pElevator);
    elevators[pElevator->shaftIdx]->setLevel(this->level);
    elevators[pElevator->shaftIdx]->setFloor(this);
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