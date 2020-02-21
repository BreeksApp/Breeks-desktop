#include "imagehover.h"

ImageHover::ImageHover(QWidget *parent):
  QPushButton(parent)
{}

void ImageHover::enterEvent(QEvent *event)
{
  emit imageEnter(true);
  QPushButton::enterEvent(event);
}

void ImageHover::leaveEvent(QEvent *event)
{
  emit imageLeave(false);
  QPushButton::leaveEvent(event);
}
