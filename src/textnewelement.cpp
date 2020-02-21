#include <QDebug>

#include "textnewelement.h"
#include "notetextedit.h"

TextNewElement::TextNewElement(QWidget *parent) :
  QTextEdit(parent),
  charCounter_(0)
{}

void TextNewElement::keyPressEvent(QKeyEvent *event)
{
  QTextEdit::keyPressEvent(event);

  int tmpLength = this->toPlainText().length();
  if (tmpLength > MAX_COUNT_CHAR) {
    const int countDelete = tmpLength - MAX_COUNT_CHAR;

    QTextCursor c(this->textCursor());
    c.setPosition(MAX_COUNT_CHAR);
    c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, countDelete);
    c.deleteChar();
  }

  charCounter_ = this->toPlainText().length();
}
