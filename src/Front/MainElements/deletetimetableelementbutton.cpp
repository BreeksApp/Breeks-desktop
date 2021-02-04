#include "deletetimetableelementbutton.h"

DeleteTimetableElementButton::DeleteTimetableElementButton(QWidget *parent) :
  QPushButton(parent)
{}

void DeleteTimetableElementButton::mouseDoubleClickEvent(QMouseEvent *event) {
  emit deleteElement();
}
