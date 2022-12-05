#ifndef DIALOG_H
#define DIALOG_H

#include <string>



typedef enum Question_Type
{
  WHO,
  WHAT,
  WHEN,
  WHERE,
  WHY,
  WHETHER
};

#define NQuestionTypes 6


class Dialog
{
    protected:
    static unsigned int _IDCounter;
    virtual void Dialog::generateDialog() = 0;

    public:
    Dialog();
    ~Dialog();

    Dialog &operator=(const Dialog &dialog);
    Dialog(const Dialog &dialog);
    Dialog(Dialog &&dialog);
    Dialog &operator=(Dialog &&dialog);

    const std::string& getSpeaker();
    const unsigned int& getID();
    const Question_Type& getQuestionType();
    const std::string& getSentence();

    void record(std::string& FileName);

    protected:
    std::string _speaker;
    unsigned int _ID;
    Question_Type _questionType;
    std::string _sentence = "";

};





class Answer : public Dialog
{

};


#endif






