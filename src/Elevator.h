#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Constants.h"
#include "Space.h"
#include <string>
#include "Floor.h"
#include <memory>

class Floor;


enum Direction
{
    UP,
    DOWN,
    IDLE
};

class ElevatorButton
{
private:
Direction button = IDLE;

};

class Elevator : public Space
{
    private:

        bool _buttons[NFLOORS];

        std::shared_ptr<Floor> _floors[NFLOORS];

        bool _open = false;

        Direction _direction = Direction::UP;

        

        //do not copy elevators or spaces
        Elevator& operator=(const Elevator& elevator_in);
        Elevator(const Elevator& elevator_in);

    public:
        Elevator(unsigned int shaftIdx, Floor* floors);
        Elevator();
        ~Elevator();

        //assignment operator
        
        
        Elevator(Elevator&& elevator_in);
        Elevator& operator=(Elevator&& elevator_in);

        bool isOpen();

        unsigned int shaftIdx;

        void setLevel(unsigned int level);
        void setFloor(Floor* floor);

        SpaceType spaceType()
        {
            return SpaceType::ELEVATOR;
        } 
        
        void simulate();

};




#endif