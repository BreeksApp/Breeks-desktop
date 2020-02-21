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
  const QString styleSheetDefault = "border-image:url(:/images/images/addButtonDefault.png)";
  const QString styleSheetHover = "border-image:url(:/images/images/addButtonHover.png)";
};

#endif // ADDBUTTONHOVER_H
