#include "elementtemplate.h"
#include <QDebug>

ElementTemplate::ElementTemplate(QGroupBox *parent) : QGroupBox(parent)
{
  this->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);

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

	text_ = new GenTextEdit;

  timeStart_ = new QLineEdit;
  timeEnd_ = new QLineEdit;
  timeStart_->setFocusPolicy(Qt::NoFocus);
  timeEnd_->setFocusPolicy(Qt::NoFocus);

  for (int i = 0; i < TAGS_COUNT; ++i) {
    arrTags_[i].condition = false;
    arrTags_[i].pallete.setColor(QPalette::Button, tag::ARR_COLORS[i]);
  }

  tagButton_->setFixedSize(20, 62);
  settingsButton_->setFixedSize(20, 20);
  deleteButton_->setFixedSize(20, 20);

  timeStart_->setFixedSize(45, 25);
  timeEnd_->setFixedSize(45, 25);

  text_->setFixedSize(196, 62);

  QFont font("Helvetica", 12);
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

void ElementTemplate::enterEvent(QEvent *event)
{
  tagButton_->setFixedSize(20, 20);

  deleteButton_->setEnabled(true);
  deleteButton_->setFlat(false);
  deleteButton_->setStyleSheet("border-image:url(:/Images/Images/recycle-bin.png)");

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

void ElementTemplate::setText(QString text)
{
  text_->setText(text);
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


