#include "notetextedit.h"

void NoteTextEdit::detailsEraseCharsOfSelectedText(int& cursorPos)
{
  iterator iterFirst = fontStyleVector_.begin();
  iterFirst += this->textCursor().selectionStart();
  int nChar = this->textCursor().selectedText().length();
  iterator iterLast = iterFirst + nChar;
  fontStyleVector_.erase(iterFirst, iterLast);

  charCounter_ -= nChar;
  cursorPos -= nChar; //this->textCursor().selectionStart();
}

void NoteTextEdit::detailsDeleteBackspaceRealization(Qt::KeyboardModifiers kmModifiers,QTextCursor::MoveOperation whereMove,
      int cursorPos, int blindSpot, int a)
{
  int nChar = this->textCursor().selectedText().length();
  if (nChar == 0) {
    if (cursorPos != blindSpot) {
      iterator iterFirst = fontStyleVector_.begin();

      if (kmModifiers == Qt::ControlModifier) {
        QTextCursor c = this->textCursor();
        c.movePosition(whereMove, QTextCursor::KeepAnchor);
        iterFirst += c.selectionStart();
        iterator iterLast = iterFirst + c.selectedText().length();

        this->setTextCursor(c);
        fontStyleVector_.erase(iterFirst, iterLast);
        charCounter_ -= c.selectedText().length();
      }
      else {
        iterFirst += this->textCursor().position() - a;
        fontStyleVector_.erase(iterFirst);
        --charCounter_;
      }
    }
  }
  else {
    detailsEraseCharsOfSelectedText(cursorPos);
  }
}
