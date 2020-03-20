#include "gentextedit.h"

void GenTextEdit::readFromDB(const int currentFile)
{
  charStyleVector_.clear();
  QJsonObject textInfo = filesystem::readTextEdidFromDB(currentFile);
  QJsonArray jChars = textInfo.value("charStyleVEctor").toArray();
  QString text = textInfo.value("text").toString();

  QTextStream out(&text);
  QChar tmpChar;

  charCounter_ = jChars.size();

  for (int i = 0; i < charCounter_; i++ ) {
    charStyle_t ch;
    QTextCharFormat charFormat;
    QJsonObject jChar = jChars[i].toObject();
    bool boldStatus = jChar.value("bold").toBool();
    bool italicStatus = jChar.value("italic").toBool();
    bool itemStatus = jChar.value("item").toBool();
    bool starStatus = jChar.value("star").toBool();
    bool strikeStatus = jChar.value("strike").toBool();
    bool underlineStatus = jChar.value("underline").toBool();
    QString color = jChar.value("sColor").toString();

    if (boldStatus == true) {
      detailsSetCharStyle(ch, 1);
      charFormat.setFontWeight(QFont::Bold);
    }
    if (italicStatus == true) {
      detailsSetCharStyle(ch, 2);
      charFormat.setFontItalic(true);
    }
    if (underlineStatus == true) {
      detailsSetCharStyle(ch, 3);
      charFormat.setFontUnderline(true);
    }
    if (strikeStatus == true) {
      detailsSetCharStyle(ch, 4);
      charFormat.setFontStrikeOut(true);
    }
    if (itemStatus == true) {
      detailsSetCharStyle(ch, 5);
      charFormat.setFontWeight(QFont::Normal);
    }
    if (starStatus == true) {
      detailsSetCharStyle(ch, 6);
      charFormat.setFontWeight(QFont::Normal);
    }

    ch.sColor = color;
    int cursorPos = this->textCursor().position();
    this->fillCharStyleVector(cursorPos, 1, ch);
    out >> tmpChar;
    this->textCursor().insertText(static_cast<QString>(tmpChar), charFormat);
  }
}

void GenTextEdit::writeToDB(const int currentFile)
{
  textInfo_t info;
  QJsonArray jChars;
  foreach(charStyle_t ch, charStyleVector_) {
    QJsonObject jChar;
    jChar.insert("bold", ch.bold);
    jChar.insert("italic", ch.italic);
    jChar.insert("item", ch.item);
    jChar.insert("sColor", ch.sColor);
    jChar.insert("star", ch.star);
    jChar.insert("strike", ch.strike);
    jChar.insert("underline", ch.underline);
    info.jArr.push_back(jChar);
  }

  info.text = this->toPlainText();
  filesystem::writeTextEditToDB(info, currentFile);
}
