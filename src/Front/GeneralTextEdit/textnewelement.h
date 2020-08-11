#ifndef TEXTNEWELEMENT_H
#define TEXTNEWELEMENT_H

#include <QTextEdit>

class TextNewElement : public QTextEdit
{
  Q_OBJECT
public:
  explicit TextNewElement(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event);

private:
  int charCounter_;
  const int MAX_COUNT_CHAR = 120;
};

#endif // TEXTNEWELEMENT_H
