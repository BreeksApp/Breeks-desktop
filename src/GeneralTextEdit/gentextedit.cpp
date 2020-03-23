#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <algorithm>

#include "gentextedit.h"

GenTextEdit::GenTextEdit(QWidget *parent) :
	QTextEdit(parent)
{
	undoRedoBuffer = new UndoRedoText;

	this->setTextColor(QColor(0, 0, 0));
  nCurrentFile_ = 1;
  charCounter_ = 0;
	//add saved text
	readFromDB(nCurrentFile_);
}

//We want to create our Text editor with special functions and hot-keys
//that is why we override keyPressEvent()
void GenTextEdit::keyPressEvent(QKeyEvent *event)
{
  int iKey = event->key();
  Qt::KeyboardModifiers kmModifiers = event->modifiers();
  int cursorPos = this->textCursor().position();

  QTextCharFormat charFormat; //to back Normal font style of text after Bold, Italic, Underline... words
  charFormat.setFontWeight(QFont::Normal);

  charStyle_t ch;
  detailsSetCharStyle(ch);

	commandInfo_t command;

  //all comands which insert smth
  if (charCounter_ <= MAX_COUNT_CHAR_) {
		//letters
    if (kmModifiers == 0 || kmModifiers == Qt::ShiftModifier) {
      if ( (iKey >= Qt::Key_A && iKey <= Qt::Key_Z) ||
      (QKeySequence(iKey).toString() >= "А" && (QKeySequence(iKey).toString() <= "Я")) ) {
        detailsCheckSelectionAndItem(cursorPos);

				detailsSetCharStyleByNeighbours(ch, cursorPos);
				charStyleVector_.insert(cursorPos, 1, ch);

				QTextEdit::keyPressEvent(event); //we can't identify CapsLock that's why use base method

        ++charCounter_;
			//Add coommand to UndoRefoBuffer
				const QString text = (kmModifiers != 0 ?
							QKeySequence(iKey).toString() : QKeySequence(iKey).toString().toLower());
				setCommandInfo(command, command::insertStr, cursorPos, text);
				undoRedoBuffer->pushUndoCommand(command);
			//
        return;
      }
    }
    //numbers
    if (kmModifiers == 0) {
      if (iKey >= Qt::Key_0 && iKey <= Qt::Key_9) {
        detailsCheckSelectionAndItem(cursorPos);
        this->insertPlainText(QKeySequence(iKey).toString());
				detailsSetCharStyleByNeighbours(ch, cursorPos);
        charStyleVector_.insert(cursorPos, 1, ch);

        ++charCounter_;
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, QKeySequence(iKey).toString());
				undoRedoBuffer->pushUndoCommand(command);
			//
        return;
      }
    }
    //special chars
		if (kmModifiers == 0 || kmModifiers == Qt::ShiftModifier) {
			for (QChar i : AVAILABLE_CHARS_){
				if (QKeySequence(iKey).toString() == i) {
					detailsCheckSelectionAndItem(cursorPos);
					this->insertPlainText(QKeySequence(iKey).toString());
					detailsSetCharStyleByNeighbours(ch, cursorPos);
					charStyleVector_.insert(cursorPos, 1, ch);

					++charCounter_;
				//Add coommand to UndoRefoBuffer
					setCommandInfo(command, command::insertStr, cursorPos, QKeySequence(iKey).toString());
					undoRedoBuffer->pushUndoCommand(command);
				//
					return;
				}
			}
		}

    switch (iKey) {
		 //Space
			case Qt::Key_Space : {
				detailsCheckSelectionAndItem(cursorPos);
				addSpace(cursorPos);
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, " ");
				undoRedoBuffer->pushUndoCommand(command);
			//
				return;
			}
		 //Tab
			case Qt::Key_Tab : {
				if (this->textCursor().selectedText() != "") {
					detailsEraseSelectedText(cursorPos);
        }
				addTab(cursorPos);

				return;
      }
      //Return
      case Qt::Key_Return :
        detailsCheckSelectionAndItem(cursorPos);
        this->textCursor().insertText("\n", charFormat);
        charStyleVector_.insert(cursorPos, 1, ch);
				++charCounter_;
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, "\n");
				undoRedoBuffer->pushUndoCommand(command);
			//
				return;
    }

    if (kmModifiers == Qt::ControlModifier) {
			if (QKeySequence(iKey) == Qt::Key_Z) {
				if (!undoRedoBuffer->isUndoEmpty()) {
					commandInfo_t command;
					undoRedoBuffer->popUndoCommand(command);
					this->textCursor().clearSelection();

					if (command.commandName == command::insertStr) {
						QTextCursor c = this->textCursor();
						c.setPosition(command.pos);
						c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.pos + command.text.length());
						c.deleteChar();
						iterator itBegin = charStyleVector_.begin();
						itBegin += command.pos;
						iterator itEnd = itBegin + command.text.length();
						charStyleVector_.erase(itBegin, itEnd);
						charCounter_ -= command.text.length();
					}
					if (command.commandName == command::deleteStr) {
						QTextCursor c = this->textCursor();
						c.setPosition(command.pos);
						c.insertText(command.text);
						for (int i = 0; i < command.charStyleVector.size(); ++i) {
							charStyleVector_.insert(command.pos + i, command.charStyleVector[i]);
							++charCounter_;
						}
					}

					QTextCursor c = this->textCursor();
					c.setPosition(command.pos);
					c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, command.charStyleVector.size());
					this->setTextCursor(c);

					if (command.commandName == command::changeStyle) {
						const int style = command.text.toInt();
						setCharStyle(style, true);
					}
					if (command.commandName == command::changeColor) {
						makeCharNormal();
					}
				}
				return;
			}
			//Ctrl + d - dash
			else if (QKeySequence(iKey) == Qt::Key_D ||QKeySequence(iKey).toString() == "В") {
				detailsCheckSelectionAndItem(cursorPos);
				this->insertPlainText(dashSign_);
				charStyleVector_.insert(cursorPos, 1, ch);
				++charCounter_;
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, dashSign_);
				undoRedoBuffer->pushUndoCommand(command);
			//
				return;
			}
      //Ctrl + V - paste
			else if (QKeySequence(iKey) == Qt::Key_V) {
				detailsCheckSelectionAndItem(cursorPos);

        QClipboard* buffer = QApplication::clipboard();
        QString insertLine = buffer->text();

        int first = insertLine.length();
        int second = MAX_COUNT_CHAR_ - charCounter_ + 1;
        int end = std::min(first, second);
        insertLine = insertLine.mid(0, end); //to correct work with limit of chars

        this->textCursor().insertText(insertLine);
        charStyleVector_.insert(cursorPos, insertLine.length(), ch);

        charCounter_ += insertLine.length();

			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, insertLine);
				undoRedoBuffer->pushUndoCommand(command);
			//

        return;
			}
			//Ctrl + p - add to-do-list with point
			else if (QKeySequence(iKey) == Qt::Key_P || QKeySequence(iKey).toString() == "З") {
				addTodoList(pointSign_);
				return;
      }
			//Ctrl + '-' - add to-do-list with minus
			else if (QKeySequence(iKey) == Qt::Key_Minus) {
				addTodoList(minusSign_);
				return;
			}
			//Ctrl + w - add red star
			else if (QKeySequence(iKey) == Qt::Key_W || QKeySequence(iKey).toString() == "Ц") {
				addStar();
				return;
			}
    }
	}

  //Esc canceled all selection
  if (iKey == Qt::Key_Escape) {
		this->moveCursor(QTextCursor::Right);
    return;
  }

  //Arrows Left, Up, Right, Down - move to chars and lines
  if (kmModifiers == 0) {
    switch (iKey) {
      case Qt::Key_Left :
        this->moveCursor(QTextCursor::Left);
        return;
      case Qt::Key_Right :
        this->moveCursor(QTextCursor::Right);
        return;
      case Qt::Key_Up :
        this->moveCursor(QTextCursor::Up);
        return;
      case Qt::Key_Down :
        this->moveCursor(QTextCursor::Down);
        return;
    }
  }
  //Shift + arrows
  if (kmModifiers == Qt::ShiftModifier) {
		//it is tmp soluton, I want to reimplementate work with shift
		QTextEdit::keyPressEvent(event);
		return;
  }

  //Ctrl + arrows
  if (kmModifiers == Qt::ControlModifier) {
    //Ctrl + arrows Up/Down move cursor to start/end of text
    if (QKeySequence(iKey) == Qt::Key_Up) {
      this->moveCursor(QTextCursor::Start);
      return;
    }
    else if (QKeySequence(iKey) == Qt::Key_Down) {
      this->moveCursor(QTextCursor::End);
      return;
    }
    //Ctrl + arrows <-/-> - move to words
    else if (QKeySequence(iKey) == Qt::Key_Left) {
      this->moveCursor(QTextCursor::PreviousWord);
      return;
    }
    else if (QKeySequence(iKey) == Qt::Key_Right) {
      this->moveCursor(QTextCursor::NextWord);
      return;
    }
  }

  if (kmModifiers == Qt::ControlModifier) {
    QClipboard* buffer = QApplication::clipboard();
    //Ctrl + C - copy
    if (QKeySequence(iKey) == Qt::Key_C) {
      QString Selectline = this->textCursor().selectedText();
      buffer->setText(Selectline);

      return;
    }
    //Ctrl + A - select all
    else if (QKeySequence(iKey) == Qt::Key_A) {
      this->selectAll();
      return;
    }
		//Ctrl + X - cut
		else if (QKeySequence(iKey) == Qt::Key_X) {
			detailsCheckSelectionAndItem(cursorPos); //work with UndoRedoBuffer in that function
			this->cut();
		}
		//Ctrl + b - Bold
		else if (QKeySequence(iKey) == Qt::Key_B || QKeySequence(iKey).toString() == "И") {
			setCharStyle(charStyle::Bold);
		}
		//Ctrl + i - Italic
		else if (QKeySequence(iKey) == Qt::Key_I || QKeySequence(iKey).toString() == "Ш") {
			setCharStyle(charStyle::Italic);
		}
		//Ctrl + u - Underline
		else if (QKeySequence(iKey) == Qt::Key_U || QKeySequence(iKey).toString() == "Г") {
			setCharStyle(charStyle::Underline);
		}
		//Ctrl + s - Strike
		else if (QKeySequence(iKey) == Qt::Key_S || QKeySequence(iKey).toString() == "Ы") {
			setCharStyle(charStyle::Strike);
		}
		//Ctrl + n - Normal
		else if (QKeySequence(iKey) == Qt::Key_N || QKeySequence(iKey).toString() == "Т") {
			makeCharNormal();
		}
		//Ctrl + g - highlight in green
		else if (QKeySequence(iKey) == Qt::Key_G || QKeySequence(iKey).toString() == "П") {
			colorText(colors::green);
			return;
		}
		//Ctrl + l - lavender
		else if (QKeySequence(iKey) == Qt::Key_L || QKeySequence(iKey).toString() == "Д") {
			colorText(colors::lavender);
			return;
		}
		//Ctrl + m - marina
		else if (QKeySequence(iKey) == Qt::Key_M || QKeySequence(iKey).toString() == "Ь") {
			colorText(colors::marina);
			return;
		}
		//Ctrl + o - orange
		else if (QKeySequence(iKey) == Qt::Key_O || QKeySequence(iKey).toString() == "Щ") {
			colorText(colors::orange);
			return;
		}
		//Ctrl + r - red
		else if (QKeySequence(iKey) == Qt::Key_R || QKeySequence(iKey).toString() == "К") {
			colorText(colors::red);
			return;
		}
  }

  //Backspace
  if (QKeySequence(iKey) == Qt::Key_Backspace) {
		//analize item posotion if it is item
		detailsCheckItemPosInDeleting(cursorPos, true, kmModifiers);
		deleteSmth(kmModifiers, QTextCursor::PreviousWord, cursorPos, 0, 1);
		this->textCursor().deletePreviousChar();
  }
  //Delete
  else if (QKeySequence(iKey) == Qt::Key_Delete) {
    detailsCheckItemPosInDeleting(cursorPos, false, kmModifiers);
		deleteSmth(kmModifiers, QTextCursor::NextWord, cursorPos, charStyleVector_.size());
    this->textCursor().deleteChar();
  }
}
