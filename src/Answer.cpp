#include "Answer.h"


Answer::Answer(const std::string &speaker, Question &question)
{
    _speaker = speaker;
    _ID = question.getID();
    _questionType = question.getQuestionType();

    generateDialog();
}

void Answer::generateDialog()
{
    switch (_questionType)
    {
    case WHO:
    {
        _sentence = "Your landlord.";
        break;
    }
    case WHAT:
    {
        _sentence = "A caterpillar.";
        break;
    }
    case WHEN:
    {
        _sentence = "In 100 years.";
        break;
    }
    case WHERE:
    {
        _sentence = "In your dreams.";
        break;
    }
    case WHY:
    {
        _sentence = "Because I said so.";
        break;
    }
    case WHETHER:
    {
        _sentence = "No.";
        break;
    }
    default:
    {
        _sentence = "I don't know.";
        break;
    }
    }
}