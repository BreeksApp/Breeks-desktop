#include "gentextedit.h"

void GenTextEdit::recieveUsername(const QString username) //SLOT
{
  username_ = username;
}

void GenTextEdit::fillFontStyleVector(int cursorPos, int count, int style)
{
  fontStyleVector_.insert(cursorPos, count, fontStyleValue_t(style));
}

int GenTextEdit::getCharStyle(int index) const
{
  if (index < 0 || index >= charCounter_) {
    qDebug() << "Index is out of range!";
    return 0;
  }
  return fontStyleVector_[index];
}

void GenTextEdit::setCharCounter(int value)
{
  charCounter_ = value;
}

int GenTextEdit::getCharCounter() const
{
  return charCounter_;
}
