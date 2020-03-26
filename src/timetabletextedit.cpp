#include "timetabletextedit.h"

TimetableTextEdit::TimetableTextEdit(QWidget *parent)
        :GenTextEdit(parent)
{
  this->clearCharStyleVector();
  this->clear();
  this->setCharCounter(0);
}

void TimetableTextEdit::fillCharsAndSetText(QString text, const QVector<charStyle_t>& arr)
{
  this->clearCharStyleVector();
  this->setCharCounter(arr.size());

  QJsonArray jArr;

  for (charStyle_t ch: arr) {
    QJsonObject jChar;
    jChar.insert("bold", ch.bold);
    jChar.insert("italic", ch.italic);
    jChar.insert("underline", ch.underline);
    jChar.insert("strike", ch.strike);
    jChar.insert("item", ch.item);
    jChar.insert("star", ch.star);
    jChar.insert("sColor", ch.sColor);
    jArr.push_back(jChar);
  }

  QTextStream out(&text);
  QChar tmpChar;
  charStyle_t ch;
  QTextCharFormat charFormat;

  for (int i = 0; i < this->getCharCounter(); ++i) {
    QJsonObject jChar = jArr[i].toObject();
    charFormat.setFontWeight(QFont::Normal);
    GenTextEdit::setStylesToChar(ch, charFormat, jChar);
    int cursorPos = this->textCursor().position();
    this->fillCharStyleVector(cursorPos, 1, ch);
    out >> tmpChar;
    this->textCursor().insertText(static_cast<QString>(tmpChar), charFormat);
  }
}

