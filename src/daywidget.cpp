#include "daywidget.h"

DayWidget::DayWidget(QWidget *parent) : QWidget(parent)
{
  setAcceptDrops(true);
}

void DayWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("NO");
    event->acceptProposedAction();
}

void DayWidget::dropEvent(QDropEvent *event)
{
  qDebug("YEES");
  emit dropElement(dayNumber_);
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
