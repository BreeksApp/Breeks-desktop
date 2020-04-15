#include "daywidget.h"

DayWidget::DayWidget(QWidget *parent) : QWidget(parent)
{
  setAcceptDrops(true);
}

void DayWidget::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}

void DayWidget::dropEvent(QDropEvent *event)
{
  elementData_t elemData;
  QByteArray data = event->mimeData()->data("elemData");
  QDataStream out(&data, QIODevice::ReadOnly);
  out >> elemData.text >> elemData.timeStart >> elemData.timeEnd >> elemData.palette >> dragPos_;
  QByteArray indexes = event->mimeData()->data("indexes");
  QDataStream outIndexes(&indexes, QIODevice::ReadOnly);
  outIndexes >> dayIndex_ >> elemIndex_;

  QByteArray charVector = event->mimeData()->data("charVector");
  QDataStream outVector(&charVector, QIODevice::ReadOnly);
  int size = 0;
  outVector >> size;
  for (int i = 0; i < size; i++) {
    charStyle_t ch;
    outVector >> ch.bold >> ch.italic >> ch.underline >> ch.strike >> ch.item >> ch.star >> ch.sColor;
    elemData.charStyleVector.push_back(ch);
  }

  if (dayNumber_ != dayIndex_) {
   emit dropElement(dayNumber_, dayIndex_, elemIndex_, elemData);
   emit sendDayAndElementIndex(dayIndex_, elemIndex_);
  }

  event->acceptProposedAction();
}

void DayWidget::dragMoveEvent(QDragMoveEvent *event)
{
  event->acceptProposedAction();
}

int DayWidget::getDayNumber()
{
  return dayNumber_;
}

void DayWidget::setDayNumber(const int numb)
{
  dayNumber_ = numb;
}
