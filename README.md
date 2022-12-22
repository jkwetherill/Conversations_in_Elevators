 # Conversations_in_Elevators
 
 This project simulates the traveling of people through a building, from starting floors onto elevators to destination floors. All the while, in each space, be it a floor or an elevator, all the people there are having a conversation.
 
 The user specifies the people traveling through the building in the file People.txt, which is located in the project directory. Each row represents a person. First the name is listed, then the person's starting floor index is listed, and finally the person's destination floor is listed. The floors are indexed from 0 to 9. The name, starting floor, and destination floor are separated by spaces. Names must not contain spaces.
 
 There are 10 floors, indexed 0 through 9, and 3 elevators, indexed 0 through 2. The number of floors or elevators could be changed by hard-coding a different constant value in the Constants.h file.
 
 In each space, the conversation consists of a list of open questions that have been asked. When a person talks, they first try to answer a question that has been asked. If there are no unanswered questions, the person asks one. Sometimes a person answers their own question.
 
 The simulation outputs sentences to the terminal to specify when each person enters a space (a floor or elevator); what each person is saying and to whom; and when each elevator moves to each floor.
 
 
 
 
 
 Loops, Functions, I/O

The project reads data from an external file on line 73 of Building.cpp

The project processes this input in the file Building.cpp in the function readInPeople on line 73

Line 27 in Answer.cpp is one example of a switch statement. The project contains many control structures.



OBJECT-ORIENTED PROGRAMMING

As you can see, more or less each .h/.cpp pair of files corresponds to a class

All class data members are specified as either private, public or protected. For instance on line ### in Person.h, the member _ID is specified as private.

There are several member initialization lists in the project. For example the Person constructor on line 19 of Person.cpp has a member initialization list that specifies _name and _destFloor

The classes contain encapsulation. For instance, see the getter & setter on lines 106 and 112 of Person.cpp

Classes follow an inheritance hierarchy. For example the class Floor in Floor.h is a child class of the class Space in Space.h. The class Elevator in Elevator.h is another child class of the Space class. Additionally the classes Question and Answer (in Question.h and Answer.h) are child classes of the class Dialog in Dialog.h.

One example of an overloaded function is the function spaceType() in the Space.h on line 44. It is overloaded in Floor.h on line 44 and in Elevator.h on line 63

The destructor in the space class is virtual and overridden by the destructor in Floor.h and Elevator.h. See line 35 in Space.h

There are several examples of templates in the project. For example, the MessageQueue class has a template, and it is used in MessageQueue.h on line 41. The typename is used as an Answer, a Question, and an unsigned int in various locations of the project.



MEMORY MANAGEMENT

A function that takes a reference as an input is on line 15 of Floor.cpp. A second function that takes a reference as an input is on line 73 of Building.cpp (the input errorMsg). A reference to a mutex is on line 144 of Person.cpp.




The project follows the rule of 5. See Space.h, Person.h, Floor.h, Elevator.h

The lifetime of many resources is handled by smart pointers. The smart pointer is a member of a class, and when the class is constructed, the object to which the smart pointer points is created on the heap. The smart pointers then take care of the destruction of the object. For example, the pointer to each person in the simulation is a unique pointer, created on line 170 of Person.cpp. Each elevator also lives in a unique pointer, as shown on line 23 of Floor.h. Each floor is in a shared pointer, as shown on line 16 of Floor.h and line 34 of Elevator.h.




CONCURRENCY

There are many instances of futures used in multiple threads. See lines 119 and 121 in Building .cpp. See lines 18 & 28 in Building.cpp.

Each elevator has a mutex. They are used on line 17 of Floor.cpp and 145 of Person.cpp

The messagequeue has a condition variable. See line 28 of MessageQueue.h
 

