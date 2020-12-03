//VIEW

#ifndef BREEK_H
#define BREEK_H

#include <QPushButton>

#include <QObject>
#include <QQuickWidget>

#include "Front/datastructures.h"

class Breek : public QPushButton
{
  Q_OBJECT

public:
  explicit Breek(QWidget *parent = nullptr);
  Breek(int width, int height, QWidget *parent = nullptr);
  ~Breek();

	void keyPressEvent(QKeyEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void focusInEvent(QFocusEvent *) override;
	void focusOutEvent(QFocusEvent *) override;

  bool getState();
  void setState(bool state);

	Conditions getColorState();
	void setColorState(Conditions cond);

	void connectToQml(int indexOfEmoji, Conditions cond);
	void connectToQml(Conditions cond, bool = false);
  void connectToQml(int indexOfEmoji, Directions dir,
                    Conditions from, Conditions to);

  void setEmoj(int);
  int getEmojiNum();
  void setIndex(const int zoneIndex, const int dayIndex);

  int getWidth();
  int getHeight();

private:
  bool state_;

	bool isAnimated_;
	void waitAnimationEnd();

  Conditions workState_;
  int zoneIndex_;
  int dayIndex_;
  int width_;
  int height_;
  int nEmoj_;

  QQuickWidget *quickWidget_;
  QObject *graphObject_;

	bool callHub_;

signals:
  void moveBreek(int, int, bool);
	void sendSateToLilDay(int, int, int);
	void isHere(int, int, bool);
	void doubleClicked();
	void setZoneFocus(int, bool);
	void changeState(int, int);

public slots:
	void setZoneIndex(int);
  void changeBreekState();
	void changeEmoji(int);
	void closeEmojiHub();
	void openEmojiHub();
};

#endif // BREEK_H
