#include "gentextedit.h"

void GenTextEdit::readFromDB(const int currentFile)
{
  QJsonObject textInfo = filesystem::readTextEdidFromDB(currentFile);
  QJsonArray jChars = textInfo.value("charStyleVector").toArray();
  QString text = textInfo.value("text").toString();

  charStyleVector_.clear();
  charCounter_ = jChars.size();

  QTextStream out(&text);
  QChar tmpChar;
  QTextCharFormat charFormat;
  charStyle_t ch;

  for (int i = 0; i < charCounter_; ++i) {
    QJsonObject jChar = jChars[i].toObject();
    charFormat.setFontWeight(QFont::Normal);
    setStylesToChar(ch, charFormat, jChar);
    int cursorPos = this->textCursor().position();
    this->fillCharStyleVector(cursorPos, 1, ch);
    out >> tmpChar;
    this->textCursor().insertText(static_cast<QString>(tmpChar), charFormat);

		QTextCursor c = this->textCursor();
		c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
		detailsColorText(c, ch.sColor);
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
		jChar.insert("underline", ch.underline);
		jChar.insert("strike", ch.strike);
		jChar.insert("item", ch.item);
		jChar.insert("star", ch.star);
		jChar.insert("sColor", ch.sColor);
		info.jArr.push_back(jChar);
  }

  info.text = this->toPlainText();
  filesystem::writeTextEditToDB(info, currentFile);
}
