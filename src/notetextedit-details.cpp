#include "notetextedit.h"
#include <QDebug>
#include <iostream>
#include <algorithm>

void NoteTextEdit::detailsEraseCharsOfSelectedText(int& cursorPos)
{
	QTextCursor c = this->textCursor();
	int pos = std::min(c.selectionStart(), c.selectionEnd());
	int nChar = c.selectedText().length();

	c.movePosition(QTextCursor::Start);
	c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nChar);

	qDebug() << c.selectedText();

	iterator iterFirst = fontStyleVector_.begin();
	iterFirst += c.selectionStart();
  iterator iterLast = iterFirst + nChar;

	//if some parts of item is chosen we must delete full item ---
	qDebug() << *iterFirst;
	while (true) {
		if (*iterFirst == fontStyleValue_t::Item) {
			if (iterFirst != fontStyleVector_.begin()) {
				--iterFirst;
				++nChar;

				pos = c.selectionStart() - 1;
				c.clearSelection();
				c.movePosition(QTextCursor::Start);
				c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);
				c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nChar);
				//qDebug() << c.selectedText();
			}
			else {
				break;
			}
		}
		else if (*iterLast == fontStyleValue_t::Item) {
			if (iterLast != fontStyleVector_.end()) {
				++iterLast;
				c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
				++nChar;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	//---

  fontStyleVector_.erase(iterFirst, iterLast);

  charCounter_ -= nChar;
	cursorPos -= c.selectionStart();
	this->setTextCursor(c);
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
				//special situation with item
				QTextCursor tmpC = c;
				while (true) {
					if (tmpC.positionInBlock() != 0 && tmpC.position() != this->toPlainText().length()) {
						QTextCursor::MoveOperation moveSide = (whereMove == QTextCursor::PreviousWord) ?
									QTextCursor::Left : QTextCursor::Right;
						tmpC.movePosition(moveSide, QTextCursor::KeepAnchor);
						int pos = (whereMove == QTextCursor::PreviousWord) ? 0 : tmpC.selectedText().length() - 1;
						//analize current char
						if (tmpC.selectedText()[pos] == ' ' || tmpC.selectedText()[pos] == pointSign_) {
							//__•!dddddddd !(_) - should not be deleted
							if (fontStyleVector_[tmpC.selectionStart()] == fontStyleValue_t::Item &&
									fontStyleVector_[tmpC.selectionStart() + 1] != fontStyleValue_t::Item) {
								break;
							}
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
		qDebug() << "!";
    detailsEraseCharsOfSelectedText(cursorPos);
  }
}

void NoteTextEdit::detailsItemCheck(int& cursorPos, bool isBS, Qt::KeyboardModifiers& mod)
{
	QTextCursor::MoveOperation moveSide = isBS ? QTextCursor::Right : QTextCursor::Left;
	int i = isBS ? 1 : -1;
	int blindSpot = isBS ? 0 : this->toPlainText().length();

	int pos = std::max(0, cursorPos - std::max(0, i));

	if (cursorPos != blindSpot && fontStyleVector_[pos] == fontStyleValue_t::Item) {
		QTextCursor c = this->textCursor();
		QTextCursor::MoveMode selection = QTextCursor::MoveAnchor;
		if (this->textCursor().selectedText() != "") {
			selection = QTextCursor::KeepAnchor;
		}
		while (cursorPos < charCounter_ && cursorPos > 0) {
			if (fontStyleVector_[cursorPos] == fontStyleValue_t::Item) {
				cursorPos += i;
				c.movePosition(moveSide, selection);
			}
			else {
				//qDebug() << cursorPos << " " << fontStyleVector_[cursorPos];
				cursorPos += i;
				c.movePosition(moveSide, QTextCursor::MoveAnchor);
			}
		}
		this->setTextCursor(c);
		mod = Qt::ControlModifier;
	}
}


