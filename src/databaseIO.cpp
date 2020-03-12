#include "mainwindow.h"
#include "notetextedit.h"
#include <QDebug>


//--------------------TimeTable IO-----------------------(
// Doesn't work with DB yet
void MainWindow::setStatesFromFileLastVisit()
{
  if (!fileLastVisit_.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "FILE LAST_VISIT OPENING CRASHED";
  }
  QString text = fileLastVisit_.readAll();
  QTextStream stream(&text);

  int nLastNotePage = 1;
  int iTmp = 0;
  stream >> iTmp;
  if (iTmp >= 1 && iTmp <= 6) {
    nLastNotePage = iTmp;
  }
  noteChangePage(nLastNotePage);

  QString imageName = defaultImageName_;
  QString sTmp = "";
  stream >> sTmp;
  if (QString::compare(sTmp, defaultImageName_) != 0) {
    if (openImageFromDisk(sTmp)) {
      imageName = sTmp;
    }
  }
  setImage(imageName);

  fileLastVisit_.flush();
  fileLastVisit_.close();
}

void MainWindow::writeDataToFileLastVisit()
{
  if (!fileLastVisit_.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    qDebug() << "FILE LAST_VISIT OPENING CRASHED";
  }
  QTextStream out(&fileLastVisit_);

  const int nNotePage = ui->note->getNumberCurrentFile();
  out << nNotePage << " ";

  out << currentImageName_;

  fileLastVisit_.flush();
  fileLastVisit_.close();
}

void MainWindow::readElementsDataFromFile(const int index)
{
  switch (index) {
    case 0 :
      readElementsDataFromFile(fileMon_, index);
      break;
    case 1 :
      readElementsDataFromFile(fileTue_, index);
      break;
    case 2 :
      readElementsDataFromFile(fileWed_, index);
      break;
    case 3 :
      readElementsDataFromFile(fileThu_, index);
      break;
    case 4 :
      readElementsDataFromFile(fileFri_, index);
      break;
    case 5 :
      readElementsDataFromFile(fileSat_, index);
      break;
  }
}

void MainWindow::readElementsDataFromFile(QFile &file, const int index)
{
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "FILE OPENING CRASHED";
  }

  QString data = file.readAll();
    //13 0000000000000 Hello, World!
  QTextStream out(&data);

  int count = 0;
  out >> count;

  bool arr[DAYS_COUNT];
  for (int i = 0; i < DAYS_COUNT; ++i) {
    if (i != index) {
      arr[i] = false;
    }
    else {
      arr[i] = true;
    };
  }

  int h = 0, m = 0, s = 0;
  QString sColor = "";

  QChar trash;
  out >> trash;

  for (int i = 0; i < count; ++i) {
    QChar ch = '!';
    sColor = "";

    ElementData newElement;

    while (ch != ' ') {
      out >> ch;
      if (ch != ' ') {
        sColor += ch;
      }
    }
    QColor color(sColor);
    newElement.palette.setColor(QPalette::Button, color);

    out >> h >> trash >> m;
    newElement.timeStart = QTime(h, m, s).toString().remove(5, 3);

    out >> h >> trash >> m >> trash;
    newElement.timeEnd = QTime(h, m, s).toString().remove(5, 3);

    while (ch != '\n') {
      out >> ch;
      if (ch != '\n') {
        newElement.text += ch;
      }
    }

    recieveTimeTableZoneData(arr, DAYS_COUNT, newElement);
  }

  file.close();
}

void MainWindow::writeElementsDataToFile(const int index)
{
  switch (index) {
    case 0 :
      writeElementsDataToFile(fileMon_, index);
      break;
    case 1 :
      writeElementsDataToFile(fileTue_, index);
      break;
    case 2 :
      writeElementsDataToFile(fileWed_, index);
      break;
    case 3 :
      writeElementsDataToFile(fileThu_, index);
      break;
    case 4 :
      writeElementsDataToFile(fileFri_, index);
      break;
    case 5 :
      writeElementsDataToFile(fileSat_, index);
      break;
  }
}

void MainWindow::writeElementsDataToFile(QFile &file, const int index)
{
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    qDebug() << "FILE OPENING CRASHED";
  }
  QTextStream in(&file);

  const int count = arrDaysData_[index].size();
  in << count << '\n';

  //write update data to array from application form
  for (int i = 0; i < arrDaysData_[index].size(); ++i) {
    ElementTemplate *a = qobject_cast<ElementTemplate*>(arrDays_[index].layoutDayElements->itemAt(i)->widget());
    arrDaysData_[index][i].text = a->getText();
    arrDaysData_[index][i].palette = a->getColor();
  }

  //write data to file
  for (ElementData element : arrDaysData_[index]) {
    QColor color = element.palette.color(QPalette::Button);
    in << color.name() << ' ';

    in << element.timeStart << ' ' << element.timeEnd << ' ';
    in << element.text << '\n';
  }

  file.flush();
  file.close();
}

//----------------------TextEdit IO--------------------------------
void NoteTextEdit::readFromFile()
{
  QJsonDocument jDoc = QJsonDocument::fromJson(getDataFromDB().toUtf8());
  QJsonObject jObject = jDoc.object();
  QJsonObject notes = jObject.value("textEdit").toObject();

  parseDataBase(notes);

  switch (nCurrentFile_) {
    case 1:
      nCurrentFile_ = 1;
      readFromFile(note1_);
      break;
    case 2:
      nCurrentFile_ = 2;
      readFromFile(note2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      readFromFile(note3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      readFromFile(note4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      readFromFile(note5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      readFromFile(note6_);
      break;
    }
}

void NoteTextEdit::writeToFile()
{
  QJsonDocument jDoc = QJsonDocument::fromJson(getDataFromDB().toUtf8());
  QJsonObject jObject = jDoc.object();
  QJsonObject notes = jObject.value("textEdit").toObject();

  parseDataBase(notes);

  switch (nCurrentFile_) {
    case 1:
      nCurrentFile_ = 1;
      writeToFile(jDoc, jObject, notes, note1_);
      break;
    case 2:
      nCurrentFile_ = 2;
      writeToFile(jDoc, jObject, notes, note2_);
      break;
    case 3:
      nCurrentFile_ = 3;
      writeToFile(jDoc, jObject, notes, note3_);
      break;
    case 4:
      nCurrentFile_ = 4;
      writeToFile(jDoc, jObject, notes, note4_);
      break;
    case 5:
      nCurrentFile_ = 5;
      writeToFile(jDoc, jObject, notes, note5_);
      break;
    case 6:
      nCurrentFile_ = 6;
      writeToFile(jDoc, jObject, notes, note6_);
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
}

void NoteTextEdit::writeToFile(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &notes, QJsonObject &note)
{
  note.insert("charCount", this->getCharCounter());
  int charCounter = this->getCharCounter();
  QString charState;
  for (int i = 0; i < charCounter; ++i) {
    charState += QString::number(this->getCharStyle(i));
  }
  note.insert("charState", charState);
  note.insert("charCounter", charCounter);
  note.insert("text", this->toPlainText());

  notes.insert("note" + QString::number(nCurrentFile_), note);
  jObject.insert("textEdit", notes);
  jDoc.setObject(jObject);
  QString strJson(jDoc.toJson(QJsonDocument::Compact));
  QSqlQuery query("UPDATE Employee SET Notes ='"+strJson+"' WHERE Username ='1'");
}

QString NoteTextEdit::getDataFromDB()
{
  QString queryString = "SELECT Notes FROM Employee WHERE Username='1'";
  QString data;
  QSqlQuery query;
  query.exec(queryString);
  while (query.next()) {
    QSqlRecord record = query.record();
    data = record.value(0).toString();
  }
  return data;
}

void NoteTextEdit::parseDataBase(QJsonObject &notes)
{
  note1_ = notes.value("note1").toObject();
  note2_ = notes.value("note2").toObject();
  note3_ = notes.value("note3").toObject();
  note4_ = notes.value("note4").toObject();
  note5_ = notes.value("note5").toObject();
  note6_ = notes.value("note6").toObject();
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

