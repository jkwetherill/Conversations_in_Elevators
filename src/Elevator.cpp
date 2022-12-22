#include "Elevator.h"
#include <random>
#include <thread>
#include <iostream>

Elevator::Elevator()
{
}
Elevator::~Elevator()
{
}

Elevator::Elevator(unsigned int shaftIdxIn, std::shared_ptr<Floor>* floors):shaftIdx(shaftIdxIn)
{
    messageQueue.reset(new MessageQueue<unsigned int>);
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _floors[i] = floors[i]->get_shared_this();
    }
}


Elevator::Elevator(Elevator &&elevator_in) // move constructor
{
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        buttons[i] = elevator_in.buttons[i];
    }

    _open = elevator_in._open;

    shaftIdx = elevator_in.shaftIdx;

    _direction = elevator_in._direction;

    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        //_floors[i] = std::move(elevator_in._floors[i]);
        _floors[i] = elevator_in._floors[i];
    }

    messageQueue = std::move(elevator_in.messageQueue);

}

Elevator &Elevator::operator=(Elevator &&elevator_in)  // move assignment
{

    if (this == &elevator_in)
    {
        return *this;
    }

    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        buttons[i] = elevator_in.buttons[i];
    }

    _open = elevator_in._open;

    _direction = elevator_in._direction;

    shaftIdx = elevator_in.shaftIdx;

    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _floors[i] = std::move(elevator_in._floors[i]);
    }

    messageQueue = std::move(elevator_in.messageQueue);

    return *this;
}

bool Elevator::isOpen()
{
    return _open;
}

void Elevator::setFloor(Floor *floors)
{
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _floors[i] = (*(floors+i)).get_shared_this();
    }
}

/*
void Elevator::setLevel(unsigned int level_in)
{
    level = level_in;
}
*/

void Elevator::simulate()
{

    std::cout << "Elevator # " << this->shaftIdx << " is launched.\n";

    // pause 20-30 seconds
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(25000, 30000);

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(distr(eng)));

        if (_direction == UP && level == NFLOORS-1)
        {
            _direction = DOWN;
        }
        if (_direction == DOWN && level == 0)
        {
            _direction = UP;
        }
        unsigned int nextFloorIdx;
        std::shared_ptr<Floor> pNextFloor;
        switch (_direction)
        {
        case UP:
        {
            nextFloorIdx = level + 1;
            pNextFloor = _floors[level+1];
            break;
        }
        case DOWN:
        {
            nextFloorIdx = level - 1;
            pNextFloor = _floors[level-1];
            break;
        }
        default:
        {
            nextFloorIdx = level;
            pNextFloor = _floors[level];
            break;
        }
        }


        std::cout << "Elevator # " << this->shaftIdx << " moving to floor " << nextFloorIdx << " \n";

        pNextFloor->moveElevatorHere(std::move(_floors[level]->elevators[this->shaftIdx]));

        if (_direction == UP && level == NFLOORS-1)
        {
            _direction = DOWN;
        }
        if (_direction == DOWN && level == 0)
        {
            _direction = UP;
        }

        if (buttons[nextFloorIdx])
        {
            buttons[nextFloorIdx] = false; // release button
        }
        if (_direction == UP && pNextFloor->upButtons[this->shaftIdx])
        {
            pNextFloor->upButtons[this->shaftIdx] = false; // release button
        }
        else if (_direction == DOWN && pNextFloor->downButtons[this->shaftIdx])
        {
            pNextFloor->downButtons[this->shaftIdx] = false; // release button
        }


    }
}