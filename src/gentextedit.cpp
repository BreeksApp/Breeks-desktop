#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <algorithm>

#include "gentextedit.h"

GenTextEdit::GenTextEdit(QWidget *parent) :
  QTextEdit(parent)
{
//add saved text
  nCurrentFile_ = 1;
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

  //all comands which insert smth
  if (charCounter_ <= MAX_COUNT_CHAR_) {
		//letters
    if (kmModifiers == 0 || kmModifiers == Qt::ShiftModifier) {
      if ( (iKey >= Qt::Key_A && iKey <= Qt::Key_Z) ||
      (QKeySequence(iKey).toString() >= "А" && (QKeySequence(iKey).toString() <= "Я")) ) {
				QTextEdit::keyPressEvent(event); //we can't identify CapsLock that's why use base method
				if (this->textCursor().selectedText() != "") {
					detailsEraseCharsOfSelectedText(cursorPos);
				}
				detailsItemCheckAndCanselStatus(cursorPos);

				fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);
        ++charCounter_;

        return;
      }
    }
    //numbers
    if (kmModifiers == 0) {
      if (iKey >= Qt::Key_0 && iKey <= Qt::Key_9) {
        if (this->textCursor().selectedText() != "") {
          detailsEraseCharsOfSelectedText(cursorPos);
        }

				detailsItemCheckAndCanselStatus(cursorPos);

        this->insertPlainText(QKeySequence(iKey).toString());
				fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);

        ++charCounter_;
        return;
      }
    }
    //special chars
		if (kmModifiers == 0 || kmModifiers == Qt::ShiftModifier) {
			for (QChar i : AVAILABLE_CHARS_){
				if (QKeySequence(iKey).toString() == i) {
					if (this->textCursor().selectedText() != "") {
						detailsEraseCharsOfSelectedText(cursorPos);
					}

					detailsItemCheckAndCanselStatus(cursorPos);

					this->insertPlainText(QKeySequence(iKey).toString());
					fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);

					++charCounter_;
					return;
				}
			}
		}

    switch (iKey) {
      //Space
			case Qt::Key_Space : {
        if (this->textCursor().selectedText() != "") {
          detailsEraseCharsOfSelectedText(cursorPos);
        }

				detailsItemCheckAndCanselStatus(cursorPos);

        this->textCursor().insertText(" ", charFormat);
				fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);

        ++charCounter_;
				return;
			}
      //Tab
      case Qt::Key_Tab : {
        if (this->textCursor().selectedText() != "") {
          detailsEraseCharsOfSelectedText(cursorPos);
        }
				//detailsItemCheckAndCanselStatus(cursorPos);

				int pos = cursorPos;
				QTextCursor c = this->textCursor();

				if (charCounter_ != 0 && fontStyleVector_[std::max(0, pos - 1)] == fontStyleValue_t::Item) {
					QTextCursor tmp = c;
					tmp.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
					int nMove = std::min(ITEM_LENGTH, c.position() - tmp.position());

					c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, nMove);
					pos = c.position();
				}

				for (int i = 0; i < TAB_LENGTH; ++i) {
					c.insertText(" ", charFormat);
					fontStyleVector_.insert(pos, 1, fontStyleValue_t::Item);
					++pos;
					++charCounter_;
				}

				if (c.position() != cursorPos) {
					c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, ITEM_LENGTH);
				}

				this->setTextCursor(c);
        break;
      }
      //Return
      case Qt::Key_Return :
        if (this->textCursor().selectedText() != "") {
          detailsEraseCharsOfSelectedText(cursorPos);
        }

        this->textCursor().insertText("\n", charFormat);
				fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);
        ++charCounter_;

        break;
    }

    if (kmModifiers == Qt::ControlModifier) {
			//Ctrl + d - dash
			if (QKeySequence(iKey) == Qt::Key_D ||QKeySequence(iKey).toString() == "В") {
				if (this->textCursor().selectedText() != "") {
					detailsEraseCharsOfSelectedText(cursorPos);
				}
				detailsItemCheckAndCanselStatus(cursorPos);

				this->insertPlainText("—");
				fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);
				++charCounter_;

				return;
			}
      //Ctrl + V - paste
			else if (QKeySequence(iKey) == Qt::Key_V) {
        QClipboard* buffer = QApplication::clipboard();

        if (this->textCursor().selectedText() != "") {
          detailsEraseCharsOfSelectedText(cursorPos);
        }

				detailsItemCheckAndCanselStatus(cursorPos);

        QString insertLine = buffer->text();

        int first = insertLine.length();
        int second = MAX_COUNT_CHAR_ - charCounter_ + 1;
        int end = std::min(first, second);
        insertLine = insertLine.mid(0, end); //to correct work with limit of chars

        this->textCursor().insertText(insertLine);
				fontStyleVector_.insert(cursorPos, insertLine.length(), fontStyleValue_t::Normal);

        charCounter_ += insertLine.length();
      }
			//Ctrl + p - add to-do-list with point
			else if (QKeySequence(iKey) == Qt::Key_P || QKeySequence(iKey).toString() == "З") {
				addTodoList(pointSign_);
      }
			//Ctrl + '-' - add to-do-list with minus
			else if (QKeySequence(iKey) == Qt::Key_Minus) {
				addTodoList(minusSign_);
			}
			else if (QKeySequence(iKey) == Qt::Key_W || QKeySequence(iKey).toString() == "Ц") {
				QTextCursor c = this->textCursor();
				c.movePosition(QTextCursor::StartOfBlock);
				int pos = std::max(0, c.position() - 1);

				QString color = "#ff3366";
				QString html = "<font color=" + color + ">*</font>";
				c.insertHtml(html);
				this->setTextColor(QColor(0, 0, 0));
				fontStyleVector_.insert(pos, 1, fontStyleValue_t::Star);
				++charCounter_;
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
		if (QKeySequence(iKey) == Qt::Key_Up) {
			QTextCursor c = this->textCursor();
			c.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
			c.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
			this->setTextCursor(c);
		}
		else if (QKeySequence(iKey) == Qt::Key_Down) {
			QTextCursor c = this->textCursor();
			c.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
			this->setTextCursor(c);
		}
		else {
			//it is tmp soluton, I want to reimplementate work with shift
			QTextEdit::keyPressEvent(event);
		}
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
      detailsEraseCharsOfSelectedText(cursorPos);
			detailsItemCheckAndCanselStatus(cursorPos);
      this->cut();
    }
		//Ctrl + b - Bold
		else if (QKeySequence(iKey) == Qt::Key_B || QKeySequence(iKey).toString() == "И") {
      setFontStyle(fontStyleValue_t::Bold);
    }
		//Ctrl + i - Italic
		else if (QKeySequence(iKey) == Qt::Key_I || QKeySequence(iKey).toString() == "Ш") {
      setFontStyle(fontStyleValue_t::Italic);
    }
		//Ctrl + u - Underline
		else if (QKeySequence(iKey) == Qt::Key_U || QKeySequence(iKey).toString() == "Г") {
      setFontStyle(fontStyleValue_t::Underline);
    }
		//Ctrl + s - Strike
		else if (QKeySequence(iKey) == Qt::Key_S || QKeySequence(iKey).toString() == "Ы") {
      setFontStyle(fontStyleValue_t::Strike);
    }
		//Ctrl + n - Normal
		else if (QKeySequence(iKey) == Qt::Key_N || QKeySequence(iKey).toString() == "Т") {
      QString selectline = this->textCursor().selectedText();
      QTextCharFormat textFormat;
      textFormat.setFontWeight(QFont::Normal);

      int first = this->textCursor().selectionStart();
      int last = this->textCursor().selectionEnd();

      for (int i = first; i < last; ++i) {
				if (fontStyleVector_[i] == fontStyleValue_t::Item) {
					continue;
				}
        this->textCursor().setPosition(i);
        fontStyleVector_[i] = fontStyleValue_t::Normal;
        this->textCursor().setCharFormat(textFormat);
      }
    }
  }

  //Backspace
  if (QKeySequence(iKey) == Qt::Key_Backspace) {
		//analize item posotion if it is item
		detailsItemCheckInDeleting(cursorPos, true, kmModifiers);
		detailsDeleteBackspaceRealization(kmModifiers, QTextCursor::PreviousWord, cursorPos, 0, 1);
		this->textCursor().deletePreviousChar();
  }
  //Delete
  else if (QKeySequence(iKey) == Qt::Key_Delete) {
		detailsItemCheckInDeleting(cursorPos, false, kmModifiers);
    detailsDeleteBackspaceRealization(kmModifiers, QTextCursor::NextWord, cursorPos, fontStyleVector_.size());
    this->textCursor().deleteChar();
  }
}

void GenTextEdit::setFontStyle(int style)
{
  QString selectline = this->textCursor().selectedText();
  QTextCharFormat textFormat;

  int first = this->textCursor().selectionStart();
  int last = this->textCursor().selectionEnd();
	QTextCursor c(this->textCursor());

  for (int i = first; i < last; ++i) {
    c.setPosition(i);
    c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
		//avoid effects for item
		if (fontStyleVector_[c.position() - 1] == fontStyleValue_t::Item) {
      continue;
		}

    if (fontStyleVector_.value(i) != fontStyleValue_t(style)) {
      fontStyleVector_[i] = fontStyleValue_t(style);
      switch (style) {
        case fontStyleValue_t::Bold:
          textFormat.setFontWeight(QFont::Bold);
          break;
        case fontStyleValue_t::Italic :
          textFormat.setFontItalic(true);
          break;
        case fontStyleValue_t::Underline :
          textFormat.setFontUnderline(true);
          break;
        case fontStyleValue_t::Strike :
          textFormat.setFontStrikeOut(true);
          break;
      }
    }
    else {
      fontStyleVector_[i] = fontStyleValue_t::Normal;
      textFormat.setFontWeight(QFont::Normal);
    }
    c.setCharFormat(textFormat);
  }
}

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
		detailsEraseCharsOfSelectedText(cursorPos);
	}
	//for checking empty line
  int n = c.selectedText().length();
  QString spaceLine = "";
  for (int i = 0; i < n; ++i) {
    spaceLine += " ";
  }
	//---

	QString item = "  " + itemSign + " "; //2 space + point + space
  if ((c.position() == cursorPos) || (c.selectedText() == spaceLine)) {
    this->textCursor().insertText(item, charFormat);
		fontStyleVector_.insert(cursorPos, 4, fontStyleValue_t::Item);
    charCounter_ += 4;
  }
  else {
    this->textCursor().insertText('\n' + item, charFormat);
		fontStyleVector_.insert(cursorPos, 4, fontStyleValue_t::Item);
		fontStyleVector_.insert(cursorPos, 1, fontStyleValue_t::Normal);

    charCounter_ += 5;
  }
}

//for file system
void GenTextEdit::recieveUsername(const QString username) //SLOT
{
	username_ = username;
}

void GenTextEdit::fillFontStyleVector(int cursorPos, int count, int style)
{
  fontStyleVector_.insert(cursorPos, count, fontStyleValue_t(style));
}
int GenTextEdit::getCharStyle(int index) const
{
  if (index < 0 || index >= charCounter_) {
    qDebug() << "Index is out of range!";
    return 0;
  }
  return fontStyleVector_[index];
}

void GenTextEdit::setCharCounter(int value)
{
  charCounter_ = value;
}
int GenTextEdit::getCharCounter() const
{
  return charCounter_;
}