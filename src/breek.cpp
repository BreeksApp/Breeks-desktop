#include <QDebug>
#include <QKeyEvent>
#include <QQmlProperty>
#include <QQuickItem>

#include "breek.h"

Breek::Breek(QWidget *parent):
  QPushButton(parent),
  state_(false),
  workState_(Conditions::GREY),
  width_(80),
  height_(80),
  quickWidget_(nullptr),
  graphObject_(nullptr)
{
  this->setFocusPolicy(Qt::ClickFocus);
  this->setFixedSize(width_, height_);
  this->setFlat(true);
}

Breek::Breek(int width, int height, QWidget *parent):
  QPushButton(parent),
  state_(false),
  workState_(Conditions::GREY),
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

  if (iKey == Qt::Key_W) {
    if (workState_ == Conditions::RED) {
//      updateEmoji(emoji_);
      connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::GREY);
      workState_ = Conditions::GREY;
    }
    else if (workState_ == Conditions::GREY) {
//      updateEmoji(emojiComplited_);
      connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::GREEN);
      workState_ = Conditions::GREEN;
    }
    else {
      connectToQml(nEmoj_, Directions::DOWNSIDE, workState_, Conditions::RED);
      workState_ = Conditions::RED;
    }
  }

  if (iKey == Qt::Key_S) {
    if (workState_ == Conditions::RED) {
//      updateEmoji(emoji_);
      connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::GREEN);
      workState_ = Conditions::GREEN;
    }
    else if (workState_ == Conditions::GREY) {
//      updateEmoji(emojiDroped_);
      connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::RED);
      workState_ = Conditions::RED;
    }
    else if (workState_ == Conditions::GREEN){
//      updateEmoji(emoji_);
      connectToQml(nEmoj_, Directions::UPSIDE, workState_, Conditions::GREY);
      workState_ = Conditions::GREY;
    }
  }

  if (iKey == Qt::Key_D) {
    emit moveBreek(zoneIndex_, dayIndex_, true);
  }

  if (iKey == Qt::Key_A) {
    emit moveBreek(zoneIndex_, dayIndex_, false);
  }
}

bool Breek::getState()
{
  return state_;
}

void Breek::setState(bool state)
{
  state_ = state;
}

void Breek::connectToQml(int indexOfEmoji)
{
  if (indexOfEmoji < 1 || indexOfEmoji > 9) return;

  // код, связывающий кнопку с qml
  if (quickWidget_ == nullptr) {
    quickWidget_ = new QQuickWidget(QUrl("qrc:/qml/Qml/qml_for_breeks.qml"), this);
    quickWidget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget_->setFixedSize(0.875 * width_, 0.875 * height_);
    graphObject_ = quickWidget_->rootObject();
  }

  graphObject_->setProperty("indexOfEmoji", indexOfEmoji);
  QQmlProperty(graphObject_, "animationOn").write(false);
  graphObject_->setProperty("indexOfCondFrom", Conditions::GREY);

  // работа с фоном сцены
//  QColor color = Qt::GlobalColor::gray;
//  quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
  // конец кода, связывающего кнопку с qml
}

void Breek::connectToQml(int indexOfEmoji, Directions dir,
                         Conditions from, Conditions to)
{
  if (indexOfEmoji < 1 || indexOfEmoji > 9) return;

  // код, связывающий кнопку с qml
  if (quickWidget_ == nullptr) {
      quickWidget_ = new QQuickWidget(QUrl("qrc:/qml/Qml/qml_for_breeks.qml"), this);
      quickWidget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
      quickWidget_->setFixedSize(0.875 * width_, 0.875 * height_);

      graphObject_ = quickWidget_->rootObject();
  }

  graphObject_->setProperty("indexOfEmoji", indexOfEmoji);
  QQmlProperty(graphObject_, "direction").write(dir);
  graphObject_->setProperty("indexOfCondFrom", from);
  graphObject_->setProperty("indexOfCondTo", to);
  QQmlProperty(graphObject_, "animationOn").write(false);
  QQmlProperty(graphObject_, "animationOn").write(true);

  // работа с фоном сцены
//  QColor color = Qt::GlobalColor::gray;
//  quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
  // конец кода, связывающего кнопку с qml
}

void Breek::setEmoj(int numOfEmoji)
{
  if (numOfEmoji > 0 && numOfEmoji < 10) nEmoj_ = numOfEmoji;
}

//void Breek::setEmoji(const QString emoji, const QString emojiCompleted, const QString emojiDroped)
//{
//  emoji_ = emoji;
//  emojiComplited_ = emojiCompleted;
//  emojiDroped_ = emojiDroped;
//}

void Breek::setIndex(const int zoneIndex, const int dayIndex)
{
  zoneIndex_ = zoneIndex;
  dayIndex_ = dayIndex;
}

void Breek::changeBreekState()
{
  state_ = !state_;
  this->setEnabled(!this->isEnabled());

//  QString emoji = "";
//  if (state_) {
//    emoji = emoji_;
//  }
//  updateEmoji(emoji);
  connectToQml(nEmoj_);
	//this->setFlat(!this->isFlat());
}

//void Breek::updateEmoji(const QString& emoji)
//{
//  QPixmap pix(emoji);
//  pix = pix.scaledToWidth(this->width(), Qt::SmoothTransformation);
//  QIcon buttonIcon(pix);
//  this->setIcon(buttonIcon);
//  this->setIconSize(pix.rect().size());
//}

int Breek::getWidth()
{
  return width_;
}

int Breek::getHeight()
{
  return height_;
}
