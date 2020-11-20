#ifndef EMOJIBUTTON_H
#define EMOJIBUTTON_H

#include <QPushButton>



class EmojiButton : public QPushButton
{
	Q_OBJECT
public:
	EmojiButton(const int);
	void mousePressEvent(QMouseEvent *event);

signals :
	void chosed(int);

private:
	int num_;
};

#endif // EMOJIBUTTON_H
