//VIEW

#ifndef BREEK_H
#define BREEK_H

#include <QPushButton>

#include <QObject>
#include <QQuickWidget>

class Breek : public QPushButton
{
  Q_OBJECT

public:
  enum Directions
  {
    DOWNSIDE,
    UPSIDE
  };
  enum Conditions
  {
    RED,
    GREY_FOREGROUND,
    GREY_BACKGROUND,
		GREEN,
		BLUE
  };

  explicit Breek(QWidget *parent = nullptr);
  Breek(int width, int height, QWidget *parent = nullptr);
  ~Breek();

  void keyPressEvent(QKeyEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

  bool getState();
  void setState(bool state);

	void connectToQml(int indexOfEmoji, Conditions cond);
	void connectToQml(Conditions cond);
  void connectToQml(int indexOfEmoji, Directions dir,
                    Conditions from, Conditions to);

  void setEmoj(int);
  int getEmojiNum();
  void setIndex(const int zoneIndex, const int dayIndex);

  int getWidth();
  int getHeight();

private:
  bool state_;

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

public slots:
  void changeBreekState();
	void changeEmoji(int);
	void closeEmojiHub();
	void openEmojiHub();
};

#endif // BREEK_H
