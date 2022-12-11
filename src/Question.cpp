#include "Question.h"
#include <random>



Question::Question()
{

}

void Question::ask(const std::string &speaker)
{
  _speaker = speaker;
  //_ID = _IDCounter++;

  generateDialog();
}


Question::~Question()
{

}


void Question::generateDialog()
{

  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(0, NQuestionTypes - 1);

  unsigned int nQT = distr(eng);

  if (nQT == 0)
  {
    _questionType = WHO;
    _sentence = "Who are you?";
  }
  else if (nQT == 1)
  {
    _questionType = WHAT;
    _sentence = "What is that?";
  }
  else if (nQT == 2)
  {
    _questionType = WHEN;
    _sentence = "When is dinner?";
  }
  else if (nQT == 3)
  {
    _questionType = WHERE;
    _sentence = "Where do you live?";
  }
  else if (nQT == 4)
  {
    _questionType = WHY;
    _sentence = "Why is the sky blue?";
  }
  else if (nQT == 5)
  {
    _questionType = WHETHER;
    _sentence = "Do you like it?";
  }
  else
  {
    _questionType = WHETHER;
    _sentence = "Are you hungry?";
  }
}

/*
typedef enum Question_Type
{
  WHO,
  WHAT,
  WHEN,
  WHERE,
  WHY,
  WHETHER
};

*/