#include "mainwindow.h"
#include <QScrollArea>

void MainWindow::buildTimeTable()
{
  bigWidgetInWorkZone_->setFixedSize(WORK_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);

  workZoneScrollArea_->setWidget(bigWidgetInWorkZone_);

  workZoneScrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  bigWidgetInWorkZone_->setLayout(workZoneLayout_);
  workZoneLayout_->setContentsMargins(0, 0, 0, 200);

  allocateMemoryForDays();

  //add groupboxes for days
  const int dayWidth = 300;
  const int dayHeight = 480;
  for (int i = 0; i < DAYS_COUNT; ++i) {
    arrDays_[i].groupBoxDay->setFixedSize(dayWidth, dayHeight);
    workZoneLayout_->addWidget(arrDays_[i].groupBoxDay, 0, i);
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
  if (currentDayOfWeek == "понедельник") {
    iCurrentDay = 0;
  }
  else if (currentDayOfWeek == "вторник") {
    iCurrentDay = 1;
    workZoneScrollArea_->ensureVisible(scrollPosTue, 0);
  }
  else if (currentDayOfWeek == "среда") {
    iCurrentDay = 2;
    workZoneScrollArea_->ensureVisible(scrollPosWed, 0);
  }
  else if (currentDayOfWeek == "четверг") {
    iCurrentDay = 3;
    workZoneScrollArea_->ensureVisible(scrollPosThu, 0);
  }
  else if (currentDayOfWeek == "пятница") {
    iCurrentDay = 4;
    workZoneScrollArea_->ensureVisible(scrollPosFri, 0);
  }
  else if (currentDayOfWeek == "суббота") {
    iCurrentDay = 5;
    workZoneScrollArea_->ensureVisible(scrollPosSat, 0);
  }
  else {
    iCurrentDay = 6;
    workZoneScrollArea_->ensureVisible(scrollPosSat, 0);
  }

  //special data for set info about days in the LOOP BELOW: date, name of the day and font effects
  const QString arrMonthsRu[12] = { "января", "февраля", "марта", "апреля", "майя",
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
    QString nameMonth = tmpDate.toString("MMMM");
    for (int i = 0; i < 12; ++i) {
      if (nameMonth == arrMonthsRu[i]) {
        nameMonth = arrMonthsEng[i];
      }
    }

    //set font for label with day info
    arrDays_[i].labelDate->setFont(font);
    //set font style for elements count label
    for (int i = 0; i < DAYS_COUNT; ++i) {
      arrDays_[i].labelElementsCount->setFont(fontCounter);
      arrDays_[i].labelElementsCount->setStyleSheet("font: italic;");
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
    arrDays_[iCurrentDay].labelDate->setStyleSheet("background-color: #c9eaff;");
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
    arrDays_[i].widgetDay = new QWidget;
    arrDays_[i].helpLayout = new QVBoxLayout;
    arrDays_[i].layoutDayElements = new QVBoxLayout;
  }

  initializeDaysParameters();
}

void MainWindow::initializeDaysParameters()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
    arrDays_[i].groupBoxElementsHeight = 0;
    arrDays_[i].elementsCount = 0;
    arrDays_[i].labelElementsCount->setText("");
  }
}

void MainWindow::setDaysStructure()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
    arrDays_[i].groupBoxDay->setLayout(arrDays_[i].layoutFullDay);

    //day info
    arrDays_[i].layoutFullDay->addLayout(arrDays_[i].layoutDayInfo);
    arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelDate);
    arrDays_[i].layoutDayInfo->addStretch(15);
    arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelElementsCount);

    //scroll area for elements
    arrDays_[i].layoutFullDay->addWidget(arrDays_[i].scrollArea);
    const int dayWidgetScrollAreaWidth = 277;
    const int dayWidgetScrollAreaHeight = 400;
    arrDays_[i].scrollArea->setFixedSize(dayWidgetScrollAreaWidth, dayWidgetScrollAreaHeight);
    arrDays_[i].scrollArea->setStyleSheet("QScrollBar {width: 0px;}");

    //zone for elements
    arrDays_[i].scrollArea->setWidget(arrDays_[i].widgetDay);

    arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight);
    arrDays_[i].widgetDay->setLayout(arrDays_[i].helpLayout);

    arrDays_[i].helpLayout->addLayout(arrDays_[i].layoutDayElements);
    arrDays_[i].layoutDayElements->setContentsMargins(5, 0, 0, 0);
  }
}
