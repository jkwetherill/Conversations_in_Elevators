#include "Building.h"
#include "Person.h"
#include <fstream>
#include <sstream>

Building::Building()
{

    for (unsigned int i = 0; i < NFLOORS; i++)
    {
        Floors[i].setLevel(i);
    }

    for (unsigned int i = 0; i < NELEVATORS; i++)
    {
        std::unique_ptr<Elevator> elevator(new Elevator(i));
        Floors[0].moveElevatorHere(std::move(elevator));
    }
}

Building::~Building()
{
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
}