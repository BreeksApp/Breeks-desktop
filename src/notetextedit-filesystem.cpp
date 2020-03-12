#include <QDebug>

#include "notetextedit.h"

void NoteTextEdit::readFromFile()
{
  QString queryString = "SELECT Notes FROM Employee WHERE Username='1'";
  QString data;
  QSqlQuery query;
  query.exec(queryString);
  while (query.next()) {
    QSqlRecord record = query.record();
    data = record.value(0).toString();
  }

  jDoc_ = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject jObject = jDoc_.object();
  QJsonObject notes = jObject.value("textEdit").toObject();
  note1_ = notes.value("note1").toObject();
  note2_ = notes.value("note2").toObject();
  note3_ = notes.value("note3").toObject();
  note4_ = notes.value("note4").toObject();
  note5_ = notes.value("note5").toObject();
  note6_ = notes.value("note6").toObject();

  switch (nCurrentFile_) {
    case 1:
      nCurrentFile_ = 1;
      if (!file1_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note1_);
      break;
    case 2:
      nCurrentFile_ = 2;
      if (!file2_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      if (!file3_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      if (!file4_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      if (!file5_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      if (!file6_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "FILE OPENING CRASHED";
      }
      readFromFile(note6_);
      break;
    }
}

void NoteTextEdit::writeToFile()
{
  QString queryString = "SELECT Notes FROM Employee WHERE Username='1'";
  QString data;
  QSqlQuery query;
  query.exec(queryString);
  while (query.next()) {
    QSqlRecord record = query.record();
    data = record.value(0).toString();
  }

  jDoc_ = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject jObject = jDoc_.object();
  QJsonObject notes = jObject.value("textEdit").toObject();
  note1_ = notes.value("note1").toObject();
  note2_ = notes.value("note2").toObject();
  note3_ = notes.value("note3").toObject();
  note4_ = notes.value("note4").toObject();
  note5_ = notes.value("note5").toObject();
  note6_ = notes.value("note6").toObject();

  switch (nCurrentFile_) {
    case 1: {
      nCurrentFile_ = 1;
      writeToFile(note1_);
      notes.insert("note1", note1_);
      jObject.insert("textEdit", notes);
      jDoc_.setObject(jObject);
      QString strJson(jDoc_.toJson(QJsonDocument::Compact));
      query.exec("UPDATE Employee SET Notes ='"+strJson+"' WHERE Username ='1'");
      break;
    }
    case 2:
      nCurrentFile_ = 2;
      writeToFile(note2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      writeToFile(note3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      writeToFile(note4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      writeToFile(note5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      writeToFile(note6_);
      break;
    }
}

void NoteTextEdit::readFromFile(QJsonObject& object)
{
  int charCount = object.value("charCount").toInt();
  QString chars = QString::number(charCount);
  QString charState = object.value("charState").toString();
  QString textChar = object.value("text").toString();
  QString info = chars;
  info.append(" ");
  info.append(charState);
  info.append(" ");
  info.append(textChar);
  qDebug() << info;
  //QString text = file.readAll();
  //13 0000000000000 Hello, World!
  QTextStream out(&info);

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
    QChar line = info[i + jump];
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
  }
  //file.flush();
  //file.close();
}

void NoteTextEdit::writeToFile(QJsonObject &object)
{
    /*
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
      qDebug() << "FILE OPENING CRASHED";
  }
  */
  //QTextStream in(&file);

  object.insert("charCount", this->getCharCounter());
  int charCounter = this->getCharCounter();
  QString charState;
  //in << charCounter << " ";
  for (int i = 0; i < charCounter; ++i) {
    charState += QString::number(this->getCharStyle(i));
  }
  object.insert("charState", charState);
  object.insert("charCounter", charCounter);
  object.insert("text", this->toPlainText());
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
