#include "deletebreekszonebutton.h"

DeleteBreeksZoneButton::DeleteBreeksZoneButton(int zoneIndex, QWidget *parent) :
	QPushButton(parent),
	zoneIndex_(zoneIndex)
{
}

void DeleteBreeksZoneButton::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit deleteZone(zoneIndex_);
}

void DeleteBreeksZoneButton::setZoneIndex(int zoneIndex)
{
	zoneIndex_ = zoneIndex;
}
