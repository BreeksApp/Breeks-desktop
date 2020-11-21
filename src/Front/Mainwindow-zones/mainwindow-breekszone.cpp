#include "Front/mainwindow.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QtConcurrent/QtConcurrent>

void MainWindow::setBreeksZone(breeksZone_t* breeksZone)
{
	const int groupBoxHeight = 100;

  //-----BREEKS ZONE sizes-----
	breeksZone->breeksZoneGroupBox->setFixedWidth(WORK_ZONE_BIG_WIDGET_WIDTH - 36);
  breeksZone->breeksZoneGroupBox->setFixedHeight(groupBoxHeight);
	//breeksZone->breeksZoneGroupBox->setContentsMargins(0, 0, 0, 0);
	breeksZone->breeksZoneGroupBox->setStyleSheet("QGroupBox {background: #F7F7F7; border: 1.5px solid #F1F1F1; border-radius: 20px;}");

	breeksZone->breeksZoneGroupBox->setLayout(breeksZone->breeksZoneLayout);
	breeksZone->breeksZoneLayout->setContentsMargins(100, 0, 100, 0);
  breeksZone->flagIfPosFilled = false;

  for (int i = 0; i < DAYS_COUNT; ++i) {
		breeksZone->arrBreeks[i]->setEnabled(false);
		breeksZone->arrBreeks[i]->setState(false);

		breeksZone->arrBreeksZoneDays[i]->setFixedSize(90, 90);
		breeksZone->arrBreeks[i]->setFixedSize(90, 90);
		breeksZone->arrBreeks[i]->setStyleSheet("background: none;");

		connect(breeksZone->arrBreeks[i], SIGNAL(sendSateToLilDay(int, int, int)), this, SLOT(changeBreeksZoneLilDayState(int, int, int)));
    connect(breeksZone->arrBreeks[i], SIGNAL(moveBreek(int, int, bool)), this, SLOT(moveBreek(int, int, bool)));
		connect(breeksZone->arrBreeks[i], SIGNAL(isHere(int, int, bool)), this, SLOT(setBreeksZoneLilDayShadow(int, int, bool)));
  }

	//-----DESCRIPTION ZONE-----
	breeksZone->breeksDescriptionGroupBox->setFixedSize(300, groupBoxHeight);
	breeksZone->breeksDescriptionGroupBox->setStyleSheet("QGroupBox{background: #F7F7F7; border: 1.5px solid #F1F1F1; border-radius: 15px;}");

	breeksDescriptionZoneScrollArea_->verticalScrollBar()->setStyleSheet(
				"QScrollBar:vertical {"
					"border: 0.1px solid #FFFFFF;"
					"background: #FFFFFF;"
					"width: 9px;"
					"margin: 0px 0px 0px 0px;}"

				"QScrollBar::handle:vertical {"
					"border: 0.5px solid #c7c7bf;"
					"border-radius: 4px;"
					"background: #c7c7bf;"
					"min-height: 0px;}"

				"QScrollBar::add-line:vertical {"
				"border: none;"
				"background: none;}"

				"QScrollBar::sub-line:vartical {"
				"border: none;"
				"background: none;}");


	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(5);
	effect->setXOffset(0);
	effect->setYOffset(0);
	effect->setColor("#BABCBE");

	breeksZone->breekText->setFixedSize(240, 60);
	breeksZone->breekText->setStyleSheet("background: #FFFFFF; border: 0.2px solid #EEEEEE; border-radius: 4px;"
																			 "padding-left: 2; padding-top: 2; padding-bottom: 2; padding-right: 2;");
	QFont font("Helvetica", 12);
	breeksZone->breekText->setFont(font);

	breeksZone->breekText->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
	breeksZone->breekText->verticalScrollBar()->setStyleSheet(
				"QScrollBar:vertical {"
					"border: 0.1px solid #FFFFFF;"
					"background: #FFFFFF;"
					"width: 12px;"
					"margin: 0px 0px 0px 0px;}"

				"QScrollBar::handle:vertical {"
					//"border: 0.5px solid #c7c7bf;"
					"border-radius: 3px;"
					"background: #e3e3df;"
					"min-height: 0px;}"

				"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

				"QScrollBar::sub-line:vartical {"
					"border: none;"
					"background: none;}");

  const int buttonSize = 20;
  breeksZone->buttonBreekDays->setFixedSize(buttonSize, buttonSize);
  breeksZone->buttonDelete->setFixedSize(buttonSize, buttonSize);

	breeksZone->breeksDescriptionLayout->addWidget(breeksZone->breekText, 0, 0, 1, 1);

	//breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonBreekDays, 0, 2);
	//breeksZone->buttonBreekDays->setStyleSheet("border-image:url(:/Images/Front/Images/calendar-and-clock.png)");
	//breeksZone->buttonBreekDays->setStyleSheet("background: none;");

	breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonDelete, 0, 1);
	breeksZone->buttonDelete->setStyleSheet("background: none; border-image:url(:/Images/Front/Images/trash.png)");

  QHBoxLayout *days = new QHBoxLayout;
	days->setContentsMargins(0, 0, 28, 0);

  for (int i = 0; i < DAYS_COUNT; ++i) {
    breeksZone->arrBreeksZoneDays[i]->setFixedSize(25, 20);
		breeksZone->arrBreeksZoneDays[i]->setStyleSheet("background: #FFFFFF; border-radius: 4px;");
		days->addWidget(breeksZone->arrBreeksZoneDays[i], Qt::AlignCenter);
  }
	breeksZone->arrBreeksZoneDays[0]->setText("Пн");
	breeksZone->arrBreeksZoneDays[1]->setText("Вт");
	breeksZone->arrBreeksZoneDays[2]->setText("Ср");
	breeksZone->arrBreeksZoneDays[3]->setText("Чт");
	breeksZone->arrBreeksZoneDays[4]->setText("Пт");
	breeksZone->arrBreeksZoneDays[5]->setText("Сб");

  //
  QPushButton *helper = new QPushButton;
	helper->setFixedSize(15, 20);
  helper->setEnabled(false);
  helper->setFlat(true);
	helper->setStyleSheet("background: none;");
	//days->addWidget(helper);
  //

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(breeksZone->breeksDescriptionLayout);
	mainLayout->addLayout(days);
	mainLayout->setContentsMargins(6, 6, 6, 4);

	breeksZone->breeksDescriptionGroupBox->setContentsMargins(0, 0, 0, 0);
	breeksZone->breeksDescriptionGroupBox->setLayout(mainLayout);
  //

  for (int i = 0; i < 4; ++i) {
    switch (i) {
      case 0 :
        arrEmojiNormal[0] = "";
        break;
      case 1 :
        arrEmojiCompleted[0] = "";
        break;
      case 2 :
        arrEmojiDroped[0] = "";
        break;
      case 3 :
        arrEmojiProcess[0] = "";
    }
  }

  for (int i = 1; i < EMOJI_COUNT; ++i) {
    for (int j = 1; j < 5; ++j) {
      QString sAdress = ":/Images/Front/Images/Breeks/" + QString::number(i) + "." + QString::number(j) + ".png";

      switch (j) {
        case 1 :
          arrEmojiNormal[i] = sAdress;
          break;
        case 2 :
          arrEmojiCompleted[i] = sAdress;
          break;
        case 3 :
          arrEmojiDroped[i] = sAdress;
          break;
        case 4 :
          arrEmojiProcess[i] = sAdress;
          break;
      }
    }
  }
}

void MainWindow::buildBreeksDescriptionZone()
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");
	ui->groupBoxBreeksDescreption->setGraphicsEffect(effect);
	ui->groupBoxBreeksDescreption->setStyleSheet("QGroupBox{background: #FFFFFF; border-radius: 6px;}");


  QHBoxLayout *layOut = new QHBoxLayout;
  ui->groupBoxBreeksDescreption->setLayout(layOut);

	breeksDescriptionZoneScrollArea_->setFixedHeight(ui->groupBoxBreeksDescreption->height() - 20);
  layOut->addWidget(breeksDescriptionZoneScrollArea_);

	bigWidgetInBreeksDescriptionZone_->setFixedSize(ui->groupBoxBreeksDescreption->width() - 30, bigWidgetHeight_);
	bigWidgetInBreeksDescriptionZone_->setContentsMargins(7, 0, 0, 0);
	bigWidgetInBreeksDescriptionZone_->setStyleSheet("QWidget{background: #FFFFFF;}");

	breeksDescriptionZoneScrollArea_->setWidget(bigWidgetInBreeksDescriptionZone_);
	breeksDescriptionZoneScrollArea_->setStyleSheet("background: #FFFFFF; border-radius: 9px;");

	//breeksDescriptionZoneLayout_->setContentsMargins(0, 0, 0, 200);
  bigWidgetInBreeksDescriptionZone_->setLayout(breeksDescriptionZoneLayout_);

//GroupBox to describe posibilities of breeks
	QGroupBox *mfc = new QGroupBox;

	//const int descriptionWidth = 270;
  const int descriptionHeight = 480;

	mfc->setFixedHeight(descriptionHeight);
	mfc->setStyleSheet("QGroupBox{background: #F7F7F7; border-radius: 6px;}");
	breeksDescriptionZoneLayout_->addWidget(mfc, 0, 0, Qt::AlignCenter);
}

void MainWindow::setDaysConnect(breeksZone_t* breeksZone)
{
  for (int i = 0; i < DAYS_COUNT; ++i) {
		connect(breeksZone->arrBreeksZoneDays[i], SIGNAL(singleClick()), breeksZone->arrBreeks[i], SLOT(changeBreekState()));
		connect(breeksZone->arrBreeksZoneDays[i], SIGNAL(doubleClick(int, int)), this, SLOT(descriptionZoneDayDobleClick(int, int)));
  }
}

void MainWindow::allocateMemoryForBreeks(breeksZone_t* breeksZone)
{
  breeksZone->breeksZoneGroupBox = new QGroupBox;
  breeksZone->breeksZoneLayout = new QGridLayout;

  breeksZone->breeksDescriptionGroupBox = new QGroupBox;
  breeksZone->breeksDescriptionLayout = new QGridLayout;

	breeksZone->breekText = new TimetableTextEdit();
  breeksZone->buttonBreekDays = new QPushButton;
  breeksZone->buttonDelete = new QPushButton;

  for (int i = 0; i < DAYS_COUNT; i++) {
    breeksZone->arrBreeks[i] = new Breek;
		breeksZone->arrBreeksZoneDays[i] = new DescriptionZoneDayButton(breeksZone->zoneIndex, i);
  }
}

void MainWindow::fillBreeksPositions(int zoneIndex)
{
  if (zoneIndex < arrBreeksZones_.size() && zoneIndex >= 0) {
    for (auto i : arrBreeksZones_[zoneIndex].arrBreeks) {
      arrBreeksZones_[zoneIndex].positionsOfBreeks.push_back(i->pos());
    }
	}
}

void MainWindow::changeBreeksZoneLilDayState(int zoneIndex, int dayIndex, int iState)
{
	if (dayIndex == iCurrentDay_) {
		return;
	}

	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
	shadow->setBlurRadius(9);
	shadow->setXOffset(0);
	shadow->setYOffset(0);
	shadow->setColor("#81C4FF");

	switch (iState) {
		case 0 :
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setGraphicsEffect(shadow);
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #FFFFFF; border-radius: 4px;");
		break;
		case 1 :
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setGraphicsEffect(nullptr);
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #d0f896; border-radius: 4px;");
		break;
		case 2 :
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setGraphicsEffect(nullptr);
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #ff8696; border-radius: 4px;");
	}
}

void MainWindow::setBreeksZoneLilDayShadow(int zoneIndex, int dayIndex, bool state)
{
	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
	shadow->setBlurRadius(9);
	shadow->setXOffset(0);
	shadow->setYOffset(0);
	shadow->setColor("#81C4FF");

	arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #FFFFFF; border-radius: 4px;");

	if (state) {
		arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setGraphicsEffect(shadow);
		if (dayIndex == iCurrentDay_) {
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #b3defc; border-radius: 4px;");
		}
	}
	else {
		arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setGraphicsEffect(nullptr);
		if (dayIndex == iCurrentDay_) {
			arrBreeksZones_[zoneIndex].arrBreeksZoneDays[dayIndex]->setStyleSheet("background: #FFFFFF; border-radius: 4px;");
		}
	}
}

void MainWindow::setBreeksDescriptionZoneFocus(int zoneIndex, bool cond)
{
	if (cond) {
		QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
		shadow->setBlurRadius(9);
		shadow->setXOffset(0);
		shadow->setYOffset(0);
		shadow->setColor("#909090");

		arrBreeksZones_[zoneIndex].breeksDescriptionGroupBox->setGraphicsEffect(shadow);
	}
	else {
		arrBreeksZones_[zoneIndex].breeksDescriptionGroupBox->setGraphicsEffect(nullptr);
	}
}

void MainWindow::descriptionZoneDayDobleClick(int zoneIndex, int dayIndex)
{
	int sliderPos = workZoneScrollArea_->horizontalScrollBar()->sliderPosition();
	int dayPos = arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->pos().x();

	if (sliderPos < dayPos) {
		workZoneScrollArea_->ensureVisible(dayPos + 530, workZoneScrollArea_->verticalScrollBar()->sliderPosition());
	}
	else {
		workZoneScrollArea_->ensureVisible(dayPos - 405, workZoneScrollArea_->verticalScrollBar()->sliderPosition());
	}

	arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->setFocus();
}

void MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime) {
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		}
}

void MainWindow::moveBreek(int zoneIndex, int dayIndex, bool right)
{
	if (!arrBreeksZones_[zoneIndex].flagIfPosFilled) {
		fillBreeksPositions(zoneIndex);
		arrBreeksZones_[zoneIndex].flagIfPosFilled = true;
	}

	if (right) {

		if (dayIndex < DAYS_COUNT - 1) {
			breeksZone_t *zone = &arrBreeksZones_[zoneIndex];

			if (!zone->arrBreeks[dayIndex + 1]->isEnabled()) {
				Conditions workState = Conditions::GREY_FOREGROUND;
				zone->arrBreeks[dayIndex]->setColorState(workState);
				zone->arrBreeks[dayIndex]->connectToQml(zone->arrBreeks[dayIndex]->getEmojiNum(), workState);

				QRect rectFrom = zone->arrBreeks[dayIndex]->geometry();
				QPoint posFrom = zone->arrBreeks[dayIndex]->pos();
				QPoint posTo = zone->arrBreeks[dayIndex + 1]->pos();

				QPropertyAnimation *animation = new QPropertyAnimation(zone->arrBreeks[dayIndex], "geometry");
				QRect rectTo(posTo.x(), posTo.y(), rectFrom.width(), rectFrom.height());
				animation->setDuration(MOVE_DURATION);
				animation->setStartValue(rectFrom);
				animation->setEndValue(rectTo);

				animation->start();
				delay(MOVE_DURATION + 50);

				zone->arrBreeks[dayIndex]->changeBreekState();

				if (zone->arrBreeks[dayIndex + 1]->getEmojiNum() != zone->arrBreeks[dayIndex]->getEmojiNum()) {
					zone->arrBreeks[dayIndex + 1]->setEmoj(zone->arrBreeks[dayIndex]->getEmojiNum());
					zone->arrBreeks[dayIndex + 1]->connectToQml(zone->arrBreeks[dayIndex + 1]->getEmojiNum(), zone->arrBreeks[dayIndex + 1]->getColorState());
					QThread::msleep(100);
				}

				zone->arrBreeks[dayIndex + 1]->changeBreekState();
				zone->arrBreeks[dayIndex]->move(posFrom);

				QThread::msleep(200);
				descriptionZoneDayDobleClick(zoneIndex, dayIndex + 1);
				//workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex + 1]->pos().x() + 530, workZoneScrollArea_->verticalScrollBar()->sliderPosition());
			}
			zone->arrBreeks[dayIndex + 1]->setFocus();
			return;
		}

	}
	else {
		if (dayIndex > 0) {
			breeksZone_t *zone = &arrBreeksZones_[zoneIndex];
			if (!zone->arrBreeks[dayIndex - 1]->isEnabled()) {
				Conditions workState = Conditions::GREY_FOREGROUND;
				zone->arrBreeks[dayIndex]->setState(workState);
				zone->arrBreeks[dayIndex]->connectToQml(zone->arrBreeks[dayIndex]->getEmojiNum(), workState);

				QRect rectFrom = zone->arrBreeks[dayIndex]->geometry();
				QPoint posFrom = zone->arrBreeks[dayIndex]->pos();
				QPoint posTo = zone->arrBreeks[dayIndex - 1]->pos();

				QPropertyAnimation *animation = new QPropertyAnimation(zone->arrBreeks[dayIndex], "geometry");
				QRect rectTo(posTo.x(), posTo.y(), rectFrom.width(), rectFrom.height());
				animation->setDuration(MOVE_DURATION);
				animation->setStartValue(rectFrom);
				animation->setEndValue(rectTo);

				animation->start();
				delay(MOVE_DURATION + 50);

				zone->arrBreeks[dayIndex]->changeBreekState();

				if (zone->arrBreeks[dayIndex - 1]->getEmojiNum() != zone->arrBreeks[dayIndex]->getEmojiNum()) {
					zone->arrBreeks[dayIndex - 1]->setEmoj(zone->arrBreeks[dayIndex]->getEmojiNum());
					zone->arrBreeks[dayIndex - 1]->connectToQml(zone->arrBreeks[dayIndex - 1]->getEmojiNum(), zone->arrBreeks[dayIndex - 1]->getColorState());
					QThread::msleep(100);
				}
				zone->arrBreeks[dayIndex - 1]->changeBreekState();
				zone->arrBreeks[dayIndex]->move(posFrom);

				QThread::msleep(200);
				descriptionZoneDayDobleClick(zoneIndex, dayIndex - 1);
				//workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex - 1]->pos().x() - 405, workZoneScrollArea_->verticalScrollBar()->sliderPosition());
			}
			zone->arrBreeks[dayIndex - 1]->setFocus();
			return;
		}
	}

	if (dayIndex == iCurrentDay_) {
		arrBreeksZones_[zoneIndex].arrBreeksZoneDays[iCurrentDay_]->setStyleSheet("background: #FFFFFF; border-radius: 4px;");
	}
	if (iCurrentDay_ < DAYS_COUNT & arrBreeksZones_[zoneIndex].arrBreeks[iCurrentDay_]->getState()) {
		arrBreeksZones_[zoneIndex].arrBreeksZoneDays[iCurrentDay_]->setStyleSheet("background: #b3defc; border-radius: 4px;");
	}
}
