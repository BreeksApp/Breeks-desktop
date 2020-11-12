#include "Front/mainwindow.h"
#include "Front/GeneralTextEdit/gentextedit.h"
#include <QDebug>

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

	for (QJsonValue elem: day) {
    QJsonObject jElem = elem.toObject();

    elementData_t elemData;
    elemData.text = jElem.value("text").toString();
		//QColor color(jElem.value("color").toString());
		elemData.tagColor = jElem.value("tagColor").toString();

		qDebug() << "READ: " << elemData.tagColor;

    elemData.timeStart = jElem.value("timeStart").toString();
    elemData.timeEnd = jElem.value("timeEnd").toString();

    QJsonArray jChars = jElem.value("charStyleVector").toArray();
    charStyle_t ch;
    QTextCharFormat charFormat;

    foreach (QJsonValue jCharr, jChars) {
      QJsonObject jChar = jCharr.toObject();
      GenTextEdit::setStylesToChar(ch, charFormat, jChar);
      elemData.charStyleVector.push_back(ch);
    }
    recieveTimeTableZoneData(arr, DAYS_COUNT, elemData);
  }
}

void MainWindow::writeElementsDataToFile(const int index)
{
  for (int i = 0; i < arrDaysData_[index].size(); ++i) {
    ElementTemplate *a = qobject_cast<ElementTemplate*>(arrDays_[index].layoutDayElements->itemAt(i)->widget());
    arrDaysData_[index][i].text = a->getText();
		arrDaysData_[index][i].tagColor = a->getTagColor();
    arrDaysData_[index][i].charStyleVector = a->getCharStyleVector();
  }

  //write data to file
  QJsonArray jDayElements;

  for (elementData_t element : arrDaysData_[index]) {
		//QColor color = element.palette.color(QPalette::Button);
    QJsonObject jElem;
    jElem.insert("text", element.text);
    jElem.insert("timeStart", element.timeStart);
    jElem.insert("timeEnd", element.timeEnd);
		jElem.insert("tagColor", element.tagColor);

		qDebug() << element.tagColor;

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
			jChar.insert("spellChecker", ch.spellChecker);
      jChars.push_back(jChar);
    }
		jElem.insert("charStyleVector", jChars);
		jDayElements.push_back(jElem);
  }
  filesystem::writeTimeTableToDB(jDayElements, index);
}
