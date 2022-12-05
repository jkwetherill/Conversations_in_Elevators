#include "Elevator.h"

Elevator::Elevator(unsigned int shaftIdxIn, Floor* floors):shaftIdx(shaftIdxIn)
{
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _floors[i] = (*(floors+i)).get_shared_this();
    }
}


Elevator::Elevator(Elevator &&elevator_in) // move constructor
{
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _buttons[i] = elevator_in._buttons[i];
    }

    _open = elevator_in._open;

    shaftIdx = elevator_in.shaftIdx;

    _floors = elevator_in._floors;

    _direction = elevator_in._direction;

    elevator_in._floors = nullptr;
}

Elevator &Elevator::operator=(Elevator &&elevator_in)  // move assignment
{

    if (this == &elevator_in)
    {
        return *this;
    }

    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        _buttons[i] = elevator_in._buttons[i];
    }

    _open = elevator_in._open;

    _floors = elevator_in._floors;

    _direction = elevator_in._direction;

    elevator_in._floors = nullptr;

    shaftIdx = elevator_in.shaftIdx;

    return *this;
}

bool Elevator::isOpen()
{
    return _open;
}

void Elevator::setFloor(Floor *floors)
{
    _floors = floors;
}

void Elevator::setLevel(unsigned int level_in)
{
    level = level_in;
}

void Elevator::simulate()
{
    while (1)
    {
        if (_direction == UP && level == NFLOORS-1)
        {
            _direction = DOWN;
        }
        if (_direction == DOWN && level == 0)
        {
            _direction = UP;
        }
        switch (_direction)
        {
        case UP:
        {
            Floor NextFloor = _floors[level+1];
            break;
        }
        case DOWN:
        {
            break;
        }
        default:
        {
            break;
        }
        }

    }
}