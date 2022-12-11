#ifndef ANSWER_H
#define ANSWER_H

#include "Dialog.h"


class Question;


//class Dialog;

class Answer : public Dialog
{

    public:
    Answer();
    Answer(const std::string& speaker, Question& question);
    ~Answer();

    private:
    void generateDialog();

};

#endif