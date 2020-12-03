#include "demobreek.h"
#include <QKeyEvent>
#include <QQmlProperty>
#include <QQuickItem>
#include <QtConcurrent/QtConcurrent>

DemoBreek::DemoBreek(QWidget *parent) :
	QPushButton(parent),
	nEmoji_(0),
	workState_(Conditions::GREY_FOREGROUND),
	quickWidget_(nullptr),
	graphObject_(nullptr),
	width_(110),
	height_(110)
{
	connectToQml(nEmoji_, workState_);
}

void DemoBreek::keyPressEvent(QKeyEvent *event)
{
	int iKey = event->key();

	if (event->modifiers() == 0 && !isAnimated_) {
			if (iKey == Qt::Key_W || QKeySequence(iKey).toString() == "Ц") {
				isAnimated_ = true;

				if (workState_ == Conditions::RED) {
					connectToQml(nEmoji_, Directions::UPSIDE, workState_, Conditions::GREY_BACKGROUND);
					workState_ = Conditions::GREY_BACKGROUND;
				}
				else if (workState_ == Conditions::GREY_FOREGROUND) {
					connectToQml(nEmoji_, Directions::UPSIDE, workState_, Conditions::RED);
					workState_ = Conditions::RED;
				}
				else if (workState_ == Conditions::GREEN) {
					connectToQml(nEmoji_, Directions::UPSIDE, workState_, Conditions::GREY_FOREGROUND);
					workState_ = Conditions::GREY_FOREGROUND;
				}
				else {
					connectToQml(nEmoji_, Directions::UPSIDE, workState_, Conditions::GREEN);
					workState_ = Conditions::GREEN;
				}

				QFuture<void> future = QtConcurrent::run(this, &DemoBreek::waitAnimationEnd);
			}

			if (iKey == Qt::Key_S || QKeySequence(iKey).toString() == "Ы") {
				isAnimated_ = true;

				if (workState_ == Conditions::RED) {
					connectToQml(nEmoji_, Directions::DOWNSIDE, workState_, Conditions::GREY_FOREGROUND);
					workState_ = Conditions::GREY_FOREGROUND;
				}
				else if (workState_ == Conditions::GREY_FOREGROUND) {
					connectToQml(nEmoji_, Directions::DOWNSIDE, workState_, Conditions::GREEN);
					workState_ = Conditions::GREEN;
				}
				else if (workState_ == Conditions::GREEN){
					connectToQml(nEmoji_, Directions::DOWNSIDE, workState_, Conditions::GREY_BACKGROUND);
					workState_ = Conditions::GREY_BACKGROUND;
				}
				else {
					connectToQml(nEmoji_, Directions::DOWNSIDE, workState_, Conditions::RED);
					workState_ = Conditions::RED;
				}

				QFuture<void> future = QtConcurrent::run(this, &DemoBreek::waitAnimationEnd);
			}
	}
}

void DemoBreek::mousePressEvent(QMouseEvent *event)
{
	this->setFocus();
}

void DemoBreek::focusInEvent(QFocusEvent *)
{
	connectToQml(Conditions::SHADOW, true);
}

void DemoBreek::focusOutEvent(QFocusEvent *)
{
	connectToQml(Conditions::SHADOW, false);
}

void DemoBreek::connectToQml(int indexOfEmoji, Conditions cond)
{
	//if (indexOfEmoji < 0 || indexOfEmoji > 68) return;

	// код, связывающий кнопку с qml
	if (quickWidget_ == nullptr) {
		quickWidget_ = new QQuickWidget(QUrl("qrc:/qml/Front/Qml/qml_for_breeks.qml"), this);
		quickWidget_->setResizeMode(QQuickWidget::SizeRootObjectToView);
		quickWidget_->setFixedSize(1.125 *width_, 1.125 * height_);
		graphObject_ = quickWidget_->rootObject();
	}

	if (!quickWidget_->isVisible()) quickWidget_->setVisible(true);

	graphObject_->setProperty("indexOfEmoji", indexOfEmoji);
	QQmlProperty(graphObject_, "animationOn").write(false);
	graphObject_->setProperty("indexOfCondFrom", cond);
	graphObject_->setProperty("indexOfCondTo", cond);
	graphObject_->setProperty("size1", width_);
	graphObject_->setProperty("size2", height_);

	// работа с фоном сцены
	QColor color;
	color.setNamedColor("#e8f7cd");
	quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
	// конец кода, связывающего кнопку с qml
}

void DemoBreek::connectToQml(Conditions cond, bool isShadow)
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

	graphObject_->setProperty("size1", width_);
	graphObject_->setProperty("size2", height_);

	// работа с фоном сцены
	QColor color;
	color.setNamedColor("#e8f7cd");
	quickWidget_->quickWindow()->setColor(color);
}

void DemoBreek::connectToQml(int indexOfEmoji, Directions dir,
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
	graphObject_->setProperty("size1", width_);
	graphObject_->setProperty("size2", height_);

	// работа с фоном сцены
//  QColor color = Qt::GlobalColor::gray;
//  quickWidget_->quickWindow()->setColor(color);

//  QWidget *container = QWidget::createWindowContainer(&quickWidget_, this);
	// конец кода, связывающего кнопку с qml
}

int DemoBreek::getEmojiIndex()
{
	return nEmoji_;
}

void DemoBreek::changeEmoji(int nEmoji)
{
	nEmoji_ = nEmoji;
	connectToQml(nEmoji_, workState_);
	this->setFocus();
}

void DemoBreek::waitAnimationEnd()
{
	QThread::msleep(500);
	isAnimated_ = false;
}
