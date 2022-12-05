#ifndef PERSON_H
#define PERSON_H

#include "Space.h"
#include "Building.h"
#include <string>

class Space;
class Building;

class Person
{
private:
    std::string _name;
    unsigned int _ID;
    unsigned int _destFloor;

    static unsigned int _IDCount;

public:
    Space *pSpace;

    Person();
    Person(std::string name, unsigned int destFloor, unsigned int curFloor, Building *pBuilding);

    ~Person();

    Person &operator=(const Person &person);
    Person &operator=(Person &&person);
    Person(const Person &person);
    Person(Person &&person);

    std::string &get_name();
    void set_name(const std::string &name);

    unsigned int &get_ID();

    void enterSpace(Space *pNewSpace);

    void simulate();

    void talk();

    void travel();
};

#endif