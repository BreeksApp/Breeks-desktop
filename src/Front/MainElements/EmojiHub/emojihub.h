#ifndef EMOJIHUB_H
#define EMOJIHUB_H

#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollArea>
#include <QObject>

#include "emojibutton.h"

class EmojiHub : public QGroupBox
{
  Q_OBJECT

public:
  EmojiHub(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event);

public slots:
  void chosed(int);
  void showThis();

  void showThisSt();

signals :
  void changeEmoji(int);
  void changeEmojiSt(int);
  void close();
  void closeSt();
  void open();
  void openSt();

private:
  QScrollArea *scrollArea_;

  const static int N_EMOJIES = 71;
  EmojiButton *arrEmoji_[N_EMOJIES];

  bool isSaturday_;
};

#endif // EMOJIHUB_H
