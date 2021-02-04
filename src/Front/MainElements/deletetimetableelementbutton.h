#ifndef DELETETIMETABLEELEMENTBUTTON_H
#define DELETETIMETABLEELEMENTBUTTON_H

#include <QPushButton>
#include <QObject>

class DeleteTimetableElementButton : public QPushButton
{
  Q_OBJECT

public:
  DeleteTimetableElementButton(QWidget *parent = nullptr);
  void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
  void deleteElement();
};

#endif // DELETETIMETABLEELEMENTBUTTON_H
