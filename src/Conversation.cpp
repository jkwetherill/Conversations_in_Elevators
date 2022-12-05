#include "Conversation.h"
#include <thread>
#include <future>
#include <vector>


Conversation::Conversation(std::string logFile):_logFile(logFile)
{

}

void Conversation::run()
{
    std::future<void> fQ = std::async(std::launch::async, &Conversation::receiveQuestions, this);
    std::future<void> fA = std::async(std::launch::async, &Conversation::receiveAnswers, this);

 

    fQ.get();
    fA.get();
}


void Conversation::receiveQuestions()
{
    while (1)
    {
        Question newQuestion = questionQueue.receive(); //wait for somebody to ask a question
        std::lock_guard<std::mutex> lock(_mutex);
        newQuestion.record(_logFile);
        openQuestions.emplace_back(newQuestion);
        _mutex.unlock();
    }
    
}

void Conversation::receiveAnswers()
{
    while (1)
    {
        Answer newAnswer = answerQueue.receive(); // wait for somebody to provide an answer
        std::lock_guard<std::mutex> lock(_mutex);
        
        // record answer
        newAnswer.record(_logFile);

        

        for (auto i = openQuestions.begin(); i != openQuestions.end(); i++)
        {
            if ((*i).getID() == newAnswer.getID())
            {
                openQuestions.erase(i);
                break;
            }
        }

        _mutex.unlock();
    }
}
