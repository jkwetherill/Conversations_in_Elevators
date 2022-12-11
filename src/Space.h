#ifndef SPACE_H
#define SPACE_H

#include "Conversation.h"
#include <memory>
#include <vector>

class Person;

class Conversation;

enum SpaceType
{
    FLOOR,
    ELEVATOR
};

class Space
{
public:
    unsigned int level;
    std::unique_ptr<Conversation> conversation;
    std::vector<Person> people;

public:
    Space();
    Space(const std::string &logFile);

protected:
    virtual ~Space() = 0;

public:
    Space(Space &&Space_in);            // move constructor
    Space &operator=(Space &&Space_in); // move assignment

    void setLevel(unsigned int level_in);

public:
    virtual SpaceType spaceType() = 0;

private:                                     // private so they can't be called
   // Space &operator=(const Space &Space_in); // copy assignment private(spaces shouldn't be copied
   // Space(Space &Space_in);                  // copy constructor
};

#endif
