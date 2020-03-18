#include <QDebug>
#include <iostream>
#include <algorithm>
#include <QTextCodec>

#include "gentextedit.h"

void GenTextEdit::detailsEraseSelectedText(int &cursorPos)
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

void GenTextEdit::detailsCheckItemPosInDeleting(int &cursorPos, bool isBS, Qt::KeyboardModifiers &mod)
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

void GenTextEdit::detailsCheckItemAndCanselStatus(int cursorPos)
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

void GenTextEdit::detailsCheckSelectionAndItem(int cursorPos)
{
  if (this->textCursor().selectedText() != "") {
    detailsEraseSelectedText(cursorPos);
  }
  detailsCheckItemAndCanselStatus(cursorPos);
}


