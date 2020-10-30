#include "Front/mainwindow.h"
#include "QScrollBar"

void MainWindow::setWorkZone()
{
  bigWidgetInWorkZone_ = new QWidget;
  bigWidgetInBreeksDescriptionZone_ = new QWidget;

  workZoneLayout_ = new QGridLayout;
  workZoneScrollArea_ = new QScrollArea;

  breeksDescriptionZoneScrollArea_ = new QScrollArea;
  breeksDescriptionZoneLayout_ = new QGridLayout;

  connect(this->workZoneScrollArea_->verticalScrollBar(), &QScrollBar::valueChanged,
        this->breeksDescriptionZoneScrollArea_->verticalScrollBar(), &QScrollBar::setValue);
  connect(this->breeksDescriptionZoneScrollArea_->verticalScrollBar(), &QScrollBar::valueChanged,
        this->workZoneScrollArea_->verticalScrollBar(), &QScrollBar::setValue);

	bigWidgetHeight_ = 500;//ui->groupBoxWorkZone->height() - 20;
  breeksZonesCount_ = 0;

	//const int scrollAreaWidth = 500;
	//const int scrollAreaHeight = 950;
	workZoneScrollArea_->setFixedWidth(ui->groupBoxWorkZone->width() - 20);

  QHBoxLayout *layOut = new QHBoxLayout;
  layOut->addWidget(workZoneScrollArea_, Qt::AlignCenter);
  ui->groupBoxWorkZone->setLayout(layOut);

	workZoneScrollArea_->setContentsMargins(0, 5, 0, 0);
	bigWidgetInWorkZone_->setContentsMargins(0, 5, 0, 0);

	//ui->groupBoxWorkZone->setStyleSheet("background: none;");

  buildTimeTable();
  buildBreeksDescriptionZone();
}
