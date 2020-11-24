#include "notemark.h"

#include <QGraphicsDropShadowEffect>

NoteMark::NoteMark(QWidget *parent) :
	QPushButton(parent)
{
	this->setStyleSheet(
				"QPushButton {"
				"background-color: #FFFFFF;"
				"border-radius: 4px;}"

				"QPushButton:hover {"
				"background-color: #e6f6ff;"
				"border-radius: 4px;}");

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");
	this->setGraphicsEffect(effect);
}

void NoteMark::setSelectableStyle()
{
	this->setStyleSheet(
				"QPushButton {"
				"background-color: #81C4FF;"
				"border-radius: 4px;}"

				"QPushButton:hover {"
				"background-color: #e6f6ff;"
				"border-radius: 4px;}");
}

void NoteMark::setDefaultStyle()
{
	this->setStyleSheet(
				"QPushButton {"
				"background-color: #FFFFFF;"
				"border-radius: 4px;}"

				"QPushButton:hover {"
				"background-color: #e6f6ff;"
				"border-radius: 4px;}");
}
