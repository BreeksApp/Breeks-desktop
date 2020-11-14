#include "elementtemplate.h"
#include <QDebug>

#include <QGraphicsDropShadowEffect>
#include <QScrollBar>

ElementTemplate::ElementTemplate(QGroupBox *parent) : QGroupBox(parent)
{
	this->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	this->setStyleSheet("ElementTemplate {background: #F9F9F9; border: 0.4px solid #cbcbcb; border-radius: 8px;}");

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(5);
	effect->setXOffset(0);
	effect->setYOffset(0);
	effect->setColor("#BABCBE");
	this->setGraphicsEffect(effect);

  elementLayout_ = new QGridLayout;
	//elementLayout_->setHorizontalSpacing(5);

  tagButton_ = new QPushButton;

	scaleButton_ = new QPushButton;
	scaleButton_->setEnabled(false);
	scaleButton_->setFlat(true);

  deleteButton_ = new QPushButton;
	//deleteButton_->setStyleSheet("border-image:url(:/images/images/recycle-bin.png)");
  deleteButton_->setEnabled(false);
  deleteButton_->setFlat(true);

	text_ = new TimetableTextEdit;
	text_->setStyleSheet("background: #FFFFFF; border: 0.5px solid #EEEEEE; border-radius: 6px;");
	text_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	timeStart_ = new TimeEdit();
	timeEnd_ = new TimeEdit();
	//timeStart_->setFocusPolicy(Qt::NoFocus);
	//timeEnd_->setFocusPolicy(Qt::NoFocus);
	timeStart_->setAlignment(Qt::AlignCenter);
	timeEnd_->setAlignment(Qt::AlignCenter);

  for (int i = 0; i < TAGS_COUNT; ++i) {
    arrTags_[i].condition = false;
		arrTags_[i].sColor = tag::ARR_COLORS[i];
  }

	tagButton_->setFixedSize(20, 62);
	tagButton_->setStyleSheet("QPushButton {background: #81C4FF; border-radius: 3px;}");

	scaleButton_->setFixedSize(20, 20);
	scaleButton_->setStyleSheet("background: none");
	isScaled_ = false;

	deleteButton_->setFixedSize(20, 20);
	deleteButton_->setStyleSheet("background: none");

	timeStart_->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
	timeStart_->setFixedSize(50, 20);
	timeStart_->setStyleSheet("QTimeEdit::up-button {"
														"border-image:url(:/Images/Front/Images/caret-up.png);"
														"width: 13px;}"
														"QTimeEdit::down-button {"
														"border-image:url(:/Images/Front/Images/caret-down.png);"
														"width: 13px}");

	timeEnd_->setFixedSize(50, 20);
	timeEnd_->setStyleSheet("QTimeEdit::up-button {"
														"border-image:url(:/Images/Front/Images/caret-up.png);"
														"width: 13px;}"
														"QTimeEdit::down-button {"
														"border-image:url(:/Images/Front/Images/caret-down.png);"
														"width: 13px}");

	text_->setFixedHeight(tagButton_->height());
	QFont font("Helvetica", 10);
	text_->setFont(font);

	elementLayout_->addWidget(tagButton_, 0, 0);
	elementLayout_->addWidget(text_, 0, 1, 2, 3);
	elementLayout_->addWidget(deleteButton_, 2, 0);
	elementLayout_->addWidget(scaleButton_, 1, 0);
	elementLayout_->addWidget(timeStart_, 3, 2);
	elementLayout_->addWidget(timeEnd_, 3, 3);

  this->setLayout(elementLayout_);

  connect(deleteButton_, SIGNAL (clicked()), this, SLOT (deleteElement()));
  connect(tagButton_, SIGNAL (clicked()), this, SLOT (changeTagColor()));
	connect(scaleButton_, SIGNAL(clicked()), this, SLOT (scaleTextEdit()));
}

void ElementTemplate::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
     dragStartPosition_ = event->pos();

  }
  elementData_t data;
  data.text = text_->toPlainText();
  emit sendMimeData(data, this->grab());
}

void ElementTemplate::mouseMoveEvent(QMouseEvent *event)
{
  if (!(event->buttons() & Qt::LeftButton)) {
    return;
  }
  if ((event->pos() - dragStartPosition_).manhattanLength() < QApplication::startDragDistance())
    return;

  QDrag *drag = new QDrag(this);
  QMimeData *mimeData = new QMimeData;

  QByteArray data;
  QDataStream inData(&data, QIODevice::WriteOnly);
	inData << this->text_->toPlainText() << this->timeStart_->text() << this->timeEnd_->text() << this->getTagColor() << dragStartPosition_;

  QByteArray charVector;
  QDataStream inVector(&charVector, QIODevice::WriteOnly);
  inVector << this->getCharStyleVector().size();
  for (charStyle_t ch: this->getCharStyleVector()) {
    inVector << ch.bold << ch.italic << ch.underline << ch.strike << ch.item << ch.star << ch.sColor;
  }

  QByteArray indexes;
  QDataStream inIndexes(&indexes, QIODevice::WriteOnly);
  inIndexes << dayIndex_ << elementIndex_;

  mimeData->setData("elemData", data);
  mimeData->setData("charVector", charVector);
  mimeData->setData("indexes", indexes);
  drag->setMimeData(mimeData);

	this->setAttribute(Qt::WA_NoSystemBackground);

	this->setStyleSheet("QGroupBox {background: #F9F9F9; border-radius: 8px; border: 1.3px solid #DDDDDD}");
	this->graphicsEffect()->setEnabled(false);
  drag->setPixmap(this->grab());

	this->hide();
	emit defineDayMoveFrom(dayIndex_, "d0f896");

  Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

	emit dropNoChanges();
	emit defineDayMoveFrom(dayIndex_, "d0f896");

	if (!this->isHidden()) {
		emit deleteItem(dayIndex_, elementIndex_);
	}
	else {
		this->show();
		this->graphicsEffect()->setEnabled(true);
		this->setStyleSheet("QGroupBox{background: #F9F9F9; border: 0.4px solid #cbcbcb; border-radius: 8px;}");
	}
}

void ElementTemplate::enterEvent(QEvent *event)
{
  tagButton_->setFixedSize(20, 20);

	if (!isScaled_ & text_->document()->size().height() > 56) {
		scaleButton_->setEnabled(true);
		scaleButton_->setFlat(false);
		scaleButton_->setStyleSheet("background: #F9F9F9; border-image:url(:/Images/Front/Images/caret-down.png)");
	}
	else if (isScaled_) {
		scaleButton_->setEnabled(true);
		scaleButton_->setFlat(false);
		scaleButton_->setStyleSheet("background: #F9F9F9; border-image:url(:/Images/Front/Images/caret-up.png)");
	}

  deleteButton_->setEnabled(true);
	deleteButton_->setFlat(false);
	deleteButton_->setStyleSheet("background: #F9F9F9; border-image:url(:/Images/Front/Images/trash.png)");

  QWidget::enterEvent(event);
}

void ElementTemplate::leaveEvent(QEvent *event)
{
  tagButton_->setFixedSize(20, 62);

  deleteButton_->setEnabled(false);
  deleteButton_->setFlat(true);
	deleteButton_->setStyleSheet("background: none");

	scaleButton_->setEnabled(false);
	scaleButton_->setFlat(true);
	scaleButton_->setStyleSheet("background: none");

	QWidget::leaveEvent(event);
}

int ElementTemplate::getWidth()
{
	return this->width();
}

void ElementTemplate::setText(QString text, const QVector<charStyle_t>& charArr)
{
	text_->setFocus();
  text_->fillCharsAndSetText(text, charArr);
	text_->moveCursor(QTextCursor::Start);

	text_->verticalScrollBar()->maximum();
	//text_->verticalScrollBar()->move(0, 0);
}

void ElementTemplate::setTime(QString timeStart, QString timeEnd)
{
	timeStart_->setTime(QTime(timeStart.left(2).toInt(), timeStart.mid(3, 4).toInt()));
	timeEnd_->setTime(QTime(timeEnd.left(2).toInt(), timeEnd.mid(3, 4).toInt()));
	//timeStart_->setText(timeStart.remove(5, 3));
	//timeEnd_->setText(timeEnd.remove(5, 3));

	/*if (timeEnd == "00:00") { //нужно расширить условие
    timeEnd_->hide();
	}*/
}

void ElementTemplate::setTagColor(const QString sColor)
{
	tagButton_->setStyleSheet("QPushButton {background:" + sColor + "; border-radius: 3px;}");
	tagColor_ = sColor;

  for (int i = 0; i < TAGS_COUNT; i++) {
		if (tagColor_ == arrTags_[i].sColor) {
      arrTags_[i].condition = true;
    }
    else {
      arrTags_[i].condition = false;
    }
  }
}

void ElementTemplate::deleteElement()
{
  emit sendDayAndElementIndex(dayIndex_, elementIndex_);
}

void ElementTemplate::scaleTextEdit()
{
	//int fullHeight = static_cast<int>(text_->document()->size().height());
	//int diff = fullHeight - TEXT_HEIGHT + 4;

	int diff = 0;

	if (!isScaled_) {
		diff = 48;
		isScaled_ = true;

		but1 = new QPushButton();
		but1->setFixedSize(20, 30);
		elementLayout_->addWidget(but1, 3, 0);
		but2 = new QPushButton();
		but2->setFixedSize(20, 30);
		but1->setEnabled(false);
		but2->setEnabled(false);
		but1->setStyleSheet("background: none;");
		but2->setStyleSheet("background: none;");
		elementLayout_->addWidget(but2, 4, 0);
		elementLayout_->addWidget(timeStart_, 5, 2);
		elementLayout_->addWidget(timeEnd_, 5, 3);

		//elementLayout_->addWidget(deleteButton_, 3, 0);
		scaleButton_->setStyleSheet("background: #F9F9F9; border-image:url(:/Images/Front/Images/caret-up.png)");
		elementLayout_->addWidget(text_, 0, 1, 3, 3);

		text_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
		text_->verticalScrollBar()->setStyleSheet(
					"QScrollBar:vertical {"
						"border: 0.1px solid #FFFFFF;"
						"background: #FFFFFF;"
						"width: 9px;"
						"margin: 0px 0px 0px 0px;}"

					"QScrollBar::handle:vertical {"
						"border: 0.5px solid #c7c7bf;"
						"border-radius: 4px;"
						"background: #c7c7bf;"
						"min-height: 0px;}"

					"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

					"QScrollBar::sub-line:vartical {"
					"border: none;"
					"background: none;}");
	}
	else {
		diff = -48;

		elementLayout_->removeWidget(but1);
		elementLayout_->removeWidget(but2);
		elementLayout_->addWidget(timeStart_, 3, 2);
		elementLayout_->addWidget(timeEnd_, 3, 3);

		isScaled_ = false;
		if (text_->document()->size().height() > 56) {
			scaleButton_->setStyleSheet("background: #F9F9F9; border-image:url(:/Images/Front/Images/caret-down.png)");
		}

		text_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	}

	ELEMENT_HEIGHT += diff;
	TEXT_HEIGHT += diff;

	this->setFixedHeight(ELEMENT_HEIGHT);
	text_->setFixedHeight(TEXT_HEIGHT);

	emit(changeElementsLayoutHeight(dayIndex_, diff));
}

void ElementTemplate::setDayAndElementIndex(const int dayIndex, const int elementIndex)
{
  dayIndex_ = dayIndex;
  elementIndex_ = elementIndex;
}

void ElementTemplate::setElementIndex(const int index)
{
    elementIndex_ = index;
}

QVector<charStyle_t> ElementTemplate::getCharStyleVector()
{
 return text_->getCharStyleVector();
}

void ElementTemplate::changeTagColor()
{
  for (int i = 0; i < TAGS_COUNT; ++i) {
		if (arrTags_[i].condition == true) {
			setTagColor(arrTags_[(i + 1) % TAGS_COUNT].sColor);
      arrTags_[(i + 1) % TAGS_COUNT].condition = true;
      arrTags_[i].condition = false;
			emit sendDayAndElementIndexAndTagColor(dayIndex_, elementIndex_, tagColor_);

      break;
    }
  }
}

QString ElementTemplate::getText() const
{
  return text_->toPlainText();
}

QString ElementTemplate::getTagColor() const
{
	return tagColor_;
}


