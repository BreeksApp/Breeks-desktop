#include "gentextedit.h"

void GenTextEdit::recieveUsername(const QString username) //SLOT
{
  username_ = username;
}

int GenTextEdit::getNumberCurrentFile()
{
    return nCurrentFile_;
}

void GenTextEdit::clearCharStyleVector()
{
  charStyleVector_.clear();
}

QVector<charStyle_t> GenTextEdit::getCharStyleVector()
{
    return charStyleVector_;
}
void GenTextEdit::setNumberCurrentFile(const int n)
{
  if (n >= 1 && n <= 6) {
    nCurrentFile_ = n;
  }
}

void GenTextEdit::fillCharStyleVector(int cursorPos, int count, charStyle_t ch)
{
    charStyleVector_.insert(cursorPos, count, ch);
}

void GenTextEdit::fillCharStyleVector(charStyle_t ch)
{
   charStyleVector_.push_back(ch);
}

int GenTextEdit::getCharStyle(const int index) const
{
  if (index < 0 || index >= charCounter_) {
    qDebug() << "Index is out of range!";
    return 0;
  }
    //return charStyleVector_[index];
}

int GenTextEdit::getCharCounter() const
{
  return charCounter_;
}
void GenTextEdit::setCharCounter(int value)
{
  charCounter_ = value;
}
