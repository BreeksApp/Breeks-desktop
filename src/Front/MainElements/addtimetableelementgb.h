#ifndef ADDTIMETABLEELEMENTGB_H
#define ADDTIMETABLEELEMENTGB_H

#include <QGroupBox>

class AddTimetableElementGB : public QGroupBox
{
	Q_OBJECT
public:
	AddTimetableElementGB(QWidget *parent = nullptr);
	void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // ADDTIMETABLEELEMENTGB_H
