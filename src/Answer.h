#ifndef ANSWER_H
#define ANSWER_H

#include "Dialog.h"
#include "Question.h"


class Answer : public Dialog
{

    public:
    Answer(const std::string& speaker, Question& question);
    ~Answer();

    private:
    void generateDialog();

};

#endif