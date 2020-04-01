#ifndef DAYWIDGET_H
#define DAYWIDGET_H

#include <QWidget>
#include <QDrag>
#include <QDragEnterEvent>

class DayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit DayWidget(QWidget *parent = nullptr);

  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);

  int getDayNumber();
  void setDayNumber(const int);

private:
  int dayNumber_;

signals:
  void dropElement(const int);

public slots:
};

#endif // DAYWIDGET_H
