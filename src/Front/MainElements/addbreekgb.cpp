#include "addbreekgb.h"
#include <QKeyEvent>

AddBreekGB::AddBreekGB(QWidget *parent) :
	QGroupBox(parent)
{
}

void AddBreekGB::keyPressEvent(QKeyEvent *event)
{
	qDebug("!");
	if (event->key() == Qt::Key_Escape) {
		emit focusOut();
		this->hide();
	}
	else {
		QGroupBox::keyPressEvent(event);
	}

}

void AddBreekGB::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit focusOut();
	this->hide();
}
