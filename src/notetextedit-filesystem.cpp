#include <QDebug>

#include "notetextedit.h"

void NoteTextEdit::readFromFile()
{
  switch (nCurrentFile_) {
    case 1:
      nCurrentFile_ = 1;
      if (!file1_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file1_);
      break;
    case 2:
      nCurrentFile_ = 2;
      if (!file2_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      if (!file3_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      if (!file4_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      if (!file5_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      if (!file6_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(file6_);
      break;
    }
}

void NoteTextEdit::writeToFile()
{
  switch (nCurrentFile_) {
    case 1:
      nCurrentFile_ = 1;
      writeToFile(file1_);
      break;
    case 2:
      nCurrentFile_ = 2;
      writeToFile(file2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      writeToFile(file3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      writeToFile(file4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      writeToFile(file5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      writeToFile(file6_);
      break;
    }
}

void NoteTextEdit::readFromFile(QFile& file)
{
  QString text = file.readAll();
  //13 0000000000000 Hello, World!
  QTextStream out(&text);

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
    QChar line = text[i + jump];
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
  }
  file.flush();
  file.close();
}

void NoteTextEdit::writeToFile(QFile &file)
{
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
      qDebug() << "FILE OPENING CRASHED";
  }
  QTextStream in(&file);

  int charCounter = this->getCharCounter();
  in << charCounter << " ";
  for (int i = 0; i < charCounter; ++i) {
    in << this->getCharStyle(i);
  }

  QString text = this->toPlainText();
  in << " " << text;
  file.flush();
  file.close();
}

void NoteTextEdit::setNumberCurrentFile(int n)
{
  if (n >= 1 && n <= 6) {
    nCurrentFile_ = n;
  }
}
int NoteTextEdit::getNumberCurrentFile() const
{
  return nCurrentFile_;
}
