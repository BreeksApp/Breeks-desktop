//VIEW

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QQmlProperty>
#include <QQuickItem>
#include <QtConcurrent/QtConcurrent>

#include <iostream>

#include "breek.h"

Breek::Breek(QWidget *parent):
  QPushButton(parent),
  state_(false),
  workState_(Conditions::GREY_FOREGROUND),
  width_(80),
  height_(80),
  quickWidget_(nullptr),
  graphObject_(nullptr)
{
  this->setFocusPolicy(Qt::ClickFocus);
  this->setFixedSize(width_, height_);
  this->setFlat(true);

	callHub_ = false;
}

Breek::Breek(int width, int height, QWidget *parent):
  QPushButton(parent),
  state_(false),
  workState_(Conditions::GREY_FOREGROUND),
  width_(width),
  height_(height),
  quickWidget_(nullptr),
  graphObject_(nullptr)
{
  this->setFocusPolicy(Qt::ClickFocus);
  this->setFixedSize(width_, height_);
  this->setFlat(true);
}

Breek::~Breek()
{
  graphObject_ = nullptr;
  delete quickWidget_;
}

void Breek::keyPressEvent(QKeyEvent *event)
{
  int iKey = event->key();

	if (event->modifiers() == 0 && !isAnimated_) {
		if (iKey == Qt::Key_W || QKeySequence(iKey).toString() == "Ц") {
			isAnimated_ = true;

			if (workState_ == Conditions::RED) {
			    connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::GREY_BACKGROUND);
			    workState_ = Conditions::GREY_BACKGROUND;
			}
			else if (workState_ == Conditions::GREY_FOREGROUND) {
			    connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::RED);
			    workState_ = Conditions::RED;
			}
			else if (workState_ == Conditions::GREEN) {
			    connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::GREY_FOREGROUND);
			    workState_ = Conditions::GREY_FOREGROUND;
			}
			else {
			    connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::GREEN);
			    workState_ = Conditions::GREEN;
			}

			QFuture<void> future = QtConcurrent::run(this, &Breek::waitAnimationEnd);
		}

		if (iKey == Qt::Key_S || QKeySequence(iKey).toString() == "Ы") {
			isAnimated_ = true;

			if (workState_ == Conditions::RED) {
			    connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::GREY_FOREGROUND);
			    workState_ = Conditions::GREY_FOREGROUND;
			}
			else if (workState_ == Conditions::GREY_FOREGROUND) {
			    connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::GREEN);
			    workState_ = Conditions::GREEN;
			}
			else if (workState_ == Conditions::GREEN){
			    connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::GREY_BACKGROUND);
			    workState_ = Conditions::GREY_BACKGROUND;
			}
			else {
			    connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::RED);
			    workState_ = Conditions::RED;
			}

			QFuture<void> future = QtConcurrent::run(this, &Breek::waitAnimationEnd);
		}

		if (iKey == Qt::Key_D || QKeySequence(iKey).toString() == "В") {
			isAnimated_ = true;
			if (callHub_) {
				emit doubleClicked();
			}
			emit moveBreek(zoneIndex_, dayIndex_, true);
			QFuture<void> future = QtConcurrent::run(this, &Breek::waitAnimationEnd);
		}

		if (iKey == Qt::Key_A || QKeySequence(iKey).toString() == "Ф") {
			isAnimated_ = true;
			if (callHub_) {
				emit doubleClicked();
			}
			emit moveBreek(zoneIndex_, dayIndex_, false);
			QFuture<void> future = QtConcurrent::run(this, &Breek::waitAnimationEnd);
		}

		if (iKey == Qt::Key_E || QKeySequence(iKey).toString() == "У") {
			qDebug() << dayIndex_;
			emit doubleClicked();
		}

		if (iKey == Qt::Key_Q || QKeySequence(iKey).toString() == "Й") {
			emit changeState(zoneIndex_, dayIndex_);
		}
	}

	if (event->modifiers() == Qt::ControlModifier) {
		if (QKeySequence(iKey) == Qt::Key_A || QKeySequence(iKey).toString() == "Ф") {
			if (dayIndex_ > 0) {
				emit (changeState(zoneIndex_, dayIndex_ - 1));
			}
		}
		if (QKeySequence(iKey) == Qt::Key_D || QKeySequence(iKey).toString() == "В") {
			if (dayIndex_ < 5) {
				emit (changeState(zoneIndex_, dayIndex_ + 1));
			}
		}
	}

	//for description
	if (workState_ == Conditions::GREY_FOREGROUND || workState_ == Conditions::GREY_BACKGROUND || !state_) {
		if (state_) {
			emit sendSateToLilDay(zoneIndex_, dayIndex_, 0);
		}
	}
	else if (workState_ == Conditions::GREEN) {
		emit sendSateToLilDay(zoneIndex_, dayIndex_, 1);
	}
	else {
		emit sendSateToLilDay(zoneIndex_, dayIndex_, 2);
	}
}

void Breek::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit doubleClicked();
	this->setFocus();
}

void Breek::mousePressEvent(QMouseEvent *event)
{
	this->setFocus();
}

void Breek::focusInEvent(QFocusEvent *)
{
	connectToQml(Conditions::SHADOW, true);
	emit setZoneFocus(zoneIndex_, true);
}

void Breek::focusOutEvent(QFocusEvent *)
{
	connectToQml(Conditions::SHADOW, false);
	emit setZoneFocus(zoneIndex_, false);
}

bool Breek::getState()
{
  return state_;
}

void Breek::setState(bool state)
{
	state_ = state;
}

Conditions Breek::getColorState()
{
	return workState_;
}

void Breek::setColorState(Conditions cond)
{
	workState_ = cond;
}

void Breek::connectToQml(int indexOfEmoji, Conditions cond)
{
	//if (indexOfEmoji < 0 || indexOfEmoji > 68) return;

  // код, связывающий кнопку с qml
  if (quickWidget_ == nullptr) {
    quickWidget_ = new QQuickWidget(QUrl("qrc:/qml/Front/Qml/qml_for_breeks.qml"), this);
    quickWidget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget_->setFixedSize(1.125*width_, 1.125*height_);
    graphObject_ = quickWidget_->rootObject();
  }

  if (!quickWidget_->isVisible()) quickWidget_->setVisible(true);

  graphObject_->setProperty("indexOfEmoji", indexOfEmoji);
  QQmlProperty(graphObject_, "animationOn").write(false);
	graphObject_->setProperty("indexOfCondFrom", cond);
	graphObject_->setProperty("indexOfCondTo", cond);
	graphObject_->setProperty("size1", 80);
	graphObject_->setProperty("size2", 80);

  // работа с фоном сцены
  QColor color;
	color.setNamedColor("#F7F7F7");
	quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
  // конец кода, связывающего кнопку с qml
}

void Breek::connectToQml(Conditions cond, bool isShadow)
{
	QQmlProperty(graphObject_, "animationOn").write(false);

	if (!isShadow && cond != Conditions::SHADOW) {
		graphObject_->setProperty("indexOfCondFrom", cond);
		graphObject_->setProperty("indexOfCondTo", cond);
	}
	else {
		if (isShadow) {
			graphObject_->setProperty("bigShadow", true);
		}
		else {
			graphObject_->setProperty("bigShadow", false);
		}
	}

	graphObject_->setProperty("size1", 80);
	graphObject_->setProperty("size2", 80);

	// работа с фоном сцены
	QColor color;
	color.setNamedColor("#F7F7F7");
	quickWidget_->quickWindow()->setColor(color);
}

void Breek::connectToQml(int indexOfEmoji, Directions dir,
                         Conditions from, Conditions to)
{
	//if (indexOfEmoji < 0 || indexOfEmoji > 68) return;

  // код, связывающий кнопку с qml
  if (quickWidget_ == nullptr) {
      quickWidget_ = new QQuickWidget(QUrl("qrc:/qml/Front/Qml/qml_for_breeks.qml"), this);
      quickWidget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
      quickWidget_->setFixedSize(1.125*width_, 1.125*height_);
      graphObject_ = quickWidget_->rootObject();
  }

  graphObject_->setProperty("indexOfEmoji", indexOfEmoji);
  QQmlProperty(graphObject_, "direction").write(dir);
  graphObject_->setProperty("indexOfCondFrom", from);
  graphObject_->setProperty("indexOfCondTo", to);
  QQmlProperty(graphObject_, "animationOn").write(false);
	QQmlProperty(graphObject_, "animationOn").write(true);
	graphObject_->setProperty("size1", 80);
	graphObject_->setProperty("size2", 80);
  // работа с фоном сцены
//  QColor color = Qt::GlobalColor::gray;
//  quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
  // конец кода, связывающего кнопку с qml
}

void Breek::setEmoj(int numOfEmoji)
{
	nEmoj_ = numOfEmoji;
}

int Breek::getEmojiNum()
{
  return nEmoj_;
}

void Breek::setIndex(const int zoneIndex, const int dayIndex)
{
  zoneIndex_ = zoneIndex;
  dayIndex_ = dayIndex;
}

void Breek::changeBreekState()
{
  state_ = !state_;
	workState_ = Conditions::GREY_FOREGROUND;
  this->setEnabled(!this->isEnabled());

  if (state_) {
		connectToQml(nEmoj_, workState_);
		callHub_ = false;
  } else {
    this->quickWidget_->setVisible(false);
		if (callHub_) {
			emit doubleClicked();
			callHub_ = false;
		}
  }

	emit isHere(zoneIndex_, dayIndex_, state_);
	//this->setFocus();
}

void Breek::changeEmoji(int nEmoji)
{
	nEmoj_ = nEmoji;
	connectToQml(nEmoj_, Conditions::YELLOW);
	this->setFocus();
}

void Breek::closeEmojiHub()
{
	callHub_ = false;
	this->setFocus();

	if (state_) {
		connectToQml(nEmoj_, workState_);
	}
}

void Breek::openEmojiHub()
{
	callHub_ = true;
	connectToQml(Conditions::YELLOW);
}

int Breek::getWidth()
{
  return width_;
}

int Breek::getHeight()
{
	return height_;
}

void Breek::waitAnimationEnd()
{
	QThread::msleep(500);
	isAnimated_ = false;
}

void Breek::setZoneIndex(int zoneIndex)
{
	zoneIndex_ = zoneIndex;
}
