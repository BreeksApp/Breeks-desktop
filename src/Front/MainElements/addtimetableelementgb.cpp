#include "addtimetableelementgb.h"

AddTimetableElementGB::AddTimetableElementGB(QWidget *parent) :
  QGroupBox(parent)
{}

void AddTimetableElementGB::mouseDoubleClickEvent(QMouseEvent *event) {
  this->hide();
}
