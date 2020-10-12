//VIEW

#include "addbuttonhover.h"

AddButtonHover::AddButtonHover(QWidget *parent) :
  QPushButton (parent)
{
  this->setStyleSheet(styleSheetDefault);
}

void AddButtonHover::enterEvent(QEvent *event)
{
  this->setStyleSheet(styleSheetHover);
  QPushButton::enterEvent(event);
}

void AddButtonHover::leaveEvent(QEvent *event)
{
  QPushButton::leaveEvent(event);
  this->setStyleSheet(styleSheetDefault);
}
