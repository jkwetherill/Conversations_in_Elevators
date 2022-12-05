#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H


// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

template <class T>
class MessageQueue
{
public:
std::deque<T>  _queue;
//template <typename T>
//void send(TrafficLightPhase&& signal);
//TrafficLightPhase&& receive();
void send(T &&msg);
T receive();

private:

std::condition_variable _cond;
std::mutex _mutex;
    
};

#endif