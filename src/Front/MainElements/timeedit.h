#ifndef TIMEEDIT_H
#define TIMEEDIT_H

#include <QTimeEdit>

class TimeEdit : public QTimeEdit
{
public:
  TimeEdit(QWidget *parent = nullptr);
  void wheelEvent(QWheelEvent *event);
};

#endif // TIMEEDIT_H
