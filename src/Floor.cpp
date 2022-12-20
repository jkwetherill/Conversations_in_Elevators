#include "Floor.h"
#include <iostream>

Floor::Floor()
{

}

Floor::~Floor()
{

}

void Floor::moveElevatorHere(std::unique_ptr<Elevator>&& pElevator)
{
    unsigned int shaftIdx = pElevator->shaftIdx;
    //std::cout << "pElevator is : " << pElevator.get() << "\n";
    //std::cout << "Move assignment of elevator\n";
    elevators[shaftIdx] = std::move(pElevator);
    //std::cout << "member elevator is : " << elevators[shaftIdx].get() << "\n";
    //std::cout << "Setting level of elevator\n";
    //std::cout << "Floor level is: " << this->level << "\n";
    elevators[shaftIdx]->setLevel(this->level);
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