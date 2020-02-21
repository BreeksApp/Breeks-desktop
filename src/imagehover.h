#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>

class ImageHover : public QPushButton
{
  Q_OBJECT

public:
  ImageHover(QWidget *parent = nullptr);

  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);

private:
  QGraphicsDropShadowEffect *m_shadowEffect;

signals:
  void imageEnter(bool);
  void imageLeave(bool);
};

#endif // BUTTON_H
