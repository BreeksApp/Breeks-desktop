#include "emojibutton.h"

EmojiButton::EmojiButton(const int num) :
	num_(num)
{

}

void EmojiButton::mousePressEvent(QMouseEvent *event)
{
	emit chosed(num_);
}
