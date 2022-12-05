#include <future>
#include "MessageQueue.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    std::unique_lock<std::mutex> lock(_mutex);

    _cond.wait(lock);
 
    T msg = std::move(_queue.back());
    _queue.pop_back();
    return msg; // will not be copied due to return value optimization
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lock(_mutex);

    //add a new message to the queue
    _queue.emplace_back(msg);

    //send a notification
    _cond.notify_one();
}





