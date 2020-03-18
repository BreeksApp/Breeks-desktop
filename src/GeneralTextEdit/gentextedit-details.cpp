#include <QDebug>
#include <iostream>
#include <algorithm>
#include <QTextCodec>

#include "gentextedit.h"

void GenTextEdit::detailsEraseCharsOfSelectedText(int& cursorPos)
{
	QTextCursor c = this->textCursor();
	int pos = std::min(c.selectionStart(), c.selectionEnd());
	int nChar = c.selectedText().length();

	c.movePosition(QTextCursor::Start);
	c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nChar);

	iterator iterFirst = fontStyleVector_.begin();
	iterFirst += c.selectionStart();
  iterator iterLast = iterFirst + nChar;

	//if some parts of item is chosen we must delete full item ---
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
	cursorPos = pos;
	this->setTextCursor(c);
}

void GenTextEdit::detailsDeleteBackspaceRealization(Qt::KeyboardModifiers kmModifiers,
			QTextCursor::MoveOperation whereMove, int cursorPos, int blindSpot, int a)
{
	int nSelectedChars = this->textCursor().selectedText().length();

	if (nSelectedChars == 0) { //no selected text
		if (cursorPos != blindSpot) {
      iterator iterFirst = fontStyleVector_.begin();

      if (kmModifiers == Qt::ControlModifier) {
				QTextCursor c = this->textCursor();

				//for normal working Ctrl + Backspace/Delete ---
				//special situation with item for Backspace and Delete
				QTextCursor::MoveOperation moveSide = (whereMove == QTextCursor::PreviousWord) ?
							QTextCursor::Left : QTextCursor::Right;
				c.movePosition(moveSide, QTextCursor::KeepAnchor);
				int i = (whereMove == QTextCursor::PreviousWord) ? 1 : -1;

				while (true) {
					int pos = (whereMove == QTextCursor::PreviousWord) ? 0 : c.selectedText().length() - 1;

					if (c.positionInBlock() != 0 && c.position() != charCounter_) {
						int posInVectorEnd = std::min(c.position() + i, charCounter_ - 1);
						/* 1) _innnnnn or nnnnnn_i - cursor on item ('_' - cursor)
							 2) selected text != 0
							 3) a_ or _a - cursor on first char ('_' - space) */
						if ( (fontStyleVector_[c.position()] != fontStyleValue_t::Item ||
									fontStyleVector_[posInVectorEnd] != fontStyleValue_t::Item) &&
									c.selectedText().length() != 1 &&
									( (c.selectedText()[pos] != ' ' && c.selectedText()[pos + i] == ' ') ||
									(c.selectedText()[pos] == ' ' && c.selectedText()[pos + i] != ' ') )) {
							int selectionLength = c.selectedText().length() - 1;
							c.clearSelection();
							c.setPosition(this->textCursor().position());
							c.movePosition(moveSide, QTextCursor::KeepAnchor, selectionLength);

							break;
						}
						if (fontStyleVector_[c.position() - 1] != fontStyleValue_t::Star) {
							c.movePosition(moveSide, QTextCursor::KeepAnchor);
							continue;
						}
						else {
							break;
						}
					}
					break;
				}
				//end of while()

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

void GenTextEdit::detailsItemCheckInDeleting(int &cursorPos, bool isBS, Qt::KeyboardModifiers &mod)
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
				break;
			}
		}
		this->setTextCursor(c);
		mod = Qt::ControlModifier;
	}
}

void GenTextEdit::detailsItemCheckAndCanselStatus(int cursorPos)
{
	if (cursorPos < charCounter_ && fontStyleVector_[cursorPos] == fontStyleValue_t::Item) {
		int i = std::max(0, cursorPos - 1);
		while (i >= 0 && fontStyleVector_[i] == fontStyleValue_t::Item) {
			fontStyleVector_[i] = fontStyleValue_t::Normal;
			--i;
		}
		i = cursorPos == 0 ? cursorPos + 1 : cursorPos;
		while (i < charCounter_ && fontStyleVector_[i] == fontStyleValue_t::Item) {
			fontStyleVector_[i] = fontStyleValue_t::Normal;
			++i;
		}
	}
}


