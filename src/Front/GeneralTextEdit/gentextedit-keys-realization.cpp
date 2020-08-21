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

				//Add command in UndoRedoBuffer
					commandInfo_t command;
					setCommandInfo(command, command::deleteStr, iterFirst - charStyleVector_.begin(), c.selectedText());
					undoRedoBuffer_->pushUndoCommand(command);
				//

        this->setTextCursor(c);
        charStyleVector_.erase(iterFirst, iterLast);
        charCounter_ -= c.selectedText().length();
      }
      else {
        iterFirst += this->textCursor().position() - a;
				//Add command in UndoRedoBuffer
					commandInfo_t command;
					const int pos = iterFirst - charStyleVector_.begin();
					const QString text = this->toPlainText().at(pos);
					setCommandInfo(command, command::deleteStr, pos, text);
					undoRedoBuffer_->pushUndoCommand(command);
				//
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
		item = '\n' + item;
		this->textCursor().insertText(item, charFormat);
    charStyleVector_.insert(cursorPos, 4, ch);
		detailsSetCharStyle(ch, charStyle::Normal);
    charStyleVector_.insert(cursorPos, 1, ch);
    charCounter_ += 5;
  }
	//Add coommand to UndoRefoBuffer
	commandInfo_t command;
		setCommandInfo(command, command::insertStr, cursorPos, item);
		undoRedoBuffer_->pushUndoCommand(command);
	//
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
	QString insertStr = warrningSign_; //for Ctrl + z
	//if some stars we need only one space
	if ((charCounter_ == 0) || (charStyleVector_[std::min(pos, charCounter_ - 1)].star == false &&
				charStyleVector_[std::min(pos, charCounter_ - 1)].item == false)) {
		addSpace(c.position());
		insertStr += ' ';
	}
	detailsSetCharStyle(ch, charStyle::Star);
	charStyleVector_.insert(pos, 1, ch);

	//Add command to UndoRedoBuffer
	commandInfo_t command;
	setCommandInfo(command, command::insertStr, pos, insertStr);
	undoRedoBuffer_->pushUndoCommand(command);
	//

	charCounter_ += 1;
}

//---------TAB
void GenTextEdit::addTab(int& cursorPos)
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
		charStyleVector_.insert(pos + i, 1, ch);
		//++pos;
		++charCounter_;
	}

	if (isItem) {
		c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, ITEM_LENGTH);
	}
//Add command to UndoRedoBuffer
	commandInfo_t command;
	QString sTab = "";
	sTab.insert(TAB_LENGTH - 1, " ");
	setCommandInfo(command, command::insertStr, pos, sTab, TAB_LENGTH);
	undoRedoBuffer_->pushUndoCommand(command);
//
	this->setTextCursor(c);
}

//---------BackTab
void GenTextEdit::backTab(int &cursorPos)
{
	QTextCursor c = this->textCursor();
	c.clearSelection();
	c.movePosition(QTextCursor::StartOfBlock);
	c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, TAB_LENGTH);

	QString sTab = "";
	sTab.insert(TAB_LENGTH - 1, " ");

	if (c.selectedText() == sTab) {
		this->setTextCursor(c);
		iterator iterLast = charStyleVector_.begin() + c.position();
		iterator iterFirst = iterLast - TAB_LENGTH;
	//Add command to UndoRedoBuffer
		commandInfo_t command;
		setCommandInfo(command, command::deleteStr, c.position() - TAB_LENGTH, sTab, TAB_LENGTH);
		undoRedoBuffer_->pushUndoCommand(command);
	//
		charStyleVector_.erase(iterFirst, iterLast);
		charCounter_ -= TAB_LENGTH;
		c.deleteChar();

		c.setPosition(cursorPos - TAB_LENGTH);
		this->setTextCursor(c);
	}
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
void GenTextEdit::setCharStyle(const int style, const bool forBuffer)
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

		detailsSetCharStyle(charStyleVector_[i], style, status); //set new style

		QTextCharFormat textFormat;
    textFormat.setFontWeight(QFont::Normal);

		detailsSetFormatFields(textFormat, charStyleVector_[i]);
		if (charStyleVector_[i].sColor != "") {
			textFormat.setBackground(QColor(charStyleVector_[i].sColor));
		}
		if (charStyleVector_[i].spellChecker == false || (charStyleVector_[i].spellChecker == true && style != charStyle::Underline)) {
			c.setCharFormat(textFormat);
		}
  }
	if (!forBuffer) { //because that function is also used for change style by Ctrl + z
		//Add coommand to UndoRefoBuffer
		commandInfo_t command;
		setCommandInfo(command, command::changeStyle, first, QString::number(style), last - first);
		undoRedoBuffer_->pushUndoCommand(command);
		//
	}
}

//---------COLOR TEXT
void GenTextEdit::colorText(const QString color, const bool forBuffer)
{
	QTextCursor c = this->textCursor();

	if (c.hasSelection() && color != "") {
		const int first = c.selectionStart();
		const int last = c.selectionEnd();

		for (int i = first; i < last; ++i) {
			QTextCharFormat fmt;
			fmt.setBackground(QColor(color));
			detailsSetFormatFields(fmt, charStyleVector_[i]);

			c.setCharFormat(fmt);
			charStyleVector_[i].sColor = color;
		}

		if (!forBuffer) {
		//Add coommand to UndoRefoBuffer
			commandInfo_t command;
			setCommandInfo(command, command::changeColor, first, color, last - first);
			undoRedoBuffer_->pushUndoCommand(command);
		}
	}
}

//---------Ctrl + z
void GenTextEdit::undoCommand()
{
	if (!undoRedoBuffer_->isUndoEmpty()) {
		commandInfo_t command;
		undoRedoBuffer_->popUndoCommand(command);
		this->textCursor().clearSelection();
		QTextCursor c = this->textCursor();
		c.setPosition(command.pos);

		if (command.commandName == command::insertStr) {
			detailsUndoRedoDeleteText(command);
		}
		else if (command.commandName == command::deleteStr) {
			detailsUndoRedoInsertText(command);
		}
		else if (command.commandName == command::changeStyle) {
			detailsUndoRedoEffects(command, true);
		}
		else if (command.commandName == command::changeColor) {
			c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.charStyleVector.size());
			this->setTextCursor(c);
			makeCharNormal();
			//this->moveCursor(QTextCursor::Right);
		}

		undoRedoBuffer_->pushRedoCommand(command);
	}

	return;
}
void GenTextEdit::setCommandInfo(commandInfo_t& command, const enum command commandName,
																 const int pos, const QString text, int length)
{
	command.commandName = commandName;
	command.pos = pos;
	command.text = text;

	if (length == -1) {
		length = text.length();
	}

	for (int i = 0; i < length; ++i) {
		command.charStyleVector.push_back(charStyleVector_[pos + i]);
	}
}

//---------Ctrl + y
void GenTextEdit::redoCommand()
{
	if (!undoRedoBuffer_->isRedoEmpty()) {
		commandInfo_t command;
		undoRedoBuffer_->popRedoCommand(command);
		this->textCursor().clearSelection();
		QTextCursor c = this->textCursor();
		c.setPosition(command.pos);

		if (command.commandName == command::insertStr) {
			detailsUndoRedoInsertText(command);
		}
		else if (command.commandName == command::deleteStr) {
			detailsUndoRedoDeleteText(command);
		}
		else if (command.commandName == command::changeStyle) {
			detailsUndoRedoEffects(command);
		}
		else if (command.commandName == command::changeColor) {
			c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.charStyleVector.size());
			this->setTextCursor(c);
			const QString sColor = command.text;
			colorText(sColor);
			//this->moveCursor(QTextCursor::Right);
		}

		undoRedoBuffer_->pushUndoCommand(command);
	}

	return;
}

//---------Ctrl + n
void GenTextEdit::makeCharNormal()
{
	QTextCharFormat textFormat;
	textFormat.setFontWeight(QFont::Normal);

	int first = this->textCursor().selectionStart();
	int last = this->textCursor().selectionEnd();

	for (int i = first; i < last; ++i) {
		if (charStyleVector_[i].item == true) {
			continue;
		}
		this->textCursor().setPosition(i);
		detailsSetCharStyle(charStyleVector_[i]);
		this->textCursor().setCharFormat(textFormat);
	}
}
