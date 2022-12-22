#include "Building.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>

Building::Building()
{

    std::future<void> fFloorConv[NFLOORS];
    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        Floors[i].reset(new Floor());
        Floors[i]->setLevel(i);
        Floors[i]->pBuilding = this;
        fFloorConv[i] = std::async(&Conversation::run, Floors[i]->conversation.get());
    }


    std::future<void> fElevatorConv[NELEVATORS];
    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        std::unique_ptr<Elevator> elevator(new Elevator(i, Floors));
        elevator->pBuilding = this;
        fElevatorConv[i] = std::async(&Conversation::run, elevator->conversation.get());
        Floors[0]->moveElevatorHere(std::move(elevator));
    }

    std::string errorMsg;
    std::vector<std::future<void>> talkingFutures;
    std::vector<std::future<void>> travelingFutures;
    bool e = readInPeople(".//..", errorMsg, talkingFutures, travelingFutures);
    if (e)
    {
        std::cout << "Successfully read people.\n";
    }
    else
    {
        std::cout << errorMsg << "\n";
    }

    launchElevators();
}

Building::~Building()
{
    
}

void Building::launchElevators()
{
    
    //set the elevators in motion
    std::future<void> elevatorFutures[NELEVATORS];

    
    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        // for now assumes the elevator is starting on the bottom floor, could be made more general
        elevatorFutures[i] = std::async(&Elevator::simulate, Floors[0]->elevators[i].get());
    }

    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        //elevatorFutures[i].get();
    }
   
}


bool Building::readInPeople(const std::string& inputDir, std::string& errorMsg, std::vector<std::future<void>>& talkingFutures, std::vector<std::future<void>>& travelingFutures)
{
    const std::string FileName = inputDir + "/People.txt";

    std::ifstream filestream(FileName);

    if (!filestream.is_open())
    {
        errorMsg = "Invalid file";
        return false;
    }

    std::string line;

    
    while (std::getline(filestream, line))
    {
        std::istringstream linestream(line);

        std::string name;
        unsigned int start_floor, dest_floor;

        linestream >> name >> start_floor >> dest_floor;

        bool validStart = 0 <= start_floor && start_floor < NFLOORS;
        bool validDest  = 0 <= dest_floor && dest_floor < NFLOORS;

        if (!validStart && ! validDest)
        {
            errorMsg = "Invalid starting floor and destination floor";
            return false;
        }
        if (!validStart)
        {
            errorMsg = "Invalid starting floor";
            return false;
        }
        if (!validDest)
        {
            errorMsg = "Invalid destination floor";
            return false;
        }

        // handle will be assigned to a unique pointer in the constructor
        Person* pPerson = new Person(name, dest_floor, start_floor, this);
            
        talkingFutures.emplace_back(std::async(&Person::talk, pPerson));

        travelingFutures.emplace_back(std::async(&Person::travel, pPerson));
    }
    return true;
}