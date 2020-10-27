#include "elementtemplate.h"
#include <QDebug>

#include <QGraphicsDropShadowEffect>

ElementTemplate::ElementTemplate(QGroupBox *parent) : QGroupBox(parent)
{
    this->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
    this->setStyleSheet("ElementTemplate {background: #F9F9F9; border: 0.5px solid #ECECEC; border-radius: 9px;}");

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(0.1);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor("#A0A0A0");
    this->setGraphicsEffect(effect);

  elementLayout_ = new QGridLayout;
  elementLayout_->setHorizontalSpacing(5);

  tagButton_ = new QPushButton;

  settingsButton_ = new QPushButton;
  settingsButton_->setEnabled(false);
  settingsButton_->setFlat(true);

  deleteButton_ = new QPushButton;
	//deleteButton_->setStyleSheet("border-image:url(:/images/images/recycle-bin.png)");
  deleteButton_->setEnabled(false);
  deleteButton_->setFlat(true);

  text_ = new TimetableTextEdit;
	text_->setStyleSheet("background: #FFFFFF; border: 0.4px solid #E3E3E3 ;border-radius: 6px;");

  timeStart_ = new QLineEdit;
  timeEnd_ = new QLineEdit;
  timeStart_->setFocusPolicy(Qt::NoFocus);
  timeEnd_->setFocusPolicy(Qt::NoFocus);

  for (int i = 0; i < TAGS_COUNT; ++i) {
    arrTags_[i].condition = false;
    arrTags_[i].pallete.setColor(QPalette::Button, tag::ARR_COLORS[i]);
  }

  tagButton_->setFixedSize(20, 62);
	tagButton_->setStyleSheet("background: #81C4FF; border-radius: 2px;");

	settingsButton_->setFixedSize(20, 20);

  deleteButton_->setFixedSize(20, 20);
	deleteButton_->setStyleSheet("background: none");

  timeStart_->setFixedSize(45, 25);
    timeStart_->setStyleSheet("background: #FFFFFF; border: 0.4px solid #E3E3E3;border-radius: 6px;");
  timeEnd_->setFixedSize(45, 25);
    timeEnd_->setStyleSheet("background: #FFFFFF; border: 0.4px solid #E3E3E3; border-radius: 6px;");

  text_->setFixedSize(196, 62);

	QFont font("Helvetica", 10);
  text_->setFont(font);

  elementLayout_->addWidget(tagButton_, 0, 0);
  elementLayout_->addWidget(text_, 0, 1);
  elementLayout_->addWidget(settingsButton_, 1, 0);
  elementLayout_->addWidget(deleteButton_, 2, 0);
  elementLayout_->addWidget(timeStart_, 3, 2);
  elementLayout_->addWidget(timeEnd_, 3, 3);

  this->setLayout(elementLayout_);

  connect(deleteButton_, SIGNAL (clicked()), this, SLOT (deleteElement()));
  connect(tagButton_, SIGNAL (clicked()), this, SLOT (changeTagColor()));
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
  inData << this->text_->toPlainText() << this->timeStart_->text() << this->timeEnd_->text() << this->getColor() << dragStartPosition_;

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
  drag->setPixmap(this->grab());
  Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

}

void ElementTemplate::enterEvent(QEvent *event)
{
  tagButton_->setFixedSize(20, 20);

  deleteButton_->setEnabled(true);
  deleteButton_->setFlat(false);
  deleteButton_->setStyleSheet("border-image:url(:/Images/Front/Images/recycle-bin.png)");

  settingsButton_->setEnabled(true);
  settingsButton_->setFlat(false);

  QWidget::enterEvent(event);
}

void ElementTemplate::leaveEvent(QEvent *event)
{
  tagButton_->setFixedSize(20, 62);

  deleteButton_->setEnabled(false);
  deleteButton_->setFlat(true);
  deleteButton_->setStyleSheet("background-color: #eceaec");

  settingsButton_->setEnabled(false);
  settingsButton_->setFlat(true);

  QWidget::leaveEvent(event);
}

void ElementTemplate::setText(QString text, const QVector<charStyle_t>& charArr)
{
  text_->fillCharsAndSetText(text, charArr);
}

void ElementTemplate::setTime(QString timeStart, QString timeEnd)
{
  timeStart_->setText(timeStart.remove(5, 3));
  timeEnd_->setText(timeEnd.remove(5, 3));

  if (timeEnd == "00:00") {
    timeEnd_->hide();
  }
}

void ElementTemplate::setPalette(const QPalette palette)
{
  tagButton_->setPalette(palette);

  for (int i = 0; i < TAGS_COUNT; i++) {
    if (tagButton_->palette() == arrTags_[i].pallete) {
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
      tagButton_->setPalette(arrTags_[(i + 1) % TAGS_COUNT].pallete);
      arrTags_[(i + 1) % TAGS_COUNT].condition = true;

      arrTags_[i].condition = false;

      emit sendDayAndElementIndexAndTagColor(dayIndex_, elementIndex_, tagButton_->palette());

      break;
    }
  }
}

QString ElementTemplate::getText() const
{
  return text_->toPlainText();
}

QPalette ElementTemplate::getColor() const
{
  return tagButton_->palette();
}


