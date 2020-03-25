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

  bool arr[DAYS_COUNT];
  for (int i = 0; i < DAYS_COUNT; ++i) {
    if (i != index) {
      arr[i] = false;
    }
    else {
      arr[i] = true;
    }
  }

  QJsonArray day = filesystem::readTimeTableFromDB(index);
  //qDebug() << day;
  //qDebug() << "#";
  for (QJsonValue elem: day) {
    QJsonObject jElem = elem.toObject();
    //qDebug() << jElem;
    elementData_t elemData;
    elemData.text = jElem.value("text").toString();
    QColor color(jElem.value("color").toString());
    elemData.palette.setColor(QPalette::Button, color);
    elemData.timeStart = jElem.value("timeStart").toString();
    elemData.timeEnd = jElem.value("timeEnd").toString();


    QJsonArray jChars = jElem.value("charStyleVector").toArray();

    charStyle_t ch;

    foreach (QJsonValue jCharr, jChars) {
      QJsonObject jChar = jCharr.toObject();
      GenTextEdit::detailsSetCharStyle(ch);
      bool boldStatus = jChar.value("bold").toBool();
      bool italicStatus = jChar.value("italic").toBool();
      bool underlineStatus = jChar.value("underline").toBool();
      bool strikeStatus = jChar.value("strike").toBool();
      bool itemStatus = jChar.value("item").toBool();
      bool starStatus = jChar.value("star").toBool();
      QString color = jChar.value("sColor").toString();

      if (boldStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Bold);
      }
      if (italicStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Italic);
      }
      if (underlineStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Underline);
      }
      if (strikeStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Strike);
      }
      if (itemStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Item);
      }
      if (starStatus == true) {
             GenTextEdit::detailsSetCharStyle(ch, charStyle::Star);
      }
      ch.sColor = color;

      elemData.charStyleVector.push_back(ch);
    }
    //qDebug() <<elemData.text;
    //qDebug() <<elemData.color;
    //qDebug() <<elemData.timeEnd;
    //qDebug() <<elemData.timeStart;
    //qDebug() <<elemData.charStyleVector;
    //qDebug() <<jChars;

    recieveTimeTableZoneData(arr, DAYS_COUNT, elemData, jChars);
  }
}

void MainWindow::writeElementsDataToFile(const int index)
{
  for (int i = 0; i < arrDaysData_[index].size(); ++i) {
    ElementTemplate *a = qobject_cast<ElementTemplate*>(arrDays_[index].layoutDayElements->itemAt(i)->widget());
    arrDaysData_[index][i].text = a->getText();
    arrDaysData_[index][i].palette = a->getColor();
  }

  //write data to file
  QJsonArray jDayElements;

  for (elementData_t element : arrDaysData_[index]) {
    QColor color = element.palette.color(QPalette::Button);
    QJsonObject jElem;
    jElem.insert("text", element.text);
    jElem.insert("timeStart", element.timeStart);
    jElem.insert("timeEnd", element.timeEnd);
    jElem.insert("color", color.name());

    QJsonArray jChars;
    foreach(charStyle_t ch, element.charStyleVector) {
      QJsonObject jChar;
      jChar.insert("bold", ch.bold);
      jChar.insert("italic", ch.italic);
      jChar.insert("underline", ch.underline);
      jChar.insert("strike", ch.strike);
      jChar.insert("item", ch.item);
      jChar.insert("star", ch.star);
      jChar.insert("sColor", ch.sColor);
      jChars.push_back(jChar);
    }
  jElem.insert("charStyleVector", jChars);
  jDayElements.push_back(jElem);
  }
  filesystem::writeTimeTableToDB(jDayElements, index);
}
