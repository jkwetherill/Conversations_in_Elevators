#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <mutex>
#include <vector>
#include "Answer.h"
#include "Question.h"
#include "MessageQueue.h"


//class Question;
//class Answer;

//template <class T>
//class MessageQueue;
//class MessageQueue<Question>;
//class MessageQueue<Answer>;

class Conversation
{
  public:
  Conversation();
  Conversation(std::string logFile);
  ~Conversation();

  //friend class MessageQueue<Question>;
  //friend class MessageQueue<Answer>;

  void receiveQuestions();
  void receiveAnswers();

  void run();


  
  std::vector<Question> openQuestions;

  MessageQueue<Question> questionQueue;
  MessageQueue<Answer> answerQueue;
  
 private:
  std::mutex _mutex;





  

  std::string _logFile;

  void closeQuestions();
};

#endif