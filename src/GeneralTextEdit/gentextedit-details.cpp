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

	iterator iterFirst = charStyleVector_.begin();
	iterFirst += c.selectionStart();
  iterator iterLast = iterFirst + nChar;

	//if some parts of item is chosen we must delete full item ---
	while (true) {
		if (iterFirst->item == true && iterFirst != charStyleVector_.begin() &&
					(iterFirst - 1)->item == true) {
			--iterFirst;
			++nChar;

			pos = c.selectionStart() - 1;
			c.clearSelection();
			c.movePosition(QTextCursor::Start);
			c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);
			c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nChar);
		}
		else if (iterLast->item == true && iterLast != charStyleVector_.end()
					&& (iterLast + 1)->item == true) {
			++iterLast;
			c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
			++nChar;
		}
		else {
			break;
		}
	}
	//---
	charStyleVector_.erase(iterFirst, iterLast);

  charCounter_ -= nChar;
	cursorPos = pos;
	this->setTextCursor(c);
}

void GenTextEdit::detailsCheckItemPosInDeleting(int &cursorPos, const bool isBS, Qt::KeyboardModifiers &mod)
{
	QTextCursor::MoveOperation moveSide = isBS ? QTextCursor::Right : QTextCursor::Left;
	int i = isBS ? 1 : -1;
	int blindSpot = isBS ? 0 : this->toPlainText().length();

	int pos = std::max(0, cursorPos - std::max(0, i));

	if (cursorPos != blindSpot && charStyleVector_[pos].item == true) {
		QTextCursor c = this->textCursor();
		QTextCursor::MoveMode selection = QTextCursor::MoveAnchor;
		if (this->textCursor().selectedText() != "") {
			selection = QTextCursor::KeepAnchor;
		}
		while (cursorPos < charCounter_ && cursorPos > 0) {
			if (charStyleVector_[cursorPos].item == true) {
				cursorPos += i;
				c.movePosition(moveSide, selection);
			}
			else {
				break;
			}
		}
	//special situation for Delete when it keep star
		if (moveSide == QTextCursor::Left &&
					charStyleVector_[std::min(cursorPos, charCounter_ - 1)].star == true) {
			if (c.selectedText().length() != 0) {
				int nMove = c.selectedText().length() - 1;
				int selPos = std::max(c.selectionStart(), c.selectionEnd());
				c.clearSelection();
				c.setPosition(selPos);
				c.movePosition(moveSide, selection, nMove);
			}
			else {
				c.movePosition(QTextCursor::Right, selection);
			}
		}
	//---

		this->setTextCursor(c);
		cursorPos = this->textCursor().position();
		mod = Qt::ControlModifier;
	}
}

void GenTextEdit::detailsCheckItemAndCanselStatus(int& cursorPos)
{
	if (cursorPos < charCounter_ && charStyleVector_[cursorPos].item == true) {
		int i = std::max(0, cursorPos - 1);
		while (i >= 0 && charStyleVector_[i].item == true) {
			detailsSetCharStyle(charStyleVector_[i]);
			--i;
		}
		i = cursorPos == 0 ? cursorPos + 1 : cursorPos;
		while (i < charCounter_ && charStyleVector_[i].item == true) {
			detailsSetCharStyle(charStyleVector_[i]);
			++i;
		}
	}
}

void GenTextEdit::detailsCheckSelectionAndItem(int& cursorPos)
{
  if (this->textCursor().selectedText() != "") {
    detailsEraseSelectedText(cursorPos);
  }
  detailsCheckItemAndCanselStatus(cursorPos);
}

void GenTextEdit::detailsSetCharStyle(charStyle_t &ch, const int style)
{
  if (style == charStyle::Normal) {
    ch.bold = false;
    ch.italic = false;
    ch.underline = false;
    ch.strike = false;
    ch.item = false;
    ch.star = false;
  }
  else if (style == charStyle::Bold) {
    ch.bold = !ch.bold;
  }
  else if (style == charStyle::Italic) {
    ch.italic = !ch.italic;
  }
  else if (style == charStyle::Underline) {
    ch.underline = !ch.underline;
  }
  else if (style == charStyle::Strike) {
    ch.strike = !ch.strike;
  }
  else if (style == charStyle::Item) {
    ch.item = true;
		ch.star = false;
  }
  else if (style == charStyle::Star) {
		ch.item = false;
    ch.star = true;
  }
}

