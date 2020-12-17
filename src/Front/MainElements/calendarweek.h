#ifndef CALENDARWEEK_H
#define CALENDARWEEK_H

#include <QPushButton>
#include <QObject>

class CalendarWeek : public QPushButton
{
	Q_OBJECT
public:
	CalendarWeek(QWidget *parent = nullptr);

	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	QDateTime *date;

signals:
	void changeCalendarWeek(qint64);
};

#endif // CALENDARWEEK_H
