#include "Person.h"
#include "Space.h"
#include "Building.h"
#include <vector>
#include <thread>
#include <random>
#include <iostream>

unsigned int Person::_IDCount = 0;

Person::Person()
{
    _ID = _IDCount++;
    pSpace = nullptr;
}



Person::Person(std::string name, unsigned int destFloor, unsigned int curFloor, Building* pBuilding):_name(name), _destFloor(destFloor)
{
    _ID = _IDCount++;
    
    _destFloor = destFloor;
    
    enterSpace(pBuilding->Floors[curFloor].get());

}


Person::~Person()
{

}

/*private:
    std::string _name;
    unsigned int _ID;
    unsigned int _destFloor;

    static unsigned int _IDCount;

public:
    Space *pSpace;*/



Person& Person::operator=(const Person& person)
{
    std::cout << "Copy Person (not good)\n";
   if (this == &person) 
   {
    return *this;
   }

    _name = person._name;
    _ID = person._ID;
    _destFloor = person._destFloor;
    pSpace = person.pSpace; // the person doesn't own the space, they just observe it. A space should never be deep copied

   return *this;
}
Person& Person::operator=(Person&& person)
{
   std::cout << "move person\n";
   if (this == &person) 
   {
    return *this;
   }

    _name = person._name;
    _ID = person._ID;
    _destFloor = person._destFloor;
    pSpace = person.pSpace; 

    person.pSpace = nullptr;

   return *this;
}
Person::Person(const Person& person)
{

    std::cout << "Person copy constructor\n";

    _name = person._name;
    _ID = person._ID;
    _destFloor = person._destFloor;
    pSpace = person.pSpace; // the person doesn't own the space, they just observe it. A space should never be deep copied

}

Person::Person(Person&& person)
{

    std::cout << "Person move constructor\n";

    _name = person._name;
    _ID = person._ID;
    _destFloor = person._destFloor;
    pSpace = person.pSpace; 

    person.pSpace = nullptr;

}


std::string& Person::get_name() 
{
    return _name;
}


void Person::set_name(const std::string& name)
{
    _name = name;
}

unsigned int& Person::get_ID() 
{
    return _ID;
}

void Person::enterSpace(Space *pNewSpace)
{

    Elevator* pElevator;
    unsigned int shaft_idx;
    if (pNewSpace->spaceType() == SpaceType::ELEVATOR)
    {
        // if the new space is an elevator, pause the elevator and let in only one person at a time
        pElevator = static_cast<Elevator*>(pNewSpace);
        shaft_idx = pElevator->shaftIdx;

        
    }
    else if (pSpace != nullptr && pSpace->spaceType() == SpaceType::ELEVATOR)
    {
        pElevator = static_cast<Elevator*>(pSpace);
        shaft_idx = pElevator->shaftIdx;
    }
    else
    {
        shaft_idx = 0;   
    }
    std::mutex& m = pNewSpace->pBuilding->ElevatorMutexes[shaft_idx];
    std::unique_lock<std::mutex> lock(m);

 


    bool inAnotherSpace = false;
    std::unique_ptr<Person> this_person;
    if (pSpace != nullptr)
    {
    for (std::vector<std::unique_ptr<Person>>::iterator it = pSpace->people.begin(); it != pSpace->people.end(); it++)
    {
        if ((*it)->get_ID() == _ID)
        {
            this_person = std::move(*it);
            pSpace->people.erase(it);
            inAnotherSpace = true;
            break;
        }
    }
    }

    pSpace = pNewSpace;

    if (!inAnotherSpace)
    {
        this_person.reset(this);
    }

    pSpace->people.emplace_back(std::move(this_person));

    switch (pSpace->spaceType())
    {
        case SpaceType::ELEVATOR:
        {
            Elevator* pElevator = static_cast<Elevator*>(pSpace);
            std::cout << _name << " enters elevator # " << pElevator->shaftIdx << "\n";
            break;
        }
        case SpaceType::FLOOR:
        {
            Floor* pFloor = static_cast<Floor*>(pSpace);
            std::cout << _name << " enters floor # " << pFloor->level << "\n";
            break;
        }
    }

}

void Person::talk()
{
    while (1)
    {
    // pause 3-15 seconds
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(3000, 15000);

    std::this_thread::sleep_for(std::chrono::milliseconds(distr(eng)));

    if (pSpace == nullptr)
    {
        continue;
    }
    else if (pSpace->spaceType() == SpaceType::FLOOR && pSpace->level == _destFloor)
    {
        continue; // don't talk at the destination floor
    }

    std::unique_ptr<Conversation> &convo = pSpace->conversation;
    std::vector<Question>& openQuestions = convo->openQuestions;

    if (openQuestions.size() > 0)
    {
        // answer 1st question
        Answer answer(_name, openQuestions[0]);
        pSpace->conversation->answerQueue.send(std::move(answer));
    }
    else
    {
        // ask a question
        Question question(_name);
        pSpace->conversation->questionQueue.send(std::move(question));
    }
    }
}

void Person::travel()
{

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, NELEVATORS-1);
    

    while ((_destFloor != pSpace->level) || (pSpace->spaceType() != SpaceType::FLOOR))
    {
        switch (pSpace->spaceType())
        {
            case SpaceType::FLOOR:
            {

                
                Floor* thisFloor = static_cast<Floor*> (pSpace);

                // choose a random elevator index
                unsigned int shaft_idx = distr(eng);

                if (_destFloor > pSpace->level)
                {
                    thisFloor->upButtons[shaft_idx] = true; 
                }
                else if (_destFloor < pSpace->level)
                {
                    thisFloor->downButtons[shaft_idx] = true;
                }

                

                // wait for elevator to reach this floor
                while (thisFloor->elevators[shaft_idx].get() == nullptr)
                {

                }

            
                // enter elevator
                enterSpace(thisFloor->elevators[shaft_idx].get());

                



                break;
            }
            case SpaceType::ELEVATOR:
            {
                Elevator* thisElevator = static_cast<Elevator*>(pSpace);
                thisElevator->buttons[_destFloor] = true;

                // wait for elevator to arrive on destination floor
                while (thisElevator->messageQueue->receive() != _destFloor)
                {

                }

                // enter elevator
                enterSpace(thisElevator->pBuilding->Floors[thisElevator->level].get());

                break;
            }
            default:
            {
                break;
            }
        }
    }
}


void Person::simulate()
{

}
