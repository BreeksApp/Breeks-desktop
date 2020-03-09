#include "notetextedit.h"
#include <QDebug>

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

void NoteTextEdit::detailsDeleteBackspaceRealization(Qt::KeyboardModifiers kmModifiers, QTextCursor::MoveOperation whereMove,
			int cursorPos, int blindSpot, int a)
{
	int spaceCounter = 0;

	int nSelectedChars = this->textCursor().selectedText().length();
	if (nSelectedChars == 0) { //no selected text
		if (cursorPos != blindSpot) {
      iterator iterFirst = fontStyleVector_.begin();

      if (kmModifiers == Qt::ControlModifier) {
        QTextCursor c = this->textCursor();
        c.movePosition(whereMove, QTextCursor::KeepAnchor);

				//for normal working Ctrl + Backspace/Delete ---
				//delting waste spaces in the left/right
				QTextCursor tmpC = c;
				while (true) {
					if (tmpC.positionInBlock() != 0 && tmpC.position() != this->toPlainText().length()) {
						QTextCursor::MoveOperation moveSide = (whereMove == QTextCursor::PreviousWord) ?
									QTextCursor::Left : QTextCursor::Right;
						tmpC.movePosition(moveSide, QTextCursor::KeepAnchor);
						if (tmpC.selectedText()[0] == ' ' || tmpC.selectedText()[tmpC.selectedText().length()-1] == ' ') {
							c = tmpC;
							++spaceCounter;
							continue;
						}
					}
					break;
				}
				//---

        iterFirst += c.selectionStart();
        iterator iterLast = iterFirst + c.selectedText().length();

				//qDebug() << c.selectedText();

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


