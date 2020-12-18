#include "ui_mainwindow.h"
#include "Front/mainwindow.h"

void MainWindow::setInfoButtonsStyle()
{
	arrTags_[0].condition = true;
	arrTags_[0].sColor = tag::ARR_COLORS[0];
	infoButtonColorNum = 0;

	for (int i = 1; i < TAGS_COUNT; ++i) {
		arrTags_[i].condition = false;
		arrTags_[i].sColor = tag::ARR_COLORS[i];
	}

	ui->infoButton->setStyleSheet("QPushButton {background: " + arrTags_[0].sColor + "; border-radius: 8px;}");

	connect(ui->infoGb, SIGNAL(enter()), this, SLOT(infoGBEnter()));
	connect(ui->infoGb, SIGNAL(leave()), this, SLOT(infoGBLeave()));
}

void MainWindow::on_infoButton_clicked()
{
	for (int i = 0; i < TAGS_COUNT; ++i) {
		if (arrTags_[i].condition == true) {
			setInfoButtonColor(arrTags_[(i + 1) % TAGS_COUNT].sColor);
			arrTags_[(i + 1) % TAGS_COUNT].condition = true;
			arrTags_[i].condition = false;

			for (int j = 0; j < 53; ++j) { //53 - counts of week in 2021
				CalendarWeek *week = calendarWeeks[j];

				if (week->date->toMSecsSinceEpoch() >= QDateTime::currentDateTime().toMSecsSinceEpoch()) {
					week->setStyleSheet("QPushButton{background: " + tag::ARR_LIGHT_COLORS[(i + 1) % TAGS_COUNT] + "; border-radius: 5px; "
															"font-size: 12px;font-family: Arial;color: #323232; font-weight: bold; font-style: italic; text-align:left; padding-left: 7px}");
				}
			}

			break;
		}
	}

}

void MainWindow::infoGBEnter()
{
	ui->infoButton->setFixedWidth(141);
}

void MainWindow::infoGBLeave()
{
	ui->infoButton->setFixedWidth(311);
}

void MainWindow::setInfoButtonColor(QString sColor)
{
	ui->infoButton->setStyleSheet("QPushButton {background:" + sColor + "; border-radius: 8px;}");

	for (int i = 0; i < TAGS_COUNT; i++) {
		if (sColor == arrTags_[i].sColor) {
			arrTags_[i].condition = true;
			infoButtonColorNum = i;
		}
		else {
			arrTags_[i].condition = false;
		}
	}
}

