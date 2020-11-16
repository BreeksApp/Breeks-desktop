#include "Front/mainwindow.h"
#include <QScrollArea>

void MainWindow::setBreeksZone(breeksZone_t* breeksZone)
{
	const int groupBoxHeight = 100;

  //-----BREEKS ZONE sizes-----
	breeksZone->breeksZoneGroupBox->setFixedWidth(WORK_ZONE_BIG_WIDGET_WIDTH - 36);
  breeksZone->breeksZoneGroupBox->setFixedHeight(groupBoxHeight);
	//breeksZone->breeksZoneGroupBox->setContentsMargins(0, 0, 0, 0);
	breeksZone->breeksZoneGroupBox->setStyleSheet("QGroupBox {background: #F7F7F7; border: 1.5px solid #F1F1F1; border-radius: 20px;}");
  breeksZone->breeksZoneLayout->setHorizontalSpacing(160);
  breeksZone->breeksZoneGroupBox->setLayout(breeksZone->breeksZoneLayout);
	breeksZone->breeksZoneLayout->setMargin(0);
  breeksZone->flagIfPosFilled = false;

  for (int i = 0; i < DAYS_COUNT; ++i) {
		breeksZone->arrBreeks[i]->setEnabled(false);
		breeksZone->arrBreeks[i]->setState(false);
		breeksZone->arrBreeks[i]->setStyleSheet("background: #111111;");

		breeksZone->arrBreeksZoneDays[i]->setFixedSize(90, 90);
		breeksZone->arrBreeks[i]->setFixedSize(90, 90);

    connect(breeksZone->arrBreeks[i], SIGNAL(moveBreek(int, int, bool)), this, SLOT(moveBreek(int, int, bool)));
  }

	//-----DESCRIPTION ZONE-----
  breeksZone->breeksDescriptionGroupBox->setFixedSize(270, groupBoxHeight);

  breeksZone->breekText->setFixedSize(220, 50);

  const int buttonSize = 20;
  breeksZone->buttonBreekDays->setFixedSize(buttonSize, buttonSize);
  breeksZone->buttonDelete->setFixedSize(buttonSize, buttonSize);

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->breekText, 0, 0, 1, 1);
  QFont font("Helvetica", 12);
  breeksZone->breekText->setFont(font);

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonBreekDays, 0, 2);
  breeksZone->buttonBreekDays->setStyleSheet("border-image:url(:/Images/Front/Images/calendar-and-clock.png)");

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonDelete, 1, 2);
  breeksZone->buttonDelete->setStyleSheet("border-image:url(:/Images/Front/Images/recycle-bin.png)");

  QHBoxLayout *days = new QHBoxLayout;
  days->setContentsMargins(0, 0, 0, 0);

  for (int i = 0; i < DAYS_COUNT; ++i) {
    breeksZone->arrBreeksZoneDays[i]->setFixedSize(25, 20);
    days->addWidget(breeksZone->arrBreeksZoneDays[i]);
  }
  breeksZone->arrBreeksZoneDays[0]->setText("Mn");
  breeksZone->arrBreeksZoneDays[1]->setText("Tu");
  breeksZone->arrBreeksZoneDays[2]->setText("Wd");
  breeksZone->arrBreeksZoneDays[3]->setText("Th");
  breeksZone->arrBreeksZoneDays[4]->setText("Fr");
  breeksZone->arrBreeksZoneDays[5]->setText("Sa");

  //
  QPushButton *helper = new QPushButton;
  helper->setFixedSize(5, 20);
  helper->setEnabled(false);
  helper->setFlat(true);
  days->addWidget(helper);
  //

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(breeksZone->breeksDescriptionLayout);
	mainLayout->addLayout(days);
	//mainLayout->setContentsMargins(10, 13, 10, 10);

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
	ui->groupBoxBreeksDescreption->setStyleSheet("QGroupBox{background: #FFFFFF; border-radius: 6px;}a");

  QHBoxLayout *layOut = new QHBoxLayout;
  ui->groupBoxBreeksDescreption->setLayout(layOut);

	//const int scrollAreaWidth = 323;
	//const int scrollAreaHeight = 950;

	breeksDescriptionZoneScrollArea_->setFixedHeight(ui->groupBoxBreeksDescreption->height() - 20);
  layOut->addWidget(breeksDescriptionZoneScrollArea_);

	bigWidgetInBreeksDescriptionZone_->setFixedSize(ui->groupBoxBreeksDescreption->width() - 20, bigWidgetHeight_);
	breeksDescriptionZoneScrollArea_->setWidget(bigWidgetInBreeksDescriptionZone_);
	breeksDescriptionZoneScrollArea_->setStyleSheet("border-radius: 9px;");

	//breeksDescriptionZoneLayout_->setContentsMargins(0, 0, 0, 200);
  bigWidgetInBreeksDescriptionZone_->setLayout(breeksDescriptionZoneLayout_);

//GroupBox to describe posibilities of breeks
  QGroupBox *description = new QGroupBox;

	//const int descriptionWidth = 270;
  const int descriptionHeight = 480;

	description->setFixedHeight(descriptionHeight);
	breeksDescriptionZoneLayout_->addWidget(description, 0, 0, Qt::AlignCenter);
}

void MainWindow::setDaysConnect(breeksZone_t* breeksZone)
{
  //connect(breeksZone->buttonBreekDays, SIGNAL(clicked()), breeksZone, SLOT(workWithBreekDays()));
  for (int i = 0; i < DAYS_COUNT; ++i) {
    connect(breeksZone->arrBreeksZoneDays[i], SIGNAL(clicked()), breeksZone->arrBreeks[i], SLOT(changeBreekState()));
  }
}

void MainWindow::allocateMemoryForBreeks(breeksZone_t* breeksZone)
{
  breeksZone->breeksZoneGroupBox = new QGroupBox;
  breeksZone->breeksZoneLayout = new QGridLayout;

  breeksZone->breeksDescriptionGroupBox = new QGroupBox;
  breeksZone->breeksDescriptionLayout = new QGridLayout;

  breeksZone->breekText = new TextNewElement;
  breeksZone->buttonBreekDays = new QPushButton;
  breeksZone->buttonDelete = new QPushButton;

  for (int i = 0; i < DAYS_COUNT; i++) {
    breeksZone->arrBreeks[i] = new Breek;
    breeksZone->arrBreeksZoneDays[i] = new QPushButton;
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

void MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime) {
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


