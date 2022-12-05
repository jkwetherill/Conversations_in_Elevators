
#ifndef FLOOR_H
#define FLOOR_H

#include "Constants.h"
#include "Space.h"
#include "Building.h"
#include "ElevatorButton.h"



class Floor : public Space, public std::enable_shared_from_this<Floor>
{
private:

    bool _upButtons[NELEVATORS];
    bool _downButtons[NELEVATORS];

    std::unique_ptr<Elevator> _elevators[NELEVATORS];



public:
    Floor();
    ~Floor();

    std::shared_ptr<Floor> get_shared_this()
    {
        return shared_from_this();
    }

    void Floor::moveElevatorHere(std::unique_ptr<Elevator>&& pElevator);

    void pressUpButton(unsigned int shaft_idx);
    void pressDownButton(unsigned int shaft_idx);

    void releaseUpButton(unsigned int shaft_idx);
    void releaseDownButton(unsigned int shaft_idx);

    SpaceType spaceType()
    {
        return SpaceType::FLOOR;
    } 


};

#endif