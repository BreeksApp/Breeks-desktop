#include "QScrollArea"
#include <QPointer>
#include <memory>
#include "QScrollBar"

#include "mainwindow.h"
#include "gentextedit.h"
#include "addelement.h"
#include "elementtemplate.h"

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
  if (event->button() == Qt::LeftButton) {
    //QDrag *drag = new QDrag(this);

    //drag->setMimeData(&mimeData_);
    //drag->setPixmap(dragElement_);
    //Qt::DropAction dropAction = drag->exec();
  }
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

  ui->buttonAdd->setStyleSheet("border-image:url(:/Images/Images/addButtonHover.png)");
}

void MainWindow::recieveTimeTableZoneData(bool *daysCheck, const int arrSize, elementData_t newElement)
{
  for (int i = 0; i < arrSize; i++) {
    if (daysCheck[i] == true) {
      //add new element data to array
      const int newElementIndex = addNewElementToArray(newElement, i);

      //increase scroll area of this day
      if (arrDays_[i].elementsCount < 3) {
				arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight - 30);
      }
      else {
        arrDays_[i].groupBoxElementsHeight += ELEMENT_HEIGHT_;
        arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight);
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
        if (daysCheck[i] == true && value.arrBreeks[i]->getState() == false) {
          value.ifPosTaken_[i] = true;
          value.arrBreeks[i]->setState(true);
          value.arrBreeks[i]->setEnabled(true);
          value.arrBreeks[i]->connectToQml(newElement.nEmoji);

//          value.arrBreeks[i]->setEmoji(arrEmojiNormal[newElement.nEmoji], arrEmojiCompleted[newElement.nEmoji], arrEmojiDroped[newElement.nEmoji]);
          value.arrBreeks[i]->setEmoj(newElement.nEmoji);
          //value.arrBreeks[i]->setIndex()
          //value.arrBreeks[i]->setFlat(false);

//          QPixmap pix(arrEmojiNormal[newElement.nEmoji]);
//          pix = pix.scaledToWidth(value.arrBreeks[i]->width(), Qt::SmoothTransformation);
//          QIcon buttonIcon(pix);
//          value.arrBreeks[i]->setIcon(buttonIcon);
//          value.arrBreeks[i]->setIconSize(pix.rect().size());
        }
      }

      return;
    }
  }

//if we don't have breeks zone with this name
  breeksZone_t newZone;
  newZone.zoneIndex = breeksZonesCount_;
  allocateMemoryForBreeks(&newZone); // breeks constructor call here (6 constructors)
  setBreeksZone(&newZone); // make invisible ? and connect move event
  setDaysConnect(&newZone); // arrBreeksZoneDays[6] ? connect clicked() with breeks->changeBreekState
  newZone.breekText->setText(newElement.text);

  for (int i = 0; i < arrSize; ++i) {
    newZone.breeksZoneLayout->addWidget(newZone.arrBreeks[i], 1, i); // breeks added to layout here
//    newZone.arrBreeks[i]->setEmoji(arrEmojiNormal[newElement.nEmoji], arrEmojiCompleted[newElement.nEmoji], arrEmojiDroped[newElement.nEmoji]);
    newZone.arrBreeks[i]->setEmoj(newElement.nEmoji);
    newZone.arrBreeks[i]->setIndex(newZone.zoneIndex, i);

    if (daysCheck[i] == true) {
      newZone.ifPosTaken_[i] = true;
      newZone.arrBreeks[i]->setState(true);
      newZone.arrBreeks[i]->setVisible(true);
      newZone.arrBreeks[i]->connectToQml(newElement.nEmoji);
      newZone.arrBreeks[i]->setEnabled(true);

//      QPixmap pix(arrEmojiNormal[newElement.nEmoji]);
//      pix = pix.scaledToWidth(newZone.arrBreeks[i]->width(), Qt::SmoothTransformation);
//      QIcon buttonIcon(pix);
//      newZone.arrBreeks[i]->setIcon(buttonIcon);
//      newZone.arrBreeks[i]->setIconSize(pix.rect().size());
    }
    else {
      newZone.ifPosTaken_[i] = false;
    }
  }

  workZoneLayout_->addWidget(newZone.breeksZoneGroupBox, breeksZonesCount_ + 1, 0, 1, 6);
  breeksDescriptionZoneLayout_->addWidget(newZone.breeksDescriptionGroupBox, breeksZonesCount_ + 1, 0);

  arrBreeksZones_.push_back(newZone);
//  fillBreeksPositions(arrBreeksZones_.size() - 1);

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

void MainWindow::fillBreeksPositions(int zoneIndex)
{
  if (zoneIndex < arrBreeksZones_.size() && zoneIndex >= 0) {
    for (auto i : arrBreeksZones_[zoneIndex].arrBreeks) {
      arrBreeksZones_[zoneIndex].positionsOfBreeks.push_back(i->pos());
    }
  }
}

void MainWindow::recieveDayAndElementIndex(const int dayElementIndex, const int elementIndex)
{
  auto item = arrDays_[dayElementIndex].layoutDayElements->itemAt(elementIndex);
  arrDays_[dayElementIndex].layoutDayElements->removeItem(item);
  arrDays_[dayElementIndex].layoutDayElements->removeWidget(item->widget());
  delete item->widget();
  delete item;
  arrDays_[dayElementIndex].layoutDayElements->update();

  if (arrDays_[dayElementIndex].elementsCount <= 3) {
			arrDays_[dayElementIndex].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[dayElementIndex].groupBoxElementsHeight - 30);
  }
  else {
    arrDays_[dayElementIndex].groupBoxElementsHeight -= ELEMENT_HEIGHT_;
    arrDays_[dayElementIndex].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[dayElementIndex].groupBoxElementsHeight);
  }

  --arrDays_[dayElementIndex].elementsCount;

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
    if (dayIndex < 6) {
//      if (!arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->isEnabled()) {
//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->changeBreekState();
//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->changeBreekState();

        breeksZone_t *zone = &arrBreeksZones_[zoneIndex];
        Breek *breek = zone->arrBreeks[dayIndex];

        QVector<QPoint>::iterator it = std::find(zone->positionsOfBreeks.begin(),
                                                 zone->positionsOfBreeks.end(),
                                                 breek->pos());

        if (it < zone->positionsOfBreeks.end() - 1) {
          int index = it - zone->positionsOfBreeks.begin() + 1;
          if (!zone->ifPosTaken_[index]) {
//            breek->move(*(it + 1));

            QPropertyAnimation *animation = new QPropertyAnimation(breek, "geometry");
            QRect rectTo((it + 1)->x(), (it + 1)->y(), breek->geometry().width(), breek->geometry().height());
            animation->setDuration(4000);
            animation->setStartValue(breek->geometry());
            animation->setEndValue(rectTo);
            animation->start();

            breek->setFocus();
            zone->ifPosTaken_[index] = true;
            zone->ifPosTaken_[index - 1] = false;
          }
        }

//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->setFocus();
        workZoneScrollArea_->ensureVisible(breek->pos().x() + 250, 0);
//      }
    }
  }
  else {
    if (dayIndex >= 1) {
//      if (!arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->isEnabled()) {
//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->changeBreekState();
//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->changeBreekState();

        breeksZone_t *zone = &arrBreeksZones_[zoneIndex];
        Breek *breek = zone->arrBreeks[dayIndex];

        QVector<QPoint>::iterator it = std::find(zone->positionsOfBreeks.begin(),
                                                 zone->positionsOfBreeks.end(),
                                                 breek->pos());

        if (it > zone->positionsOfBreeks.begin()) {
          int index = it - zone->positionsOfBreeks.begin() - 1;
          if (!zone->ifPosTaken_[index]) {
//            breek->move(*(it - 1));

            QPropertyAnimation *animation = new QPropertyAnimation(breek, "geometry");
            QRect rectTo((it - 1)->x(), (it - 1)->y(), breek->geometry().width(), breek->geometry().height());
            animation->setDuration(4000);
            animation->setStartValue(breek->geometry());
            animation->setEndValue(rectTo);
            animation->start();

            breek->setFocus();
            zone->ifPosTaken_[index] = true;
            zone->ifPosTaken_[index + 1] = false;
          }
        }

//        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->setFocus();
        workZoneScrollArea_->ensureVisible(breek->pos().x() - 250, 0);
//      }
    }
  }
}

void MainWindow::dropElement(const int dayNumber, const int dayIndex, const int elemIndex, const elementData_t elemData)
{
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
    arrDays_[index].widgetDay->setFixedSize(DAY_WIDTH_, ELEMENT_HEIGHT_ * 3);
  }
}


