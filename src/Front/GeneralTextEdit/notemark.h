#ifndef NOTEMARK_H
#define NOTEMARK_H

#include <QPushButton>

class NoteMark : public QPushButton
{
  Q_OBJECT
public:
  explicit NoteMark(QWidget *parent = nullptr);
  void setSelectableStyle();
  void setDefaultStyle();
};

#endif // NOTEMARK_H
