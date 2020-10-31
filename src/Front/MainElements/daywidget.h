//VIEW

#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDrag>
#include <QDragEnterEvent>
#include "Front/datastructures.h"

class DayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DayWidget(QWidget *parent = nullptr);

  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);

  int getDayNumber();
  void setDayNumber(const int);

private:
  int dayNumber_;
  int dayIndex_;
  int elemIndex_;
  QPoint dragPos_;

signals:
  void dropElement(const int, const int, const int, const elementData_t);
  void sendDayAndElementIndex(const int, const int);
  void sendElementsHeight(const int, const int);
	void moveElement();
	void dropNoChanges();

public slots:
};

#endif // DAYWIDGET_H
