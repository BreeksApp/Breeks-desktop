#include "gentextedit.h"

//---------BACKSPACE / DELETE
void GenTextEdit::deleteSmth(const Qt::KeyboardModifiers kmModifiers, const QTextCursor::MoveOperation whereMove,
																					 int& cursorPos, const int blindSpot, const int a)
{
	int nSelectedChars = this->textCursor().selectedText().length();

	if (nSelectedChars == 0) { //no selected text
		if (cursorPos != blindSpot) {
			iterator iterFirst = charStyleVector_.begin();

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

					if (c.positionInBlock() != 0 && c.position() <= charCounter_) {
						/* 1) _innnnnn or nnnnnn_i - cursor on item ('_' - cursor)
							 2) selected text != 0
							 3) a_bc or ab_c - cursor on [pos] char ('_' - space) */
						if ( (charStyleVector_[std::min(c.position() + i, charCounter_ - 1)].item == false) &&
									c.selectedText().length() > 2 &&
									( (c.selectedText()[pos] != ' ' && c.selectedText()[pos + i] == ' ') ||
									(c.selectedText()[pos] == ' ' && c.selectedText()[pos + i] != ' ') )) {
							int selectionLength = c.selectedText().length() - 1;
							c.clearSelection();
							c.setPosition(this->textCursor().position());
							c.movePosition(moveSide, QTextCursor::KeepAnchor, selectionLength);

							break;
						}
						else if (charStyleVector_[c.position() - 1].star == true || c.position() == charCounter_) {
							break;
						}
						else {
							c.movePosition(moveSide, QTextCursor::KeepAnchor);
							continue;
						}
					}
					break;
				}
				//end of while()

        iterFirst += c.selectionStart();
        iterator iterLast = iterFirst + c.selectedText().length();

        this->setTextCursor(c);
        charStyleVector_.erase(iterFirst, iterLast);
        charCounter_ -= c.selectedText().length();
      }
      else {
        iterFirst += this->textCursor().position() - a;
        charStyleVector_.erase(iterFirst);
        --charCounter_;
      }
    }
  }
  else {
    detailsEraseSelectedText(cursorPos);
  }
}

//---------ADD LIST
void GenTextEdit::addTodoList()
{
  addTodoList(pointSign_);
}
void GenTextEdit::addTodoList(const QString itemSign)
{
  int cursorPos = this->textCursor().position();
  QTextCharFormat charFormat; //to back Normal font style of text after Bold, Italic, Underline... words
  charFormat.setFontWeight(QFont::Normal);

  //if there is selected text ---
  QTextCursor c(this->textCursor());
  c.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);

	if (this->textCursor().selectedText() != "") {
		detailsEraseSelectedText(cursorPos);
	}
	//for checking empty line
	int n = c.selectedText().length();
	QString spaceLine = "";
	for (int i = 0; i < n; ++i) {
		spaceLine += " ";
	}
	//---

  QString item = "  " + itemSign + " "; //2 space + point + space
  charStyle_t ch;
	detailsSetCharStyle(ch);
  detailsSetCharStyle(ch, charStyle::Item);

  if ((c.position() == cursorPos) || (c.selectedText() == spaceLine)) {
    this->textCursor().insertText(item, charFormat);
    charStyleVector_.insert(cursorPos, 4, ch);
    charCounter_ += 4;
  }
  else {
    this->textCursor().insertText('\n' + item, charFormat);
    charStyleVector_.insert(cursorPos, 4, ch);
		detailsSetCharStyle(ch, charStyle::Normal);
    charStyleVector_.insert(cursorPos, 1, ch);
    charCounter_ += 5;
  }
}

//---------WARRNING
void GenTextEdit::addStar()
{
	charStyle_t ch;
	detailsSetCharStyle(ch);
	QTextCursor c = this->textCursor();
	c.movePosition(QTextCursor::StartOfBlock);
	int pos = c.position();

	QTextCharFormat fmt;
	fmt.setBackground(QColor(colors::marina));
	c.insertHtml(warrningSign_);
	c.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
	c.setCharFormat(fmt);
	//if some stars we need only one space
	if ((charCounter_ == 0) || (charStyleVector_[std::min(pos, charCounter_ - 1)].star == false &&
				charStyleVector_[std::min(pos, charCounter_ - 1)].item == false)) {
		addSpace(c.position());
	}
	detailsSetCharStyle(ch, charStyle::Star);
	charStyleVector_.insert(pos, 1, ch);
	charCounter_ += 1;
}

//---------TAB
void GenTextEdit::addTab(const int cursorPos)
{
	QTextCharFormat charFormat;
	charFormat.setFontWeight(QFont::Normal);
	charStyle_t ch;
	detailsSetCharStyle(ch);

	int pos = cursorPos;
	QTextCursor c = this->textCursor();
	bool isItem = false;

	if (charCounter_ != 0 && charStyleVector_[std::max(0, pos - 1)].item == true) {
		QTextCursor tmp = c;
		tmp.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
		int nMove = std::min(ITEM_LENGTH, c.position() - tmp.position());

		c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, nMove);
		pos = c.position();
		isItem = true;
	}
	detailsSetCharStyle(ch, charStyle::Item);
	for (int i = 0; i < TAB_LENGTH; ++i) {
		c.insertText(" ", charFormat);
		charStyleVector_.insert(pos, 1, ch);
		++pos;
		++charCounter_;
	}

	if (isItem) {
		c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, ITEM_LENGTH);
	}

	this->setTextCursor(c);
}

//---------SPACE
void GenTextEdit::addSpace(const int cursorPos)
{
	QTextCharFormat charFormat;
	charFormat.setFontWeight(QFont::Normal);
	charStyle_t ch;
	detailsSetCharStyle(ch);

	this->textCursor().insertText(" ", charFormat);
	charStyleVector_.insert(cursorPos, 1, ch);

	++charCounter_;
}

//---------SET STYLE FOR CHAR
void GenTextEdit::setCharStyle(const int style)
{  
  int first = this->textCursor().selectionStart();
  int last = this->textCursor().selectionEnd();
  QTextCursor c(this->textCursor());
	int status = 2;

  for (int i = first; i < last; ++i) {
    c.setPosition(i);
    c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    //avoid effects for item
		if (charStyleVector_[c.position() - 1].item == true ||
					charStyleVector_[c.position() - 1].star == true) {
      continue;
    }

		detailsSetCharStyle(charStyleVector_[i], style, status);
    QTextCharFormat textFormat;
    textFormat.setFontWeight(QFont::Normal);

    if (charStyleVector_[i].bold == true) {
      textFormat.setFontWeight(QFont::Bold);
    }
    if (charStyleVector_[i].italic == true) {
      textFormat.setFontItalic(true);
    }
    if (charStyleVector_[i].underline == true) {
      textFormat.setFontUnderline(true);
    }
    if (charStyleVector_[i].strike == true) {
      textFormat.setFontStrikeOut(true);
    }

    c.setCharFormat(textFormat);
  }
}

//---------COLOR TEXT
void GenTextEdit::colorText(const QString color)
{
	QTextCursor c = this->textCursor();

	if (c.hasSelection() && color != "") {
		QTextCharFormat fmt;
		fmt.setBackground(QColor(color));
		c.setCharFormat(fmt);

		for (int i = c.selectionStart(); i < c.selectionEnd(); ++i) {
			charStyleVector_[i].sColor = color;
		}
	}
}
