#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Constants.h"
#include "Space.h"
#include <string>
#include "Floor.h"
#include <memory>
#include "MessageQueue.h"

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

        

        std::shared_ptr<Floor> _floors[NFLOORS];

        bool _open = false;

        Direction _direction = Direction::UP;

        

        //do not copy elevators or spaces
        Elevator& operator=(const Elevator& elevator_in);
        Elevator(const Elevator& elevator_in);

    public:
        Elevator(unsigned int shaftIdx, std::shared_ptr<Floor>*);
        Elevator();
        ~Elevator();
        Elevator(Elevator&& elevator_in);
        Elevator& operator=(Elevator&& elevator_in);

        std::unique_ptr<MessageQueue<unsigned int>> messageQueue;

        bool isOpen();

        unsigned int shaftIdx;

        bool buttons[NFLOORS];

        void setFloor(Floor* floor);

        SpaceType spaceType()
        {
            return SpaceType::ELEVATOR;
        } 
        
        void simulate();

};




#endif