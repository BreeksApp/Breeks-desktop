#include <QDebug>
#include <iostream>
#include <algorithm>
#include <QTextCodec>

#include "gentextedit.h"

void GenTextEdit::detailsEraseSelectedText(int &cursorPos)
{
	if (!this->textCursor().hasSelection()) {
		return;
	}

	QTextCursor c = this->textCursor();
	int pos = std::min(c.selectionStart(), c.selectionEnd());
	int nChar = c.selectedText().length();

	c.movePosition(QTextCursor::Start);
	c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nChar);

	iterator iterFirst = charStyleVector_.begin() + c.selectionStart();
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
//Add command in UndoRedoBuffer
	commandInfo_t command;
	setCommandInfo(command, command::deleteStr, iterFirst - charStyleVector_.begin(), c.selectedText());
	undoRedoBuffer->pushUndoCommand(command);
//

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
		ch.sColor = colors::nocolor;
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
		ch.sColor = colors::nocolor;
  }
  else if (style == charStyle::Star) {
		ch.item = false;
    ch.star = true;
		ch.sColor = colors::marina;
  }
}

void GenTextEdit::detailsSetCharStyle(charStyle_t &ch, const int style, int& status)
{
	if (style == charStyle::Normal) {
		ch.bold = false;
		ch.italic = false;
		ch.underline = false;
		ch.strike = false;
		ch.item = false;
		ch.star = false;
		ch.sColor = colors::nocolor;
	}
	else if (style == charStyle::Bold) {
		detailsSetBoolByStatus(ch.bold, status);
	}
	else if (style == charStyle::Italic) {
		detailsSetBoolByStatus(ch.italic, status);
	}
	else if (style == charStyle::Underline) {
		detailsSetBoolByStatus(ch.underline, status);
	}
	else if (style == charStyle::Strike) {
		detailsSetBoolByStatus(ch.strike, status);
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
void GenTextEdit::detailsSetBoolByStatus(bool &a, int &status)
{
	if (status == 2) {
		a = !a;
		status = a == true ? 1 : 0;
	}
	else {
		a = status == 1 ? true : false;
    }
}

void GenTextEdit::fillCharsAndSetText(QString text, const QJsonArray jArr)
{
    this->clearCharStyleVector();
    this->setCharCounter(jArr.size());

    QTextStream out(&text);
  \
    QChar tmpChar;
    charStyle_t ch;
   //qDebug() << text;

    for (int i = 0; i < this->getCharCounter(); ++i) {
      detailsSetCharStyle(ch);
      QTextCharFormat charFormat;
      charFormat.setFontWeight(QFont::Normal);

      QJsonObject jChar = jArr[i].toObject();

      bool boldStatus = jChar.value("bold").toBool();
      bool italicStatus = jChar.value("italic").toBool();
      bool underlineStatus = jChar.value("underline").toBool();
      bool strikeStatus = jChar.value("strike").toBool();
      bool itemStatus = jChar.value("item").toBool();
      bool starStatus = jChar.value("star").toBool();
      QString color = jChar.value("sColor").toString();

      if (boldStatus == true) {
          detailsSetCharStyle(ch, charStyle::Bold);
          charFormat.setFontWeight(QFont::Bold);
      }
      if (italicStatus == true) {
          detailsSetCharStyle(ch, charStyle::Italic);
          charFormat.setFontItalic(true);
      }
      if (underlineStatus == true) {
          detailsSetCharStyle(ch, charStyle::Underline);
          charFormat.setFontUnderline(true);
      }
      if (strikeStatus == true) {
          detailsSetCharStyle(ch, charStyle::Strike);
          charFormat.setFontStrikeOut(true);
      }
        if (itemStatus == true) {
          detailsSetCharStyle(ch, charStyle::Item);
          charFormat.setFontWeight(QFont::Normal);
      }
        if (starStatus == true) {
          detailsSetCharStyle(ch, charStyle::Star);
          charFormat.setFontWeight(QFont::Normal);
      }
      ch.sColor = color;

      int cursorPos = this->textCursor().position();
      this->fillCharStyleVector(cursorPos, 1, ch);
      out >> tmpChar;
      this->textCursor().insertText(static_cast<QString>(tmpChar), charFormat);
      }

}

void GenTextEdit::detailsSetFormatFields(QTextCharFormat &fmt, const charStyle_t ch)
{
	if (ch.bold == true) {
		fmt.setFontWeight(QFont::Bold);
	}
	if (ch.italic == true) {
		fmt.setFontItalic(true);
	}
	if (ch.underline == true) {
		fmt.setFontUnderline(true);
	}
	if (ch.strike == true) {
		fmt.setFontStrikeOut(true);
	}
}

void GenTextEdit::detailsSetCharStyleByNeighbours(charStyle_t &ch, int indexRight)
{
	if (charCounter_ == 0) {
		ch = globCh;
		return;
	}

	int *indexLeft = &indexRight;
	//index of right neighbour (cursorPos)
	if (indexRight >= charCounter_) {
		indexRight = std::max(0, charCounter_ - 1);
	}
	else if (indexRight < 0) {
		indexRight = 0;
	}
	else {
		*indexLeft = std::max(0, indexRight - 1);
	}
	
	ch.bold = charStyleVector_[*indexLeft].bold | charStyleVector_[indexRight].bold | globCh.bold;
	ch.italic = charStyleVector_[*indexLeft].italic | charStyleVector_[indexRight].italic | globCh.italic;
	ch.underline = charStyleVector_[*indexLeft].underline | charStyleVector_[indexRight].underline | globCh.underline;
	ch.strike = charStyleVector_[*indexLeft].strike | charStyleVector_[indexRight].strike | globCh.strike;

	ch.sColor = charStyleVector_[indexRight].sColor == "" ?
				charStyleVector_[*indexLeft].sColor : charStyleVector_[indexRight].sColor;
}

void GenTextEdit::detailsSetCharStyleByIndex(const charStyle_t &ch, const int index)
{
	QTextCursor c = this->textCursor();
	c.setPosition(index);
	c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);

	QTextCharFormat fmt;
	detailsSetFormatFields(fmt, ch);
	if (ch.sColor != "") {
		fmt.setBackground(QColor(ch.sColor));
	}

	c.setCharFormat(fmt);
}

void GenTextEdit::detailsColorText(QTextCursor c, const QString color)
{
	if (c.hasSelection() && color != "") {
		QTextCharFormat fmt;
		fmt.setBackground(QColor(color));
		c.setCharFormat(fmt);
	}
}

void GenTextEdit::detailsUndoRedoInsertText(const commandInfo_t &command)
{
	QTextCursor c = this->textCursor();
	c.setPosition(command.pos);
	c.insertText(command.text);

	for (int i = 0; i < command.charStyleVector.size(); ++i) {
		c.setPosition(command.pos + i);
		c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
		charStyleVector_.insert(command.pos + i, command.charStyleVector[i]);
		//set effects
		QTextCharFormat fmt;
		fmt.setFontWeight(QFont::Normal);
		detailsSetFormatFields(fmt, charStyleVector_[command.pos + i]);
		if (charStyleVector_[i].sColor != "") {
			fmt.setBackground(QColor(charStyleVector_[command.pos + i].sColor));
		}
		c.setCharFormat(fmt);
		c.clearSelection();

		++charCounter_;
	}
}

void GenTextEdit::detailsUndoRedoDeleteText(const commandInfo_t &command)
{
	QTextCursor c = this->textCursor();
	c.setPosition(command.pos);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.text.length());
	c.deleteChar();

	iterator itBegin = charStyleVector_.begin();
	itBegin += command.pos;
	iterator itEnd = itBegin + command.text.length();
	charStyleVector_.erase(itBegin, itEnd);

	charCounter_ -= command.text.length();
}

void GenTextEdit::detailsUndoRedoEffects(const commandInfo_t &command, const bool flag)
{
	QTextCursor c = this->textCursor();
	c.setPosition(command.pos);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.charStyleVector.size());
	this->setTextCursor(c);

	const int style = command.text.toInt();
	setCharStyle(style, flag);

	this->moveCursor(QTextCursor::Right);
}
