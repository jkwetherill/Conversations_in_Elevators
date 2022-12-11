#include "Building.h"
#include "Person.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <future>

Building::Building()
{


    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        Floors[i].setLevel(i);
    }

    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        std::unique_ptr<Elevator> elevator(new Elevator(i, Floors));
        Floors[0].moveElevatorHere(std::move(elevator));
    }


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
        elevatorFutures[i] = std::async(&Elevator::simulate, Floors[0].elevators[i].get());
    }

    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        elevatorFutures[i].get();
    }
   
}


bool readInPeople(const std::string& inputDir, std::string& errorMsg)
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

        //Person thisPerson
    }
    return true;
}