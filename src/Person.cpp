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
    //future.get();
    
    std::cout << "Entering space\n";
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

    _name = person._name;
    _ID = person._ID;
    _destFloor = person._destFloor;
    pSpace = person.pSpace; // the person doesn't own the space, they just observe it. A space should never be deep copied

}

Person::Person(Person&& person)
{


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


void Person::enterSpace(Space* pNewSpace)
{
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
}


void Person::talk()
{

    
    while (1)
    {
        //pause 3-8 seconds
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(3000, 8000);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(distr(eng)));

        std::cout << "Getting open questions\n";
        if (pSpace == nullptr)
        {
            continue;
        }

        auto openQuestions = pSpace->conversation->openQuestions;
        if (openQuestions.size() > 0)
        {
            std::cout << "Answering\n";
            //answer 1st question
            Answer answer(_name, openQuestions[0]);
            pSpace->conversation->answerQueue.send(std::move(answer));
        }
        else
        {
            std::cout << "Asking\n";
            //ask a question
            Question question; //(_name);
            question.ask(_name);
            pSpace->conversation->questionQueue.send(std::move(question));
        }


    }
    
}



void Person::travel()
{
    while (_destFloor != pSpace->level && pSpace->spaceType() != FLOOR)
    {
        switch (pSpace->spaceType())
        {
            case SpaceType::FLOOR:
            {
                
                break;
            }
            case SpaceType::ELEVATOR:
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


void Person::simulate()
{

}
