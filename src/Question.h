#ifndef QUESTION_H
#define QUESTION_H

#include "Dialog.h"

class Question : public Dialog
{
  public:
  Question(const std::string& speaker);
  ~Question();

  private:
  void generateDialog();

};


#endif