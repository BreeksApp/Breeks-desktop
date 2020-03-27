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


void GenTextEdit::setStylesToChar(charStyle_t& ch, QTextCharFormat& charFormat, const QJsonObject jChar)
{
  GenTextEdit::detailsSetCharStyle(ch);
  bool boldStatus = jChar.value("bold").toBool();
  bool italicStatus = jChar.value("italic").toBool();
  bool underlineStatus = jChar.value("underline").toBool();
  bool strikeStatus = jChar.value("strike").toBool();
  bool itemStatus = jChar.value("item").toBool();
  bool starStatus = jChar.value("star").toBool();
  QString color = jChar.value("sColor").toString();

  if (boldStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Bold);
    charFormat.setFontWeight(QFont::Bold);
  }
  if (italicStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Italic);
    charFormat.setFontItalic(true);
  }
  if (underlineStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Underline);
    charFormat.setFontUnderline(true);
  }
  if (strikeStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Strike);
    charFormat.setFontStrikeOut(true);
  }
  if (itemStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Item);
    charFormat.setFontWeight(QFont::Normal);
  }
  if (starStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Star);
    charFormat.setFontWeight(QFont::Normal);
  }
  ch.sColor = color;
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
