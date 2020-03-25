#include "timetabletextedit.h"

TimetableTextEdit::TimetableTextEdit(QWidget *parent)
        :GenTextEdit(parent)
{
  this->clearCharStyleVector();
  for (charStyle_t ch: this->getCharStyleVector()) {
      qDebug() <<ch.bold;
  }
  this->clear();
  this->setCharCounter(0);
}

void TimetableTextEdit::fillCharsAndSetText(QString text, const QJsonArray jArr)
{
  this->clearCharStyleVector();
  this->setCharCounter(jArr.size());

  QTextStream out(&text);
\
  QChar tmpChar;
  charStyle_t ch;
 //qDebug() << text;
 //qDebug() << jArr;
  for (int i = 0; i < this->getCharCounter(); ++i) {
    detailsSetCharStyle(ch);
    QTextCharFormat charFormat;
    charFormat.setFontWeight(QFont::Normal);

    QJsonObject jChar = jArr[i].toObject();

    bool boldStatus = jChar.value("bold").toBool();
    bool italicStatus = jChar.value("italic").toBool();
    bool underlineStatus = jChar.value("underline").toBool();
    bool strikeStatus = jChar.value("strike").toBool();
    bool itemStatus = jChar.value("item").toBool();
    bool starStatus = jChar.value("star").toBool();
    QString color = jChar.value("sColor").toString();

    if (boldStatus == true) {
        detailsSetCharStyle(ch, charStyle::Bold);
        charFormat.setFontWeight(QFont::Bold);
    }
    if (italicStatus == true) {
        detailsSetCharStyle(ch, charStyle::Italic);
        charFormat.setFontItalic(true);
    }
    if (underlineStatus == true) {
        detailsSetCharStyle(ch, charStyle::Underline);
        charFormat.setFontUnderline(true);
    }
    if (strikeStatus == true) {
        detailsSetCharStyle(ch, charStyle::Strike);
        charFormat.setFontStrikeOut(true);
    }
      if (itemStatus == true) {
        detailsSetCharStyle(ch, charStyle::Item);
        charFormat.setFontWeight(QFont::Normal);
    }
      if (starStatus == true) {
        detailsSetCharStyle(ch, charStyle::Star);
        charFormat.setFontWeight(QFont::Normal);
    }
    ch.sColor = color;

    int cursorPos = this->textCursor().position();
    this->fillCharStyleVector(cursorPos, 1, ch);
    out >> tmpChar;
    this->textCursor().insertText(static_cast<QString>(tmpChar), charFormat);
    }
}

