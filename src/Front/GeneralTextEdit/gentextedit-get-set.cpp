#include "gentextedit.h"

void GenTextEdit::recieveUsername(const QString username) //SLOT
{
  username_ = username;
}

int GenTextEdit::getNumberCurrentFile()
{
    return nCurrentFile_;
}

void GenTextEdit::clearCharStyleVector()
{
  charStyleVector_.clear();
	charCounter_ = 0;
}

QVector<charStyle_t> GenTextEdit::getCharStyleVector()
{
    return charStyleVector_;
}
void GenTextEdit::setNumberCurrentFile(const int n)
{
  if (n >= 1 && n <= 6) {
    nCurrentFile_ = n;
  }
}

void GenTextEdit::fillCharStyleVector(int cursorPos, int count, charStyle_t ch)
{
    charStyleVector_.insert(cursorPos, count, ch);
}

void GenTextEdit::fillCharsAndSetText(QString text, const QJsonArray jArr)
{
		this->clearCharStyleVector();
		this->setCharCounter(jArr.size());

		QTextStream out(&text);
		QChar tmpChar;
		charStyle_t ch;

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

void GenTextEdit::fillCharsAndSetTextt(QString & text, QVector<charStyle_t> & styles)
{
	qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PRINT");

		this->clearCharStyleVector();
		this->setCharCounter(styles.size());

		QTextStream out(&text);
		QChar tmpChar;
		charStyle_t ch;

		for (int i = 0; i < this->getCharCounter(); ++i) {
			detailsSetCharStyle(ch);
			QTextCharFormat charFormat;
			charFormat.setFontWeight(QFont::Normal);

			bool boldStatus = styles[i].bold;
			bool italicStatus = styles[i].italic;
			bool underlineStatus = styles[i].underline;
			bool strikeStatus = styles[i].strike;
			bool itemStatus = styles[i].item;
			bool starStatus = styles[i].star;
			QString color = styles[i].sColor;

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

void GenTextEdit::setStylesToChar(charStyle_t& ch, QTextCharFormat& charFormat, const QJsonObject jChar)
{
  GenTextEdit::detailsSetCharStyle(ch);
	charFormat.setFontWeight(QFont::Normal);

  bool boldStatus = jChar.value("bold").toBool();
  bool italicStatus = jChar.value("italic").toBool();
  bool underlineStatus = jChar.value("underline").toBool();
  bool strikeStatus = jChar.value("strike").toBool();
  bool itemStatus = jChar.value("item").toBool();
  bool starStatus = jChar.value("star").toBool();
  QString color = jChar.value("sColor").toString();
	bool spellChecker = jChar.value("spellChecker").toBool();

  if (boldStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Bold);
    charFormat.setFontWeight(QFont::Bold);
  }
  if (italicStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Italic);
    charFormat.setFontItalic(true);
  }
  if (underlineStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Underline);
    charFormat.setFontUnderline(true);
  }
  if (strikeStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Strike);
    charFormat.setFontStrikeOut(true);
  }
  if (itemStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Item);
    charFormat.setFontWeight(QFont::Normal);
  }
  if (starStatus == true) {
    GenTextEdit::detailsSetCharStyle(ch, charStyle::Star);
    charFormat.setFontWeight(QFont::Normal);
  }
	if (spellChecker == true) {
		GenTextEdit::detailsSetCharStyle(ch, charStyle::SpellChecker);
	}
  ch.sColor = color;
	if (color != "") {
		charFormat.setBackground(QColor(color));
	}
	else {
		charFormat.setBackground(Qt::NoBrush);
	}
}

void GenTextEdit::getCharStyle(const int index, charStyle_t& ch) const
{
  if (index < 0 || index >= charCounter_) {
    qDebug() << "Index is out of range!";
		return;
  }
	ch = charStyleVector_[index];
}

int GenTextEdit::getCharCounter() const
{
  return charCounter_;
}
void GenTextEdit::setCharCounter(int value)
{
  charCounter_ = value;
}
