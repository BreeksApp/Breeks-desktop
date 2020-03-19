#include "gentextedit.h"

/*void GenTextEdit::readFromDB(const int currentFile)
{
		QString textInfo = filesystem::readTextEdidFromDB(currentFile);
		QTextStream out(&textInfo);

    int tmp = 0;
    out >> tmp;
    int charCounter = tmp;

    this->setCharCounter(charCounter);
    int lengthCharCounter = 0;
    while (tmp != 0) {
      ++lengthCharCounter;
      tmp /= 10;
    }

    QChar ch;
    out >> ch; //read waste space
    //jump - for correct access to text chars
    int jump = lengthCharCounter + 2 + charCounter;

    //write fontStyle in vector
    //and write to TextEdit text with itself font format
    for (int i = 0; i < charCounter; ++i) {
      QChar style;
      out >> style;
      QChar line = textInfo[i + jump];
      QTextCharFormat charFormat;
      int cursorPos = this->textCursor().position();

      if (style == '0') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Normal);
        charFormat.setFontWeight(QFont::Normal);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '1') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Bold);
        charFormat.setFontWeight(QFont::Bold);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '2') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Italic);
        charFormat.setFontItalic(true);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '3') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Underline);
        charFormat.setFontUnderline(true);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '4') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Strike);
        charFormat.setFontStrikeOut(true);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '5') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Item);
        charFormat.setFontWeight(QFont::Normal);
        this->textCursor().insertText(static_cast<QString>(line), charFormat);
      }
      else if (style == '6') {
        this->fillFontStyleVector(cursorPos, 1, this->fontStyleValue_t::Star);
        //charFormat.setFontWeight(QFont::Normal);
        QString color = "#ff3366";
        QString html = "<font color=" + color + ">" + warrningSign_ + "</font>";
        this->setTextColor(QColor(0, 0, 0));
        this->textCursor().insertHtml(html);
      }
    }
}

void GenTextEdit::writeToDB(const int currentFile)
{
  textInfo_t info;
  info.charCount = this->getCharCounter();
  QString charState;
  for (int i = 0; i < info.charCount; ++i) {
    info.charState += QString::number(this->getCharStyle(i));
  }
  info.text = this->toPlainText();

  filesystem::writeTextEditToDB(info, currentFile);
}*/
