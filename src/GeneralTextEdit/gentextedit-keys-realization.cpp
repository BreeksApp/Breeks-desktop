#include "gentextedit.h"

//---------BACKSPACE / DELETE
void GenTextEdit::deleteRealization(Qt::KeyboardModifiers kmModifiers, QTextCursor::MoveOperation whereMove,
																					 int cursorPos, int blindSpot, int a)
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

//---------SET STYLE FOR CHAR
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
