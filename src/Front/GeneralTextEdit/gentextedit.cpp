#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <algorithm>
#include <QPainter>
#include <QScrollBar>

#include "gentextedit.h"

RussianDictionary *GenTextEdit::rusDic_ = new RussianDictionary();

GenTextEdit::GenTextEdit(QWidget *parent) :
	QTextEdit(parent),
	timer_(new QTimer()),
	requestTimer_(new QTimer())
{
	undoRedoBuffer_ = new UndoRedoText;
	//rusDic_ = new RussianDictionary;
	timer_->setSingleShot(true);
	connect(timer_, SIGNAL(timeout()), this, SLOT(checkSpelling()));

	requestTimer_->setSingleShot(true);
	connect(requestTimer_, SIGNAL(timeout()), SLOT(sendServerRequest()));

	this->setTextColor(QColor(0, 0, 0));
  nCurrentFile_ = 1;
  charCounter_ = 0;
	detailsSetCharStyle(globCh);

	this->verticalScrollBar()->setStyleSheet(
				"QScrollBar:vertical {"
					"background-color: #FFFFF0;"
					"width: 9px;"
					"margin: 0px 0px 0px 0px;}"

				"QScrollBar::handle:vartical {"
					"border-radius: 4px;"
					"background: #e3e3df;"
					"min-height: 0px;}"

				"QScrollBar::handle:vertical:hover {"
					"border-radius: 4px;"
					"background: #c7c7bf;"
					"min-height: 0px;}"

				"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

				"QScrollBar::sub-line:vertical {"
					"border: none;"
					"background: none;}");
	this->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
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
      requestTimer_->start(500);
		//letters
    if (kmModifiers == 0 || kmModifiers == Qt::ShiftModifier) {
      if ( (iKey >= Qt::Key_A && iKey <= Qt::Key_Z) ||
						(QKeySequence(iKey).toString() >= "А" && (QKeySequence(iKey).toString() <= "Я")) ||
						QKeySequence(iKey).toString() == "Ё") {
        detailsCheckSelectionAndItem(cursorPos);

				detailsSetCharStyleByNeighbours(ch, cursorPos);
				charStyleVector_.insert(cursorPos, 1, ch);

				QTextEdit::keyPressEvent(event); //we can't identify CapsLock that's why use base method

				detailsSetCharStyleByIndex(ch, cursorPos + 1);

        ++charCounter_;
			//Add coommand to UndoRefoBuffer
				const QString text = (kmModifiers != 0 ?
							QKeySequence(iKey).toString() : QKeySequence(iKey).toString().toLower());
				setCommandInfo(command, command::insertStr, cursorPos, text);
				undoRedoBuffer_->pushUndoCommand(command);
			//
				timer_->stop();
				timer_->start(1000);
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

				detailsSetCharStyleByIndex(ch, cursorPos + 1);

        ++charCounter_;
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, QKeySequence(iKey).toString());
				undoRedoBuffer_->pushUndoCommand(command);
			//
				timer_->stop();
				timer_->start(1000);
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
					detailsSetCharStyleByIndex(ch, cursorPos + 1);

					++charCounter_;
				//Add coommand to UndoRefoBuffer
					setCommandInfo(command, command::insertStr, cursorPos, QKeySequence(iKey).toString());
					undoRedoBuffer_->pushUndoCommand(command);
				//
					timer_->stop();
					timer_->start(1000);
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
				undoRedoBuffer_->pushUndoCommand(command);
			//
				checkSpelling();
				return;
			}
		 //Tab
			case Qt::Key_Tab : {
//				if (this->textCursor().selectedText() != "") {
//					detailsEraseSelectedText(cursorPos);
//        }
				addTab(cursorPos);
				timer_->stop();
				timer_->start(1000);
				return;
      }
			//Shift + Tab
			case Qt::Key_Backtab : {
				backTab(cursorPos);
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
				undoRedoBuffer_->pushUndoCommand(command);
			//
				checkSpelling();
				return;
    }

    if (kmModifiers == Qt::ControlModifier) {
			//Ctrl + z
			if (QKeySequence(iKey) == Qt::Key_Z || QKeySequence(iKey).toString() == "Я") {
				undoCommand();
				timer_->stop();
				timer_->start(1000);
			}
			else if (QKeySequence(iKey) == Qt::Key_Y || QKeySequence(iKey).toString() == "Н") {
				redoCommand();
				timer_->stop();
				timer_->start(1000);
			}
			//Ctrl + d - dash
			else if (QKeySequence(iKey) == Qt::Key_D ||QKeySequence(iKey).toString() == "В") {
				detailsCheckSelectionAndItem(cursorPos);
				this->insertPlainText(dashSign_);
				charStyleVector_.insert(cursorPos, 1, ch);
				++charCounter_;
			//Add coommand to UndoRefoBuffer
				setCommandInfo(command, command::insertStr, cursorPos, dashSign_);
				undoRedoBuffer_->pushUndoCommand(command);
			//
				timer_->stop();
				timer_->start(1000);
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
				undoRedoBuffer_->pushUndoCommand(command);
			//
				timer_->stop();
				timer_->start(1000);
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
		if (this->textCursor().hasSelection()) {
			this->moveCursor(QTextCursor::Right);
		}
    return;
	}

	//Home
	if (iKey == Qt::Key_Home) {
		QTextCursor c = this->textCursor();
		c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
		this->setTextCursor(c);
		return;
	}
	//End
	if (iKey == Qt::Key_End) {
		QTextCursor c = this->textCursor();
		c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
		this->setTextCursor(c);
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
	if (kmModifiers == Qt::ShiftModifier || kmModifiers == (Qt::ShiftModifier | Qt::ControlModifier)) {
		if (QKeySequence(iKey) == Qt::Key_Up || QKeySequence(iKey) == Qt::Key_Down ||
					QKeySequence(iKey) == Qt::Key_Right || QKeySequence(iKey) == Qt::Key_Left) {
			//it is tmp soluton, I want to reimplementate work with shift
			QTextEdit::keyPressEvent(event);
			return;
		}
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
			timer_->stop();
			timer_->start(1000);
		}
		//Ctrl + b - Bold
		else if (QKeySequence(iKey) == Qt::Key_B || QKeySequence(iKey).toString() == "И") {
			if (this->textCursor().hasSelection()) {
				setCharStyle(charStyle::Bold);
			}
			else {
				detailsSetCharStyle(globCh, charStyle::Bold);
			}
		}
		//Ctrl + i - Italic
		else if (QKeySequence(iKey) == Qt::Key_I || QKeySequence(iKey).toString() == "Ш") {
			if (this->textCursor().hasSelection()) {
				setCharStyle(charStyle::Italic);
			}
			else {
				detailsSetCharStyle(globCh, charStyle::Italic);
			}
		}
		//Ctrl + u - Underline
		else if (QKeySequence(iKey) == Qt::Key_U || QKeySequence(iKey).toString() == "Г") {
			if (this->textCursor().hasSelection()) {
				setCharStyle(charStyle::Underline);
			}
			else {
				detailsSetCharStyle(globCh, charStyle::Underline);
			}
		}
		//Ctrl + s - Strike
		else if (QKeySequence(iKey) == Qt::Key_S || QKeySequence(iKey).toString() == "Ы") {
			if (this->textCursor().hasSelection()) {
				setCharStyle(charStyle::Strike);
			}
			else {
				detailsSetCharStyle(globCh, charStyle::Strike);
			}
		}
		//Ctrl + n - Normal
		else if (QKeySequence(iKey) == Qt::Key_N || QKeySequence(iKey).toString() == "Т") {
			makeCharNormal();
			detailsSetCharStyle(globCh);
			return;
		}
		//Ctrl + g - highlight in green
		else if (QKeySequence(iKey) == Qt::Key_G || QKeySequence(iKey).toString() == "П") {
			colorText(colors::green);
			this->moveCursor(QTextCursor::Right);
			return;
		}
		//Ctrl + l - lavender
		else if (QKeySequence(iKey) == Qt::Key_L || QKeySequence(iKey).toString() == "Д") {
			colorText(colors::lavender);
			this->moveCursor(QTextCursor::Right);
			return;
		}
		//Ctrl + m - marina
		else if (QKeySequence(iKey) == Qt::Key_M || QKeySequence(iKey).toString() == "Ь") {
			colorText(colors::marina);
			this->moveCursor(QTextCursor::Right);
			return;
		}
		//Ctrl + o - orange
		else if (QKeySequence(iKey) == Qt::Key_O || QKeySequence(iKey).toString() == "Щ") {
			colorText(colors::orange);
			this->moveCursor(QTextCursor::Right);
			return;
		}
		//Ctrl + r - red
		else if (QKeySequence(iKey) == Qt::Key_R || QKeySequence(iKey).toString() == "К") {
			colorText(colors::red);
			this->moveCursor(QTextCursor::Right);
			checkSpelling();
			return;
		}
  }
	//Ctrl + Shift + D - add new word to dictionary
	if (kmModifiers == (Qt::ShiftModifier | Qt::ControlModifier) &&
			(QKeySequence(iKey) == Qt::Key_D || QKeySequence(iKey).toString() == "В")) {
		rusDic_->addNewWord(this->textCursor().selectedText().toLower());
		timer_->stop();
		timer_->start(1000);
		return;
	}

  //Backspace
  if (QKeySequence(iKey) == Qt::Key_Backspace) {
		//analize item posotion if it is item
		detailsCheckItemPosInDeleting(cursorPos, true, kmModifiers);
		deleteSmth(kmModifiers, QTextCursor::PreviousWord, cursorPos, 0, 1);
		this->textCursor().deletePreviousChar();
		timer_->stop();
		timer_->start(1000);
  }
  //Delete
  else if (QKeySequence(iKey) == Qt::Key_Delete) {
    detailsCheckItemPosInDeleting(cursorPos, false, kmModifiers);
		deleteSmth(kmModifiers, QTextCursor::NextWord, cursorPos, charStyleVector_.size());
    this->textCursor().deleteChar();
		timer_->stop();
		timer_->start(1000);
	}
}

/*void GenTextEdit::paintEvent(QPaintEvent *event)
{
	// use paintEvent() of base class to do the main work
		QTextEdit::paintEvent(event);
		// draw cursor (if widget has focus)
		if (hasFocus()) {
			const QRect qRect = cursorRect(textCursor());
			QPainter qPainter(viewport());
			qPainter.fillRect(qRect, QColor(Qt::red));
		}
}*/

void GenTextEdit::checkSpelling()
{
	QString text = this->toPlainText();
	QTextStream sourseText(&text);
	QChar curCh;
	QString word = "";

	for (int i = 0; i < text.length(); ++i) {
		sourseText >> curCh;
		//dictionary doesn't know about 'Ё' letter
		if (curCh == "ё" || curCh == "Ё") {
			curCh = QChar(RUS_YO_UNICODE);
		}
		curCh = curCh.toLower();

		if (detailsIsLetter(curCh)) {
			word += curCh;
		}
		else if (!word.isEmpty() && curCh == "-") {
			word += curCh;
		}
		else if (!word.isEmpty()) {
			detailsCheckSpelling(word, i);
			word = "";
		}
	}
	//check the last word
	if (!word.isEmpty()) {
		detailsCheckSpelling(word, charCounter_);
	}
}

void GenTextEdit::sendServerRequest()
{
  emit sendServerRequest(nCurrentFile_);
}
