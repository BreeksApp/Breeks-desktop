#include "QScrollArea"
#include <QPointer>
#include <memory>
#include "QScrollBar"

#include <QtConcurrent/QtConcurrent>
#include <QThread>

#include "mainwindow.h"
#include "Front/GeneralTextEdit/gentextedit.h"
#include "Front/MainElements/addelement.h"
#include "Front/MainElements/elementtemplate.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
	ui(new Ui::MainWindow),
	fileLastVisit_(fileLastVisitName_),
	fileMon_(fileMonName_),
	fileTue_(fileTueName_),
	fileWed_(fileWedName_),
	fileThu_(fileThuName_),
	fileFri_(fileFriName_),
	fileSat_(fileSatName_)
{
  ui->setupUi(this);

	this->setStyleSheet("background: #F9F9F9");

  loginForm_ = new LoginForm;
  connect(loginForm_, SIGNAL(firstWindow()), this, SLOT(recieveUsername())); //Connect login and Mainwindow form
  connect(loginForm_, SIGNAL(sendUsername(const QString)), ui->note, SLOT(recieveUsername(const QString))); //Send username to TextEdit

	connect(ui->buttonImage, SIGNAL(imageEnter(bool)), this, SLOT(setImageBackgroundView(bool)));
	connect(ui->buttonImage, SIGNAL(imageLeave(bool)), this, SLOT(setImageBackgroundView(bool)));

	setWorkZone();

	setStatesFromFileLastVisit();
	setAllElementsEffects();
}

MainWindow::~MainWindow()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  for (int i = 0; i < 6; ++i) {
        writeElementsDataToFile(i);
  }

  delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	//qDebug("Pressed");
}

void MainWindow::moveTimetableElement()
{
	//qDebug() << ui->groupBox->mapToGlobal(this->cursor().pos());
	while (isElementDrag_) {
		QPoint pos = ui->groupBox->mapToGlobal(this->cursor().pos());
		if (pos.x() > 920 & pos.x() < 1150) {
			QPoint pos1 = bigWidgetInWorkZone_->mapFromGlobal(this->cursor().pos());
			workZoneScrollArea_->ensureVisible(pos1.x() - 5, 0);
			QThread::msleep(10);
		}
		else if (pos.x() > 1850 & pos.x() < 2050) {
			QPoint pos1 = bigWidgetInWorkZone_->mapFromGlobal(this->cursor().pos());
			workZoneScrollArea_->ensureVisible(pos1.x() + 5, 0);
			QThread::msleep(10);
		}
	}
}

void MainWindow::mousePressedByDragElement()
{
	isElementDrag_ = true;
	QFuture<void> future = QtConcurrent::run(this, &MainWindow::moveTimetableElement);
}

void MainWindow::dropNoChanges()
{
	//qDebug("LOCK");
	isElementDrag_ = false;
}

void MainWindow::on_buttonAdd_clicked()
{
  AddElement *addForm = new AddElement(ui->buttonAdd);//have to reset stylesheet in form destuctor
  addForm->setAttribute(Qt::WA_DeleteOnClose);

  //signal to move info from creating element form to new element on timetable
  connect(addForm, SIGNAL(sendTimeTableZoneData(bool*, const int, elementData_t)),
        this, SLOT(recieveTimeTableZoneData(bool*, const int, elementData_t)));
  connect(addForm, SIGNAL(sendBreeksZoneData(bool*, const int, breeksData_t)),
        this, SLOT(recieveBreeksZoneData(bool*, const int, breeksData_t)));

  addForm->show();
  const int a = -25;
  const int b = 225;
  const int x = ui->buttonAdd->pos().x() + a;
  const int y = ui->buttonAdd->pos().y() + b;
  addForm->move(x, y);

  ui->buttonAdd->setStyleSheet("border-image:url(:/Images/Front/Images/addButtonHover.png)");
}

void MainWindow::recieveTimeTableZoneData(bool *daysCheck, const int arrSize, elementData_t newElement)
{
  for (int i = 0; i < arrSize; i++) {
    if (daysCheck[i] == true) {
      //add new element data to array
      const int newElementIndex = addNewElementToArray(newElement, i);

      //increase scroll area of this day
      if (arrDays_[i].elementsCount < 3) {
				//arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight - 30);
      }
      else {
				arrDays_[i].groupBoxElementsHeight = ELEMENT_HEIGHT_ * (arrDays_[i].elementsCount + 1) + 25;
				arrDays_[i].widgetDay->setFixedHeight(arrDays_[i].groupBoxElementsHeight);
      }

      //add new element to layout
      addNewElementToLayout(i, newElementIndex);

      //TODO solve the problem with bad auto moving
      /*if ((arrDays_[i].elementsCount % 6) == 0) {
        qDebug() << arrDays_[i].elementsCount;
        arrDays_[i].groupBoxElementsHeight -= 7;
      }*/

      arrDays_[i].labelElementsCount->setText(QString::number(arrDays_[i].elementsCount));
    }
  }
}

void MainWindow::recieveBreeksZoneData(bool *daysCheck, const int arrSize, breeksData_t newElement)
{
//if we arleady have breeks zone with this name
  for (breeksZone_t &value : arrBreeksZones_) {
    if (value.breekText->toPlainText() == newElement.text) {

      for (int i = 0; i < DAYS_COUNT; i++) {
        Breek * breek = value.arrBreeks[i];
        if (breek->getEmojiNum() != newElement.nEmoji) {
          breek->setEmoj(newElement.nEmoji);
          breek->changeBreekState();
          breek->changeBreekState();

          if (daysCheck[i] == true && breek->getState() == false) {
            breek->changeBreekState();
          }
        }
        else {
          if (daysCheck[i] == true && breek->getState() == false) {
            breek->changeBreekState();
          }
        }
      }

      return;
    }
  }

//if we don't have breeks zone with this name
  breeksZone_t newZone;
  newZone.zoneIndex = breeksZonesCount_;
  allocateMemoryForBreeks(&newZone); // breeks constructor call here (6 constructors)
  setBreeksZone(&newZone); // make invisible and connect move event
  setDaysConnect(&newZone); // arrBreeksZoneDays[6] connect clicked() with breeks->changeBreekState
  newZone.breekText->setText(newElement.text);

  for (int i = 0; i < arrSize; ++i) {
    newZone.breeksZoneLayout->addWidget(newZone.arrBreeks[i], 1, i); // breeks added to layout here
    newZone.arrBreeks[i]->setEmoj(newElement.nEmoji);
    newZone.arrBreeks[i]->setIndex(newZone.zoneIndex, i);

    if (daysCheck[i] == true) {
      newZone.arrBreeks[i]->changeBreekState();
    }
  }

  workZoneLayout_->addWidget(newZone.breeksZoneGroupBox, breeksZonesCount_ + 1, 0, 1, 6);
  breeksDescriptionZoneLayout_->addWidget(newZone.breeksDescriptionGroupBox, breeksZonesCount_ + 1, 0);

  arrBreeksZones_.push_back(newZone);

  if (breeksZonesCount_ == 1) {
    bigWidgetHeight_ += 120;
  }
  else {
    bigWidgetHeight_ += 120;
  }

  bigWidgetInWorkZone_->setFixedSize(WORK_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);
  bigWidgetInBreeksDescriptionZone_->setFixedSize(BREEKS_DESCRIPTION_ZONE_BIG_WIDGET_WIDTH, bigWidgetHeight_);

  ++breeksZonesCount_;
}

void MainWindow::recieveDayAndElementIndex(const int dayElementIndex, const int elementIndex)
{
  auto item = arrDays_[dayElementIndex].layoutDayElements->itemAt(elementIndex);
	if (item->widget()->isHidden()) {
		item->widget()->show();
	}
  arrDays_[dayElementIndex].layoutDayElements->removeItem(item);
  arrDays_[dayElementIndex].layoutDayElements->removeWidget(item->widget());
  delete item->widget();
  delete item;
  arrDays_[dayElementIndex].layoutDayElements->update();
	--arrDays_[dayElementIndex].elementsCount;

  if (arrDays_[dayElementIndex].elementsCount <= 3) {
			arrDays_[dayElementIndex].groupBoxElementsHeight = 370;
			arrDays_[dayElementIndex].widgetDay->setFixedHeight(arrDays_[dayElementIndex].groupBoxElementsHeight);
  }
  else {
		arrDays_[dayElementIndex].groupBoxElementsHeight = ELEMENT_HEIGHT_ * arrDays_[dayElementIndex].elementsCount + 25;
    arrDays_[dayElementIndex].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[dayElementIndex].groupBoxElementsHeight);
  }

  if (arrDays_[dayElementIndex].elementsCount == 0) {
    arrDays_[dayElementIndex].labelElementsCount->setText("");
  }
  else {
    arrDays_[dayElementIndex].labelElementsCount->setText(QString::number(arrDays_[dayElementIndex].elementsCount));
  }

  iterType start = arrDaysData_[dayElementIndex].begin();
  arrDaysData_[dayElementIndex].erase(start + elementIndex);

  for (int i = elementIndex; i < arrDays_[dayElementIndex].elementsCount; ++i) {
    ElementTemplate *a = qobject_cast<ElementTemplate*>(arrDays_[dayElementIndex].layoutDayElements->itemAt(i)->widget());
    a->setElementIndex(i);
  }
}

void MainWindow::recieveDayAndElementIndexAndTagColor(const int dayIndex, const int elementIndex, const QPalette color)
{
    arrDaysData_[dayIndex][elementIndex].palette = color;
}

void MainWindow::recieveUsername()
{
    this->show();
}

void MainWindow::recieveMimeData(const elementData_t data, const QPixmap pixMap)
{
  mimeData_.setText(data.text);
  dragElement_ = pixMap;
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
        zone->arrBreeks[dayIndex + 1]->changeBreekState();
        zone->arrBreeks[dayIndex]->move(posFrom);

        zone->arrBreeks[dayIndex + 1]->setFocus();

        workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex + 1]->pos().x() + 250, 0);
      }
    }

  }
  else {
    if (dayIndex > 0) {
      breeksZone_t *zone = &arrBreeksZones_[zoneIndex];
      if (!zone->arrBreeks[dayIndex - 1]->isEnabled()) {
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
        zone->arrBreeks[dayIndex - 1]->changeBreekState();
        zone->arrBreeks[dayIndex]->move(posFrom);

        zone->arrBreeks[dayIndex - 1]->setFocus();

        workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex - 1]->pos().x() - 250, 0);
      }
    }
  }
}

void MainWindow::dropElement(const int dayNumber, const int dayIndex, const int elemIndex, const elementData_t elemData)
{
	dropNoChanges();

  bool daysCheck_[6];
  for (int i = 0; i < 6; i++) {
    if (i == dayNumber) {
      daysCheck_[i] = true;
    }
    else {
      daysCheck_[i] = false;
    }
  }

  recieveTimeTableZoneData(daysCheck_, 6, elemData);
}

void MainWindow::sendElementsHeight(const int height, const int index)
{
  if (arrDays_[index].elementsCount < 3) {
		arrDays_[index].widgetDay->setFixedHeight(ELEMENT_HEIGHT_ * 3);
  }
}


