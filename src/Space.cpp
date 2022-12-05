#include "Space.h"

Space::Space()
{
    conversation.reset(new Conversation);
}

Space::Space(const std::string& logFile)
{
    conversation.reset(new Conversation(logFile));
}

Space::~Space()
{
}


Space::Space(Space &&Space_in) // move constructor
{
    conversation = std::move(Space_in.conversation);
    people = std::move(people);
    level = Space_in.level;
}


Space &Space::operator=(Space &&Space_in) // move assignment
{

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



