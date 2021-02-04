#include "descriptionzonedaybutton.h"

#include <QMouseEvent>

DescriptionZoneDayButton::DescriptionZoneDayButton(int zoneIndex, int dayIndex) :
  QPushButton(),
  zoneIndex_(zoneIndex),
  dayIndex_(dayIndex)
{}

void DescriptionZoneDayButton::mousePressEvent(QMouseEvent *event) {
  if (event == nullptr) {
    emit singleClick();
    return;
  }

  if (event->button() == Qt::LeftButton) {
    emit singleClick();
    emit singleClick(zoneIndex_);
  }

  if (event->button() == Qt::RightButton) {
    emit doubleClick(zoneIndex_, dayIndex_);
  }
}

int DescriptionZoneDayButton::getZoneIndex() {
  return zoneIndex_;
}

void DescriptionZoneDayButton::setZoneIndex(int zoneIndex) {
  zoneIndex_ = zoneIndex;
  emit changeZoneIndex(zoneIndex_);
}

void DescriptionZoneDayButton::sendPutRequestBl() {
  emit singleClick(zoneIndex_);
}
