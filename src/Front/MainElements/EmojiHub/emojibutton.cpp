#include "emojibutton.h"

EmojiButton::EmojiButton(const int num) :
	num_(num)
{
	this->setStyleSheet("border-image: url(:/Images/Front/Images/Breeks/" + QString::number(num_) + ".png)");
}

void EmojiButton::mousePressEvent(QMouseEvent *event)
{
	emit chosed(num_);
}
