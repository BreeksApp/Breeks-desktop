#include "calendarweek.h"

#include <QDateTime>

CalendarWeek::CalendarWeek(QWidget *parent) :
	QPushButton(parent),
	date(new QDateTime)
{

}

void CalendarWeek::enterEvent(QEvent *event)
{
	this->setFixedSize(235, 30);
}

void CalendarWeek::leaveEvent(QEvent *event)
{
	this->setFixedSize(200, 30);
}

void CalendarWeek::mousePressEvent(QMouseEvent *event)
{
	emit changeCalendarWeek(date->toMSecsSinceEpoch());
}
