#ifndef BREEK_H
#define BREEK_H

#include <QWidget>
#include <QPushButton>

class Breek : public QPushButton
{
  Q_OBJECT

public:
  explicit Breek(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event);

  bool getState();
  void setState(bool state);

  void setEmoji(const QString, const QString, const QString);
  void setIndex(const int zoneIndex, const int dayIndex);
  void updateEmoji(const QString&);

private:
  bool state_;

  int workState_;
  int zoneIndex_;
  int dayIndex_;

  QString emoji_;
  QString emojiComplited_;
  QString emojiDroped_;

signals:
  void moveBreek(int, int, bool);

public slots:
  void changeBreekState();
};

#endif // BREEK_H
