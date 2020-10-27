#include "Front/mainwindow.h"
#include <QScrollArea>

#include <QDebug>

void MainWindow::buildTimeTable()
{
  ui->groupBoxWorkZone->setStyleSheet("background: #F9F9F9; border-radius: 6px;");

  bigWidgetInWorkZone_->setFixedSize(WORK_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);
  bigWidgetInWorkZone_->setStyleSheet("background: #FFFFFF; border-radius: 9px;");

  workZoneScrollArea_->setWidget(bigWidgetInWorkZone_);
  workZoneScrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  workZoneScrollArea_->setStyleSheet("border-radius: 9px;");

  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
  effect->setBlurRadius(10);
  effect->setXOffset(0);
  effect->setYOffset(1);
  effect->setColor("#909090");
  workZoneScrollArea_->setGraphicsEffect(effect);

  bigWidgetInWorkZone_->setLayout(workZoneLayout_);
  workZoneLayout_->setContentsMargins(0, 0, 0, 200); //experience par

  allocateMemoryForDays();

  //add groupboxes for days
  const int dayWidth = 300;
  const int dayHeight = 480;
  for (int i = 0; i < DAYS_COUNT; ++i) {
    arrDays_[i].groupBoxDay->setFixedSize(dayWidth, dayHeight);
    workZoneLayout_->addWidget(arrDays_[i].groupBoxDay, 0, i, Qt::AlignCenter);
  }

  //build a day
  setDaysStructure();
  for (int i = 0; i < DAYS_COUNT; ++i) {
   readElementsDataFromFile(i);
  }
  setDayInfo();
}

void MainWindow::setDayInfo()
{    
  //to auto-set current day in the center of screen
  const int scrollPosTue = 700;
  const int scrollPosWed = 1000;
  const int scrollPosThu = 1300;
  const int scrollPosFri = 1600;
  const int scrollPosSat = 1900;

  QString currentDayOfWeek = QDate::currentDate().toString("dddd"); //dddd gives to us full name of current day of week
  int iCurrentDay = 0;

  //identify current day of week
  if (currentDayOfWeek == "Monday") {
    iCurrentDay = 0;
  }
  else if (currentDayOfWeek == "Tuesday") {
    iCurrentDay = 1;
    workZoneScrollArea_->ensureVisible(scrollPosTue, 0);
  }
  else if (currentDayOfWeek == "Wednesday") {
    iCurrentDay = 2;
    workZoneScrollArea_->ensureVisible(scrollPosWed, 0);
  }
  else if (currentDayOfWeek == "Thursday") {
    iCurrentDay = 3;
    workZoneScrollArea_->ensureVisible(scrollPosThu, 0);
  }
  else if (currentDayOfWeek == "Friday") {
    iCurrentDay = 4;
    workZoneScrollArea_->ensureVisible(scrollPosFri, 0);
  }
  else if (currentDayOfWeek == "Saturday") {
    iCurrentDay = 5;
    workZoneScrollArea_->ensureVisible(scrollPosSat, 0);
  }
  else {
    iCurrentDay = 6;
    workZoneScrollArea_->ensureVisible(scrollPosSat, 0);
  }

  //special data for set info about days in the LOOP BELOW: date, name of the day and font effects
  const QString arrMonthsRu[12] = { "января", "февраля", "марта", "апреля", "мая",
        "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
  const QString arrMonthsEng[12] = { "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October", "November", "December" };

  const QString daysNames[6] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  QDate date = QDate::currentDate();
  QDate tmpDate = date;

  QFont font("Helvetica", 14);
  QFont fontCounter("Helvetica", 12);
  //-------

  for (int i = 0; i < DAYS_COUNT; ++i) {
    //identify current month
    QString nameMonth = "May";//tmpDate.toString("MMMM");
//    for (int i = 0; i < 12; ++i) {
//      if (nameMonth == arrMonthsRu[i]) {
//        nameMonth = arrMonthsEng[i];
//      }
//      qDebug() << nameMonth;
//    }

    //set font for label with day info
    arrDays_[i].labelDate->setFont(font);
    //set font style for elements count label
    for (int i = 0; i < DAYS_COUNT; ++i) {
      arrDays_[i].labelElementsCount->setFont(fontCounter);
      arrDays_[i].labelElementsCount->setStyleSheet("background: none; color: #000000; font: italic;");
    }

    //work with HTML to set style for a part of line
    QString strHTML = "<b>" + daysNames[i] + "</b>";
    QByteArray encoding = strHTML.toUtf8();
    const char *charHTML= encoding.data();

    //set current date
    QString currentDate = "";
    if (i != iCurrentDay) {
      tmpDate = date.addDays(i - iCurrentDay);
      currentDate = ", " + nameMonth + " " + tmpDate.toString("d");
    }
    else {
      currentDate = ", " + nameMonth + " " + date.toString("d");
    }
    arrDays_[i].labelDate->setText(tr(charHTML) + currentDate);
  }

  //set effects to underline current day
  if (iCurrentDay != 6) {
    effects::setElementShadow(arrDays_[iCurrentDay].labelDate, 10);
  }
}

void MainWindow::allocateMemoryForDays()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
    arrDays_[i].groupBoxDay = new QGroupBox;
    arrDays_[i].layoutFullDay = new QVBoxLayout;

    arrDays_[i].layoutDayInfo = new QHBoxLayout;
    arrDays_[i].labelDate = new QLabel;
    arrDays_[i].labelElementsCount = new QLabel;

    arrDays_[i].scrollArea = new QScrollArea;
    arrDays_[i].widgetDay = new DayWidget;
    arrDays_[i].widgetDay->setDayNumber(i);

    arrDays_[i].helpLayout = new QVBoxLayout;
    arrDays_[i].layoutDayElements = new QVBoxLayout;

    connect(arrDays_[i].widgetDay, SIGNAL(dropElement(const int, const int, const int, const elementData_t)),
            this, SLOT(dropElement(const int, const int, const int, const elementData_t)));

    connect(arrDays_[i].widgetDay, SIGNAL(sendDayAndElementIndex(const int, const int)),
            this, SLOT(recieveDayAndElementIndex(const int, const int)));

    connect(arrDays_[i].widgetDay, SIGNAL(sendElementsHeight(const int, const int)), this, SLOT(sendElementsHeight(const int, const int)));
  }

  initializeDaysParameters();
}

void MainWindow::initializeDaysParameters()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
    arrDays_[i].groupBoxElementsHeight = 395;
    arrDays_[i].elementsCount = 0;
    arrDays_[i].labelElementsCount->setText("");
  }
}

void MainWindow::setDaysStructure()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
    arrDays_[i].groupBoxDay->setStyleSheet("QGroupBox {background: #F9F9F9; border: 0.4px solid #E3E3E3 ;border-radius: 9px;}");
    arrDays_[i].groupBoxDay->setLayout(arrDays_[i].layoutFullDay);

    //day info
    arrDays_[i].layoutFullDay->addLayout(arrDays_[i].layoutDayInfo);
    arrDays_[i].labelDate->setStyleSheet("background: none; color: #000000;");
    arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelDate);

    arrDays_[i].layoutDayInfo->addStretch(15);
    arrDays_[i].labelElementsCount->setStyleSheet(""); //DON'T WORK
    arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelElementsCount);

    //scroll area for elements
    arrDays_[i].layoutFullDay->addWidget(arrDays_[i].scrollArea, Qt::AlignCenter);
    //const int dayWidgetScrollAreaWidth = 277;
    const int dayWidgetScrollAreaHeight = 400;
    arrDays_[i].scrollArea->setFixedHeight(dayWidgetScrollAreaHeight);

    arrDays_[i].scrollArea->setStyleSheet("QScrollArea {background: #FFFFFF; border: 0.4px solid #E3E3E3; border-radius: 6px; width: 0px;}");
    arrDays_[i].scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setXOffset(0);
    effect->setYOffset(1);
    effect->setColor("#909090");
    arrDays_[i].scrollArea->setGraphicsEffect(effect);

    //zone for elements
    arrDays_[i].scrollArea->setWidget(arrDays_[i].widgetDay);
    arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight);
    arrDays_[i].widgetDay->setLayout(arrDays_[i].helpLayout);

    arrDays_[i].helpLayout->addLayout(arrDays_[i].layoutDayElements);
    arrDays_[i].layoutDayElements->setContentsMargins(6, 0, 0, 0); //i don't know why, but it's badly needed
  }
}
