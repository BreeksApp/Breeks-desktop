#ifndef ADDBUTTONHOVER_H
#define ADDBUTTONHOVER_H

#include <QPushButton>

class AddButtonHover : public QPushButton
{
  Q_OBJECT
public:
  AddButtonHover(QWidget *parent = nullptr);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  const QString styleSheetDefault = "border-image:url(:/Images/Images/addButtonDefault.png)";
  const QString styleSheetHover = "border-image:url(:/Images/Images/addButtonHover.png)";
};

#endif // ADDBUTTONHOVER_H
