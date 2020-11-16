//VIEW

#include "addbuttonhover.h"

#include <QGraphicsDropShadowEffect>

AddButtonHover::AddButtonHover(QWidget *parent) :
  QPushButton (parent)
{
  this->setStyleSheet(styleSheetDefault);
}

void AddButtonHover::enterEvent(QEvent *event)
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");
	this->setGraphicsEffect(effect);

	QPushButton::enterEvent(event);
}

void AddButtonHover::leaveEvent(QEvent *event)
{
	QPushButton::leaveEvent(event);
	this->setGraphicsEffect(nullptr);
}
