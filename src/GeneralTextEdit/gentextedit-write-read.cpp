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
	charStyle_t ch;

	for (int i = 0; i < charCounter_; ++i) {
		detailsSetCharStyle(ch);
		QTextCharFormat charFormat;
		charFormat.setFontWeight(QFont::Normal);

		QJsonObject jChar = jChars[i].toObject();

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
