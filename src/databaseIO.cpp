#include "mainwindow.h"
#include "gentextedit.h"
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

void GenTextEdit::setNumberCurrentFile(int n)
{
  if (n >= 1 && n <= 6) {
    nCurrentFile_ = n;
  }
}
int GenTextEdit::getNumberCurrentFile()
{
  return nCurrentFile_;
}

void GenTextEdit::readFromDB(const int currentFile)
{
		textInfoForRead_ = filesystem::readTextEdidFromDB(currentFile);
		QTextStream out(&textInfoForRead_);

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
			QChar line = textInfoForRead_[i + jump];
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
        QString html = "<font color=" + color + ">*</font>";
        this->setTextColor(QColor(0, 0, 0));
        this->textCursor().insertHtml(html);
      }
    }
}

void GenTextEdit::writeToDB(const int currentFile)
{
  NoteInfo info;
  info.charCount = this->getCharCounter();
  QString charState;
  for (int i = 0; i < info.charCount; ++i) {
    info.charState += QString::number(this->getCharStyle(i));
  }
  info.text = this->toPlainText();

  filesystem::writeTextEditToDB(info, currentFile);
}
