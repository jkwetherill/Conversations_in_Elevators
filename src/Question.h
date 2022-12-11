#ifndef QUESTION_H
#define QUESTION_H

#include "Dialog.h"

//class Dialog;

class Question : public Dialog
{
  public:
  Question();
  //Question(const std::string& speaker);
  void ask(const std::string& speaker);
  ~Question();

  protected:
  void generateDialog();

};


#endif