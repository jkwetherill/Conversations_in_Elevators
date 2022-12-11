#ifndef DIALOG_H
#define DIALOG_H

#include <string>



enum Question_Type
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
    virtual void generateDialog() = 0;

    protected:
    Dialog();
    Dialog(std::string& speaker, unsigned int ID);
    virtual ~Dialog() = 0;

    Dialog &operator=(const Dialog &dialog);
    Dialog(const Dialog &dialog);
    Dialog(Dialog &&dialog);
    Dialog &operator=(Dialog &&dialog);

    public:

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


#endif






