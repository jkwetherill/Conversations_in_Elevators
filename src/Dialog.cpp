 #include "Dialog.h"


Dialog::Dialog()
{

}

Dialog::~Dialog()
{
  
}

Dialog::Dialog(std::string& speaker, unsigned int ID):_speaker(speaker), _ID(ID)
{
  
}

Dialog &Dialog::operator=(const Dialog &dialog)
{
  if (this == &dialog)
  {
    return *this;
  }


  _speaker      = dialog._speaker;
  _ID           = dialog._ID;
  _questionType = dialog._questionType;
  _sentence     = dialog._sentence;
  
  return *this;
}

Dialog::Dialog(const Dialog &dialog)
{
  _speaker      = dialog._speaker;
  _ID           = dialog._ID;
  _questionType = dialog._questionType;
  _sentence     = dialog._sentence;
}

Dialog::Dialog(Dialog &&dialog)
{  
  _speaker      = std::move(dialog._speaker);
  _ID           = dialog._ID;
  _questionType = dialog._questionType;
  _sentence     = std::move(dialog._sentence);
}

Dialog &Dialog::operator=(Dialog &&dialog)
{
  if (&dialog == this)
  {
    return *this;
  }
  _speaker      = std::move(dialog._speaker);
  _ID           = dialog._ID;
  _questionType = dialog._questionType;
  _sentence     = std::move(dialog._sentence);
  return *this;
}

const std::string &Dialog::getSentence()
{
  return _sentence;
}

const std::string &Dialog::getSpeaker()
{
  return _speaker;
}

const unsigned int &Dialog::getID()
{
  return _ID;
}

const Question_Type &Dialog::getQuestionType()
{
  return _questionType;
}

void Dialog::record(std::string &FileName)
{
  FILE *fp = fopen(FileName.c_str(), "a");
  if (!fp)
  {
    return;
  }
  std::string log = _speaker + ": " + _sentence;

  fprintf(fp, "%s\n", log.c_str());

  fclose(fp);
}
