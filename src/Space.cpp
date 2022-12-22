#include "Space.h"
#include "Person.h"
#include <iostream>

Space::Space()
{
    conversation.reset(new Conversation());
}

Space::~Space()
{
    
}

Space::Space(const std::string& logFile)
{
    conversation.reset(new Conversation(logFile));
}


Space::Space(Space &&Space_in) // move constructor
{
    std::cout << "Moving space\n";
    conversation = std::move(Space_in.conversation);
    people = std::move(people);
    level = Space_in.level;
}


Space &Space::operator=(Space &&Space_in) // move assignment
{

    std::cout << "Space Move Assignment " << &Space_in << " " << this << "\n";
    if (&Space_in == this)
    {
        return *this;
    }
    conversation = std::move(Space_in.conversation);
    level = Space_in.level;
    people = std::move(Space_in.people);

    return *this;
}

void Space::setLevel(unsigned int level_in)
{
    level = level_in;
}



