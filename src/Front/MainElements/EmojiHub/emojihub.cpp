#include "emojihub.h"

#include <QGraphicsDropShadowEffect>
#include <QScrollBar>
#include <QKeyEvent>

EmojiHub::EmojiHub(QWidget *parent) : QGroupBox(parent)
{
	this->setFixedSize(160, 90);
	this->setContentsMargins(0, 1, 0, 1);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(5);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	this->setGraphicsEffect(effect);
	this->setStyleSheet("background: none; border-radius: 10px; border: 0.4px solid #FFFFFF;");

	QLayout *layout = new QVBoxLayout;
	this->setLayout(layout);

	scrollArea_ = new QScrollArea;
	layout->addWidget(scrollArea_);

	QWidget *widget = new QWidget;
	QGridLayout *layout2 = new QGridLayout;

	scrollArea_->setStyleSheet("background:#FFFFFF; border-radius: 8px;");
	//scrollArea->setFixedHeight(80);
	scrollArea_->verticalScrollBar()->setStyleSheet(
				"QScrollBar:vertical {"
					"border: 0.1px solid #FFFFFF;"
					"background: #FFFFFF;"
					"width: 9px;"
					"margin: 0px 0px 0px 0px;}"

				"QScrollBar::handle:vertical {"
					//"border: 0.5px solid #c7c7bf;"
					"border-radius: 4px;"
					"background: #e3e3df;"
					"min-height: 40px;}"

				"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

				"QScrollBar::sub-line:vartical {"
					"border: none;"
					"background: none;}");

	scrollArea_->setWidgetResizable(true);
	scrollArea_->setWidget(widget);
	widget->setLayout(layout2);

	for (int i = 0; i < N_EMOJIES; ++i) {
		arrEmoji_[i] = new EmojiButton(i);
		arrEmoji_[i]->setFixedSize(40, 40);
		layout2->addWidget(arrEmoji_[i], i / 2, i % 2);

		connect (arrEmoji_[i], SIGNAL(chosed(int)), this, SLOT(chosed(int)));
	}

	scrollArea_->hide();
}

void EmojiHub::keyPressEvent(QKeyEvent *event)
{
	int iKey = event->key();

	if (iKey == Qt::Key_E || QKeySequence(iKey).toString() == "У") {
		this->setStyleSheet("background: none; border-radius: 9px; border: 0.4px solid #FFFFFF;");
		scrollArea_->hide();

		if (isSaturday_) {
			closeSt();
			isSaturday_ = false;
		}
		else {
			close();
		}

		QGroupBox::keyPressEvent(event);
	}
}

void EmojiHub::chosed(int nEmoji)
{
	if (!isSaturday_) {
		emit changeEmoji(nEmoji);
	}
	else {
		emit changeEmojiSt(nEmoji);
	}
}

void EmojiHub::showThis()
{
	if (isSaturday_) {
		isSaturday_ = false;
		closeSt();
	}

	if (scrollArea_->isHidden()) {
		this->setStyleSheet("background: #FFFFFF; border-radius: 9px; border: 0.4px solid #FFFFFF;");
		scrollArea_->show();
		open();
	}
	else {
		this->setStyleSheet("background: none; border-radius: 9px; border: 0.4px solid #FFFFFF;");
		scrollArea_->hide();
		close();
	}
}

void EmojiHub::showThisSt()
{
	if (isSaturday_) {
		if (!scrollArea_->isHidden()) {
			this->setStyleSheet("background: none; border-radius: 9px; border: 0.4px solid #FFFFFF;");
			scrollArea_->hide();
		}
		isSaturday_ = false;
		closeSt();
	} else {
		if (!scrollArea_->isHidden()) {
			this->setStyleSheet("background: none; border-radius: 9px; border: 0.4px solid #FFFFFF;");
			scrollArea_->hide();
			close();
		}
		else {
			this->setStyleSheet("background: #FFFFFF; border-radius: 9px; border: 0.4px solid #FFFFFF;");
			scrollArea_->show();
			openSt();
			isSaturday_ = true;
		}
	}
}
