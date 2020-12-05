#include "Front/mainwindow.h"

int MainWindow::addNewElementToArray(const elementData_t& newElement, const int index)
{
	qDebug() << "ARRAY";
	//TODO: UPDATE DATE REQUEST HERE
	if (newElement.idOnServer != -1) {
		//server request
		QJsonObject json;
		json.insert("tagColorNum", newElement.tagColorNum);
		json.insert("mainText", newElement.text);
		json.insert("timeFrom", newElement.timeStart);
		json.insert("timeTo", newElement.timeEnd);
		json.insert("date", QDateTime(arrDays_[index].date).toMSecsSinceEpoch());
		QJsonDocument jsonDoc(json);

		QUrl url = QUrl(Network::serverUrl + Network::editTTElementUrl + '/' + QString::number(newElement.idOnServer));
		server->sendPutRequestWithBearerToken(url , jsonDoc.toJson(), userData->getAccessToken());
	}
	//---------

  if (arrDaysData_[index].size() == 0) {
    arrDaysData_[index].push_back(newElement);
    return 0;
  }

  iterType start = arrDaysData_[index].begin();
  iterType end = arrDaysData_[index].end();

  int newElementIndex = 0;

  for (iterType j = start; j < end; ++j) {
    newElementIndex++;

    if (newElement.timeStart > j->timeStart) {
      if (j + 1 == end) {
        arrDaysData_[index].push_back(newElement);
        break;
      }
    }
    else if (newElement.timeStart < j->timeStart) {
      arrDaysData_[index].insert(j, newElement);
      break;
    }
    else if (newElement.timeStart == j->timeStart && newElement.timeEnd < j->timeEnd) {
      arrDaysData_[index].insert(j, newElement);
      break;
    }
    else if ((newElement.timeEnd == j->timeEnd) && (newElement.text < j->text)) {
      arrDaysData_[index].insert(j, newElement);
      break;
    }

    if (j + 1 == end) {
      arrDaysData_[index].push_back(newElement);
      break;
    }
  }

  return newElementIndex;
}

void MainWindow::addNewElementToLayout(const int index, const int newElementIndex)
{
  //clear layout
  for (int j = 0; j < arrDays_[index].elementsCount; ++j) {
    auto item = arrDays_[index].layoutDayElements->itemAt(0);
    arrDays_[index].layoutDayElements->removeItem(item);
    arrDays_[index].layoutDayElements->removeWidget(item->widget());
    delete item->widget();
    delete item;
    arrDays_[index].layoutDayElements->update();
  }

  ++arrDays_[index].elementsCount;

  for (int j = 0; j < arrDays_[index].elementsCount; ++j) {
    //create new element object
    ElementTemplate *elem = new ElementTemplate;

		connect(server, SIGNAL(initTEidOnServer(long)), elem, SLOT(setId(long)));
		connect(elem, SIGNAL(updateId(int, int, long)), this, SLOT(updateTTElementIdOnServer(int, int, long)));
		connect(elem, SIGNAL(sendEditRequest(int, int)), this, SLOT(sendPutRequest(int, int)));

    connect(elem, SIGNAL(sendMimeData(const elementData_t, const QPixmap)), this, SLOT(recieveMimeData(const elementData_t, const QPixmap)));
		connect(elem, SIGNAL(dropNoChanges()), this, SLOT(dropNoChanges()));
		connect(elem, SIGNAL(defineDayMoveFrom(int, QString)), this, SLOT (defineDayMoveFrom(int, QString)));
		connect(elem, SIGNAL(deleteItem(int, int, bool)), this, SLOT(recieveDayAndElementIndex(int, int, bool)));

    elem->setText(arrDaysData_[index][j].text, arrDaysData_[index][j].charStyleVector);
		elem->setTime(arrDaysData_[index][j].timeStart, arrDaysData_[index][j].timeEnd);

		elem->setTagColor(arrDaysData_[index][j].tagColor);
		elem->setIdOnServer(arrDaysData_[index][j].idOnServer);
    elem->setDayAndElementIndex(index, j);

    //for deleting element from arrDaysData_
		connect(elem, SIGNAL(sendDayAndElementIndex(const int, const int, bool)),
					this, SLOT(recieveDayAndElementIndex(const int, const int, bool)));
    //for updating info about element's tag color
		connect(elem, SIGNAL(sendDayAndElementIndexAndTagColor(const int, const int, const int)),
					this, SLOT(recieveDayAndElementIndexAndTagColor(const int, const int, const int)));
		//for change day heigth after scaling element
		connect(elem, SIGNAL(changeElementsLayoutHeight(const int, const int)),
					this, SLOT(changeElementsLayoutHeight(const int, const int)));
		//for changing time
		connect(elem, SIGNAL(changeTime(int, int, QString, QString)),
						this, SLOT(recieveTimetableElementDayAndElemIndexAndTime(int, int, QString, QString)));
		connect(elem, SIGNAL(changeText(int, int, QString, QVector<charStyle_t>)),
						this, SLOT(recieveTimetableDayAndElementIndexAndText(int, int, QString, QVector<charStyle_t>)));

		arrDays_[index].layoutDayElements->addWidget(elem, Qt::AlignCenter);

    if (j == newElementIndex) {
      const int a = 150 * newElementIndex; //150 is lucky coefficient
      arrDays_[index].scrollArea->ensureVisible(0, a);
    }
  }
}
