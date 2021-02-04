#ifndef DEMOBREEK_H
#define DEMOBREEK_H

#include <QPushButton>
#include <QQuickWidget>

#include "Front/datastructures.h"

class DemoBreek : public QPushButton
{
  Q_OBJECT

public:
  DemoBreek(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void focusInEvent(QFocusEvent *) override;
  void focusOutEvent(QFocusEvent *) override;

  void connectToQml(int indexOfEmoji, Conditions cond);
  void connectToQml(Conditions cond, bool = false);
  void connectToQml(int indexOfEmoji, Directions dir,
                    Conditions from, Conditions to);

  int getEmojiIndex();

public slots:
  void changeEmoji(int);

private:
  int nEmoji_;
  Conditions workState_;

  QQuickWidget *quickWidget_;
  QObject *graphObject_;

  bool isAnimated_;
  void waitAnimationEnd();

  const int width_;
  const int height_;
};

#endif // DEMOBREEK_H
