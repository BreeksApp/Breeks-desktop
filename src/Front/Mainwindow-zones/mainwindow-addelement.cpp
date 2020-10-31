#include "Front/mainwindow.h"

int MainWindow::addNewElementToArray(const elementData_t& newElement, const int index)
{
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

    connect(elem, SIGNAL(sendMimeData(const elementData_t, const QPixmap)), this, SLOT(recieveMimeData(const elementData_t, const QPixmap)));
		connect(elem, SIGNAL(dropNoChanges()), this, SLOT(dropNoChanges()));

    elem->setText(arrDaysData_[index][j].text, arrDaysData_[index][j].charStyleVector);

    elem->setTime(arrDaysData_[index][j].timeStart, arrDaysData_[index][j].timeEnd);
    elem->setPalette(arrDaysData_[index][j].palette);
    elem->setDayAndElementIndex(index, j);

    //for deleting element from arrDaysData_
    connect(elem, SIGNAL(sendDayAndElementIndex(const int, const int)),
          this, SLOT(recieveDayAndElementIndex(const int, const int)));
    //for updating info about element's tag color
    connect(elem, SIGNAL(sendDayAndElementIndexAndTagColor(const int, const int, const QPalette)),
          this, SLOT(recieveDayAndElementIndexAndTagColor(const int, const int, const QPalette)));

		arrDays_[index].layoutDayElements->addWidget(elem, Qt::AlignCenter);

    if (j == newElementIndex) {
      const int a = 150 * newElementIndex; //150 is lucky coefficient
      arrDays_[index].scrollArea->ensureVisible(0, a);
    }
  }
}
