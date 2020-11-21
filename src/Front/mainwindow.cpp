#include "QScrollArea"
#include <QPointer>
#include <memory>
#include "QScrollBar"

#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <Front/MainElements/EmojiHub/emojihub.h>

#include "mainwindow.h"
#include "Front/GeneralTextEdit/gentextedit.h"
#include "Front/MainElements/addelement.h"
#include "Front/MainElements/elementtemplate.h"
#include "Front/datastructures.h"

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

	ui->note->setContentsMargins(10, 10, 10, 10);
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
		QPoint pos = this->mapToGlobal(this->cursor().pos());

		int posMain = this->mapToGlobal(ui->groupBoxWorkZone->pos()).x();

		if (pos.x() > posMain & pos.x() < posMain + 700) {
			QPoint pos1 = bigWidgetInWorkZone_->mapFromGlobal(this->cursor().pos());
			workZoneScrollArea_->ensureVisible(pos1.x() - 0.5, 0);
			QThread::msleep(2);
		}
		else if (pos.x() > posMain + ui->groupBoxWorkZone->width() - 700 & pos.x() < posMain + ui->groupBoxWorkZone->width()) {
			QPoint pos1 = bigWidgetInWorkZone_->mapFromGlobal(this->cursor().pos());
			workZoneScrollArea_->ensureVisible(pos1.x() + 0.5, 0);
			QThread::msleep(2);
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

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");
	ui->buttonAdd->setGraphicsEffect(effect);
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

			arrDays_[i].elementsScaledCount = 0;
      arrDays_[i].labelElementsCount->setText(QString::number(arrDays_[i].elementsCount));
    }
  }
}

void MainWindow::recieveBreeksZoneData(bool *daysCheck, const int arrSize, breeksData_t newElement)
{
//if we arleady have breeks zone with this name
	for (breeksZone_t &value : arrBreeksZones_) { //value == zone
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

			if (iCurrentDay_ < DAYS_COUNT & value.arrBreeks[iCurrentDay_]->getState()) {
				value.arrBreeksZoneDays[iCurrentDay_]->setStyleSheet("background: #b3defc; border-radius: 4px;");
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

	newZone.breekText->setFocus();
	newZone.breekText->fillCharsAndSetText(newElement.text, newElement.charStyleVector);
	newZone.breekText->moveCursor(QTextCursor::Start);
	newZone.breekText->verticalScrollBar()->maximum();

	if (iCurrentDay_ < DAYS_COUNT & newZone.arrBreeks[iCurrentDay_]->getState()) {
		newZone.arrBreeksZoneDays[iCurrentDay_]->setStyleSheet("background: #b3defc; border-radius: 4px;");
	}

	workZoneLayout_->addWidget(newZone.breeksZoneGroupBox, breeksZonesCount_ + 1, 0, 1, 6, Qt::AlignCenter);
	breeksDescriptionZoneLayout_->addWidget(newZone.breeksDescriptionGroupBox, breeksZonesCount_ + 1, 0, Qt::AlignCenter);

  arrBreeksZones_.push_back(newZone);

	if (breeksZonesCount_ == 0) {
		bigWidgetHeight_ += 130;
	}
	else {
		bigWidgetHeight_ += 125;
	}
	bigWidgetInWorkZone_->setFixedHeight(bigWidgetHeight_);
	bigWidgetInBreeksDescriptionZone_->setFixedHeight(bigWidgetHeight_);
	++breeksZonesCount_;

	//ADD BREEKS

	int i = 0;
	while (i < 11) {
		arrBreeksZones_[breeksZonesCount_ - 1].breeksZoneLayout->addWidget(newZone.arrBreeks[i / 2], 1, i);// breeks added to layout here

		//emojiHub
		EmojiHub *emojiHub = new EmojiHub;
		if (i != 10) {
			arrBreeksZones_[breeksZonesCount_ - 1].breeksZoneLayout->addWidget(emojiHub, 1, i + 1, Qt::AlignCenter);
		}

		arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2]->setEmoj(newElement.nEmoji);
		arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2]->setIndex(newZone.zoneIndex, i / 2);

		if (daysCheck[i / 2] == true) {
			arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2]->changeBreekState();
		}

		if (i / 2 < 5) {
			connect(arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2], SIGNAL(doubleClicked()), emojiHub, SLOT(showThis()));
			connect(emojiHub, SIGNAL(changeEmoji(int)), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2], SLOT(changeEmoji(int)));
			connect(emojiHub, SIGNAL(close()), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2], SLOT(closeEmojiHub()));
			connect(emojiHub, SIGNAL(open()), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2], SLOT(openEmojiHub()));
		}
		if (i / 2 + 1 == 5){
			connect(arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2 + 1], SIGNAL(doubleClicked()), emojiHub, SLOT(showThisSt()));
			connect(emojiHub, SIGNAL(changeEmojiSt(int)), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2 + 1], SLOT(changeEmoji(int)));
			connect(emojiHub, SIGNAL(closeSt()), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2 + 1], SLOT(closeEmojiHub()));
			connect(emojiHub, SIGNAL(openSt()), arrBreeksZones_[breeksZonesCount_ - 1].arrBreeks[i / 2 + 1], SLOT(openEmojiHub()));
		}

		i += 2;
	}
}

void MainWindow::recieveDayAndElementIndex(const int dayElementIndex, const int elementIndex)
{
  auto item = arrDays_[dayElementIndex].layoutDayElements->itemAt(elementIndex);

	if (!item->widget()->isHidden()) {
		arrDays_[dayElementIndex].layoutDayElements->removeItem(item);
		arrDays_[dayElementIndex].layoutDayElements->removeWidget(item->widget());

		if (item->widget()->size().height() > 100) {
			--arrDays_[dayElementIndex].elementsScaledCount;
		}

		delete item->widget();
		delete item;
		arrDays_[dayElementIndex].layoutDayElements->update();

		--arrDays_[dayElementIndex].elementsCount;

		if (arrDays_[dayElementIndex].elementsCount <= 3 & arrDays_[dayElementIndex].elementsScaledCount < 3) {
				arrDays_[dayElementIndex].groupBoxElementsHeight = 370;
		}
		else {
			arrDays_[dayElementIndex].groupBoxElementsHeight = ELEMENT_HEIGHT_ * (arrDays_[dayElementIndex].elementsCount
						- arrDays_[dayElementIndex].elementsScaledCount)
						+ (ELEMENT_HEIGHT_ + 30) * arrDays_[dayElementIndex].elementsScaledCount + 25;
			//arrDays_[dayElementIndex].groupBoxElementsHeight =
						//ELEMENT_HEIGHT_ * arrDays_[dayElementIndex].elementsCount + 25;
		}
		arrDays_[dayElementIndex].widgetDay->setFixedHeight(arrDays_[dayElementIndex].groupBoxElementsHeight);

		if (arrDays_[dayElementIndex].elementsCount == 0) {
			arrDays_[dayElementIndex].labelElementsCount->setText("");
		}
		else {
			arrDays_[dayElementIndex].labelElementsCount->setText(
						QString::number(arrDays_[dayElementIndex].elementsCount));
		}

		iterType start = arrDaysData_[dayElementIndex].begin();
		arrDaysData_[dayElementIndex].erase(start + elementIndex);

		for (int i = elementIndex; i < arrDays_[dayElementIndex].elementsCount; ++i) {
			ElementTemplate *a = qobject_cast<ElementTemplate*>
						(arrDays_[dayElementIndex].layoutDayElements->itemAt(i)->widget());
			a->setElementIndex(i);
		}
	}
	else {
		item->widget()->show();
	}
}

void MainWindow::recieveDayAndElementIndexAndTagColor(const int dayIndex, const int elementIndex, const QString sColor)
{
		arrDaysData_[dayIndex][elementIndex].tagColor = sColor;
}

void MainWindow::recieveUsername()
{
		this->showMaximized();
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

        workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex + 1]->pos().x() + 250, 0);
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
				}
        zone->arrBreeks[dayIndex - 1]->changeBreekState();
        zone->arrBreeks[dayIndex]->move(posFrom);

        workZoneScrollArea_->ensureVisible(zone->arrBreeks[dayIndex - 1]->pos().x() - 250, 0);
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


