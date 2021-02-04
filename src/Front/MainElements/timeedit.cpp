#include "timeedit.h"
#include <QFocusEvent>

TimeEdit::TimeEdit(QWidget *parent) :
	QTimeEdit(parent)
{
  this->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

void TimeEdit::wheelEvent(QWheelEvent *event) {
 //it's nessesary to avoid scrolling time when you are scrolling day
}


