#include <QDebug>
#include <QKeyEvent>

#include "breek.h"

Breek::Breek(QWidget *parent) : QPushButton(parent)
{
  state_ = false;
  workState_ = 1;
  this->setFocusPolicy(Qt::ClickFocus);
}

void Breek::keyPressEvent(QKeyEvent *event)
{
  int iKey = event->key();

  if (iKey == Qt::Key_W) {
    if (workState_ == 1) {
      updateEmoji(emojiComplited_);
      workState_ = 2;
    }
    else if (workState_ == 0) {
      updateEmoji(emoji_);
      workState_ = 1;
    }
  }

  if (iKey == Qt::Key_S) {
    if (workState_ == 1) {
      updateEmoji(emojiDroped_);
      workState_ = 0;
    }
    else if (workState_ == 2){
      updateEmoji(emoji_);
      workState_ = 1;
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

void Breek::setEmoji(const QString emoji, const QString emojiCompleted, const QString emojiDroped)
{
  emoji_ = emoji;
  emojiComplited_ = emojiCompleted;
  emojiDroped_ = emojiDroped;
}

void Breek::setIndex(const int zoneIndex, const int dayIndex)
{
  zoneIndex_ = zoneIndex;
  dayIndex_ = dayIndex;
}

void Breek::changeBreekState()
{
  state_ = !state_;
  this->setEnabled(!this->isEnabled());

  QString emoji = "";
  if (state_) {
    emoji = emoji_;
  }

  updateEmoji(emoji);
	//this->setFlat(!this->isFlat());
}

void Breek::updateEmoji(const QString& emoji)
{
  QPixmap pix(emoji);
  pix = pix.scaledToWidth(this->width(), Qt::SmoothTransformation);
  QIcon buttonIcon(pix);
  this->setIcon(buttonIcon);
  this->setIconSize(pix.rect().size());
}
