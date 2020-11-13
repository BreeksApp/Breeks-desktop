#include "Front/mainwindow.h"
#include <QScrollArea>
#include <QScrollBar>

#include <QDebug>

void MainWindow::buildTimeTable()
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBoxWorkZone->setGraphicsEffect(effect);
	ui->groupBoxWorkZone->setStyleSheet("background: #FFFFFF; border-radius: 6px;");

	bigWidgetInWorkZone_->setFixedSize(WORK_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);
	bigWidgetInWorkZone_->setStyleSheet("background: #FFFFFF; border-radius: 9px;");

  workZoneScrollArea_->setWidget(bigWidgetInWorkZone_);
  workZoneScrollArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	workZoneScrollArea_->setStyleSheet("border-radius: 9px;");

  bigWidgetInWorkZone_->setLayout(workZoneLayout_);
	//workZoneLayout_->setContentsMargins(0, 0, 0, 200); //experience par

  allocateMemoryForDays();

  //add groupboxes for days
	const int dayWidth = 305;
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

	timer_ = new QTimer();
	timer_->setSingleShot(true);
	connect(timer_, SIGNAL(timeout()), this, SLOT(setDayInfo()));
	iCurrentDay_ = 0;

	setDayInfo();

	isElementDrag_ = false;
}

void MainWindow::setDayInfo()
{
	arrDays_[iCurrentDay_].scrollArea->verticalScrollBar()->setStyleSheet(
				"QScrollBar:vertical {"
					"border: 0.1px solid #FFFFFF;"
					"background: #FFFFFF;"
					"width: 16px;    "
					"margin: 0px 0px 0px 0px;}"

				"QScrollBar::handle:vertical {"
					"border: 0.5px solid #E3E3E3;"
					"border-radius: 4px;"
					"background: #FCFCFC;"
					"min-height: 0px;}"

				"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

				"QScrollBar::sub-line:vartical {"
					"border: none;"
					"background: none;}");

	QDate date = QDate::currentDate();

  //to auto-set current day in the center of screen
  const int scrollPosTue = 700;
  const int scrollPosWed = 1000;
  const int scrollPosThu = 1300;
  const int scrollPosFri = 1600;
	const int scrollPosSat = bigWidgetInWorkZone_->width();
	//const int scrollPosSun = workZoneScrollArea_->width();

	//identify current day of week
	iCurrentDay_ = date.dayOfWeek() - 1;

	if (iCurrentDay_ < DAYS_COUNT) {
		arrDays_[iCurrentDay_].scrollArea->verticalScrollBar()->setStyleSheet(
					"QScrollBar:vertical {"
						"border: 0.1px solid #FFFFFF;"
						"background: #FFFFFF;"
						"width: 16px;    "
						"margin: 0px 0px 0px 0px;}"

					"QScrollBar::handle:vertical {"
						"border: 0.5px solid #b3defc;"
						"border-radius: 4px;"
						"background: #b3defc;"
						"min-height: 0px;}"

					"QScrollBar::add-line:vertical {"
						"border: none;"
						"background: none;}"

					"QScrollBar::sub-line:vartical {"
						"border: none;"
						"background: none;}");
	}

	switch (iCurrentDay_) {
		case 1 :
			workZoneScrollArea_->ensureVisible(scrollPosTue, 0);
		break;
		case 2 :
			workZoneScrollArea_->ensureVisible(scrollPosWed, 0);
		break;
		case 3 :
			workZoneScrollArea_->ensureVisible(scrollPosThu, 0);
		break;
		case 4 :
			workZoneScrollArea_->ensureVisible(scrollPosFri, 0);
		break;

		default :
			workZoneScrollArea_->ensureVisible(scrollPosSat, 0);
	}

  //special data for set info about days in the LOOP BELOW: date, name of the day and font effects
  const QString arrMonthsRu[12] = { "января", "февраля", "марта", "апреля", "мая",
        "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
  const QString arrMonthsEng[12] = { "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October", "November", "December" };

	const QString daysNamesRu[7] = {"Понедельник", "Вторник", "Среда",
																	"Четверг", "Пятница", "Суббота", "Воскресенье"};
	const QString daysNamesEng[7] = {"Monday", "Tuesday", "Wednesday",
																	 "Thursday", "Friday", "Saturday", "Sunday"};

	QDate tmpDate = date;

	QFont font("Helvetica", 12);
	QFont fontCounter("Helvetica", 11);
  //-------
	for (int i = 0; i < DAYS_COUNT; ++i) {
		//identify month of day
		tmpDate = date.addDays(i - iCurrentDay_);
		QString nameMonth = tmpDate.toString("MMMM");

    //set font for label with day info
    arrDays_[i].labelDate->setFont(font);
    //set font style for elements count label
    for (int i = 0; i < DAYS_COUNT; ++i) {
      arrDays_[i].labelElementsCount->setFont(fontCounter);
			arrDays_[i].labelElementsCount->setStyleSheet("background: none; color: #000000; "
																										"font: italic;");
    }

    //work with HTML to set style for a part of line
		QString strHTML = "<b>" + daysNamesRu[i] + "</b>";
    QByteArray encoding = strHTML.toUtf8();
    const char *charHTML= encoding.data();

    //set current date
		QString sCurrentDate = "";
		sCurrentDate = ", " + nameMonth + " " + tmpDate.toString("d");
		if (i != iCurrentDay_) {
			arrDays_[i].labelDate->setText(tr(charHTML) + sCurrentDate);
		}
		else {
			arrDays_[i].labelDate->setText(QString(tr(charHTML)).toUpper() + sCurrentDate);
		}
  }

	int iTime = QDateTime::currentDateTime().msecsTo(
				QDateTime::currentDateTime().date().startOfDay().addDays(1));
	timer_->start(iTime);
	//qDebug() << iTime;
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

		connect(arrDays_[i].widgetDay, SIGNAL(sendElementsHeight(const int, const int)),
						this, SLOT(sendElementsHeight(const int, const int)));
		connect(arrDays_[i].widgetDay, SIGNAL(moveElement()), this, SLOT(mousePressedByDragElement()));

		connect(arrDays_[i].widgetDay, SIGNAL(elementEnterArea(int)), this, SLOT(enterDayArea(int)));
		connect(arrDays_[i].widgetDay, SIGNAL(elementLeaveArea(int)), this, SLOT(leaveDayArea(int)));
  }

  initializeDaysParameters();
}

void MainWindow::initializeDaysParameters()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
		arrDays_[i].groupBoxElementsHeight = 370;
    arrDays_[i].elementsCount = 0;
		arrDays_[i].elementsScaledCount = 0;
    arrDays_[i].labelElementsCount->setText("");
  }
}

void MainWindow::setDaysStructure()
{
  for (int i = 0; i < DAYS_COUNT; i++) {
		arrDays_[i].groupBoxDay->setStyleSheet("QGroupBox {background: #F7F7F7; border: 1.5px solid #F9F9F9 ;border-radius: 20px;}");
    arrDays_[i].groupBoxDay->setLayout(arrDays_[i].layoutFullDay);

		arrDays_[i].layoutFullDay->setContentsMargins(10, 10, 10, 30);

    //day info
    arrDays_[i].layoutFullDay->addLayout(arrDays_[i].layoutDayInfo);
    arrDays_[i].labelDate->setStyleSheet("background: none; color: #000000;");
    arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelDate);

		arrDays_[i].layoutDayInfo->addStretch(11);
		arrDays_[i].layoutDayInfo->addWidget(arrDays_[i].labelElementsCount, Qt::AlignRight);

    //scroll area for elements
		arrDays_[i].layoutFullDay->addWidget(arrDays_[i].scrollArea);
		//const int dayWidgetScrollAreaWidth = 277;
		const int dayWidgetScrollAreaHeight = 370;
		arrDays_[i].scrollArea->setFixedHeight(dayWidgetScrollAreaHeight);

		arrDays_[i].scrollArea->setStyleSheet("QScrollArea {background: #FFFFFF; border: 0.4px solid #E3E3E3; border-radius: 9px;}");

		arrDays_[i].scrollArea->verticalScrollBar()->setStyleSheet(
					"QScrollBar:vertical {"
						"border: 0.1px solid #FFFFFF;"
						"background: #FFFFFF;"
						"width: 16px;"
						"margin: 0px 0px 0px 0px;}"

					"QScrollBar::handle:vertical {"
						"border: 0.5px solid #E3E3E3;"
						"border-radius: 4px;"
						"background: #FCFCFC;"
						"min-height: 0px;}"

					"QScrollBar::add-line:vertical {"
						"border: none;"
						"background: none;}"

					"QScrollBar::sub-line:vartical {"
						"border: none;"
						"background: none;}");

		arrDays_[i].scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		arrDays_[i].scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		oldStyle_ = "";

		QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
		effect->setBlurRadius(7);
    effect->setXOffset(0);
    effect->setYOffset(1);
    effect->setColor("#909090");
		arrDays_[i].scrollArea->setGraphicsEffect(effect);

		//zone for elements
		arrDays_[i].scrollArea->setWidgetResizable(true);
    arrDays_[i].scrollArea->setWidget(arrDays_[i].widgetDay);
		arrDays_[i].widgetDay->setFixedHeight(arrDays_[i].groupBoxElementsHeight);
		arrDays_[i].widgetDay->setLayout(arrDays_[i].helpLayout);

		arrDays_[i].helpLayout->addLayout(arrDays_[i].layoutDayElements, Qt::AlignCenter);
		arrDays_[i].layoutDayElements->setContentsMargins(3, 10, 0, 10); //i don't know why, but it's badly needed
		arrDays_[i].layoutDayElements->setSpacing(15);
	}
}

void MainWindow::enterDayArea(int index)
{
	arrDays_[index].scrollArea->graphicsEffect()->setEnabled(false);
	if (index != iCurrentDay_) {
		arrDays_[index].scrollArea->setStyleSheet("QScrollArea {background: #f8feee; border-radius: 9px;}");
	}
	else {
		arrDays_[iCurrentDay_].scrollArea->setStyleSheet("QScrollArea {background: #e7f4fe; border-radius: 9px;}");
	}
}

void MainWindow::leaveDayArea(int index)
{
	arrDays_[index].scrollArea->graphicsEffect()->setEnabled(true);
	arrDays_[index].scrollArea->setStyleSheet("border-radius: 9px;");
}

void MainWindow::defineDayMoveFrom(int dayIndex, QString sColor) {
	if (oldStyle_ == "") {
		oldStyle_ = arrDays_[dayIndex].scrollArea->verticalScrollBar()->styleSheet();
		arrDays_[dayIndex].scrollArea->verticalScrollBar()->setStyleSheet(
					"QScrollBar:vertical {"
						"border: 0.1px solid #FFFFFF;"
						"background: #FFFFFF;"
						"width: 16px;"
						"margin: 0px 0px 0px 0px;}"

					"QScrollBar::handle:vertical {"
						"border: 0.5px solid #E3E3E3;"
						"border-radius: 4px;"
						"background: #" + sColor + ";"
						"min-height: 0px;}"

					"QScrollBar::add-line:vertical {"
					"border: none;"
					"background: none;}"

					"QScrollBar::sub-line:vartical {"
					"border: none;"
					"background: none;}");
	}
	else {
		arrDays_[dayIndex].scrollArea->verticalScrollBar()->setStyleSheet(oldStyle_);
		oldStyle_ = "";
	}
}

void MainWindow::changeElementsLayoutHeight(const int dayIndex, const int diffHeight)
{
	if (diffHeight > 0) {
		arrDays_[dayIndex].elementsScaledCount++;
	}
	else {
		arrDays_[dayIndex].elementsScaledCount--;
	}

	if (arrDays_[dayIndex].elementsCount > 2) {
		arrDays_[dayIndex].groupBoxElementsHeight = ELEMENT_HEIGHT_ * (arrDays_[dayIndex].elementsCount - arrDays_[dayIndex].elementsScaledCount)
					+ (ELEMENT_HEIGHT_ + 46) * arrDays_[dayIndex].elementsScaledCount + 25;
	}
	else {
		arrDays_[dayIndex].groupBoxElementsHeight = 370;
	}
	arrDays_[dayIndex].widgetDay->setFixedHeight(arrDays_[dayIndex].groupBoxElementsHeight);
}
