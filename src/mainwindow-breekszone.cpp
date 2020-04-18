#include "mainwindow.h"
#include <QScrollArea>

void MainWindow::setBreeksZone(breeksZone_t* breeksZone)
{
  const int groupBoxHeight = 120;

  //-----BREEKS ZONE sizes-----
  breeksZone->breeksZoneGroupBox->setFixedHeight(groupBoxHeight);
  breeksZone->breeksZoneLayout->setHorizontalSpacing(160);
  breeksZone->breeksZoneGroupBox->setLayout(breeksZone->breeksZoneLayout);
  breeksZone->flagIfPosFilled = false;

  for (int i = 0; i < DAYS_COUNT; ++i) {
    breeksZone->arrBreeks[i]->setEnabled(false);
    breeksZone->arrBreeks[i]->setState(false);

    connect(breeksZone->arrBreeks[i], SIGNAL(moveBreek(int, int, bool)), this, SLOT(moveBreek(int, int, bool)));
  }

  //-----DeSCRIPTION ZONE-----
  breeksZone->breeksDescriptionGroupBox->setFixedSize(270, groupBoxHeight);

  breeksZone->breekText->setFixedSize(220, 50);

  const int buttonSize = 20;
  breeksZone->buttonBreekDays->setFixedSize(buttonSize, buttonSize);
  breeksZone->buttonDelete->setFixedSize(buttonSize, buttonSize);

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->breekText, 0, 0, 1, 1);
  QFont font("Helvetica", 12);
  breeksZone->breekText->setFont(font);

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonBreekDays, 0, 2);
  breeksZone->buttonBreekDays->setStyleSheet("border-image:url(:/Images/Images/calendar-and-clock.png)");
  //connect(breeksZone->buttonBreekDays, SIGNAL(clicked()), , SLOT())

  breeksZone->breeksDescriptionLayout->addWidget(breeksZone->buttonDelete, 1, 2);
  breeksZone->buttonDelete->setStyleSheet("border-image:url(:/Images/Images/recycle-bin.png)");

  QHBoxLayout *days = new QHBoxLayout;
  days->setContentsMargins(0, 0, 0, 0);

  for (int i = 0; i < DAYS_COUNT; ++i) {
    breeksZone->arrBreeksZoneDays[i]->setFixedSize(25, 20);
    //breeksZone->arrBreeksZoneDays[i]->setEnabled(false);
    //breeksZone->arrBreeksZoneDays[i]->setFlat(true);

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

  QVBoxLayout *main = new QVBoxLayout;
  main->addLayout(breeksZone->breeksDescriptionLayout);
  main->addLayout(days);
  main->setContentsMargins(10, 13, 10, 10);

  breeksZone->breeksDescriptionGroupBox->setLayout(main);
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
      QString sAdress = ":/Images/Images/Breeks/" + QString::number(i) + "." + QString::number(j) + ".png";

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
  QHBoxLayout *layOut = new QHBoxLayout;
  ui->groupBoxBreeksDescreption->setLayout(layOut);

  const int scrollAreaWidth = 323;
  const int scrollAreaHeight = 950;

  breeksDescriptionZoneScrollArea_->setFixedSize(scrollAreaWidth, scrollAreaHeight);
  layOut->addWidget(breeksDescriptionZoneScrollArea_);

  bigWidgetInBreeksDescriptionZone_->setFixedSize(BREEKS_DESCRIPTION_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);

  breeksDescriptionZoneScrollArea_->setWidget(bigWidgetInBreeksDescriptionZone_);

  breeksDescriptionZoneLayout_->setContentsMargins(0, 0, 0, 200);
  bigWidgetInBreeksDescriptionZone_->setLayout(breeksDescriptionZoneLayout_);

//GroupBox to describe posibilities of breeks
  QGroupBox *description = new QGroupBox;

  const int descriptionWidth = 270;
  const int descriptionHeight = 480;

  description->setFixedSize(descriptionWidth, descriptionHeight);
  breeksDescriptionZoneLayout_->addWidget(description, 0, 0);
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

/*void MainWindow::setEmoji(const QString emoji)
{
  QPixmap pix(emoji);
  pix = pix.scaledToWidth(arrBreeksZones_. width(), Qt::SmoothTransformation);
  QIcon buttonIcon(pix);
  newZone.arrBreeks[i]->setIcon(buttonIcon);
  newZone.arrBreeks[i]->setIconSize(pix.rect().size());
}*/


