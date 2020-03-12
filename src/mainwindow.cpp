#include "QScrollArea"
#include <QPointer>
#include <memory>
#include "QScrollBar"

#include "mainwindow.h"
#include "notetextedit.h"
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
  ui->note->writeToFile();

  for (int i = 0; i < 6; ++i) {
    writeElementsDataToFile(i);
  }

  delete ui;
}

void MainWindow::on_buttonAdd_clicked()
{
  AddElement *addForm = new AddElement(ui->buttonAdd);//have to reset stylesheet in form destuctor
  addForm->setAttribute(Qt::WA_DeleteOnClose);

  //signal to move info from creating element form to new element on timetable
  connect(addForm, SIGNAL(sendTimeTableZoneData(bool*, const int, ElementData)),
        this, SLOT(recieveTimeTableZoneData(bool*, const int, ElementData)));
  connect(addForm, SIGNAL(sendBreeksZoneData(bool*, const int, BreeksData)),
        this, SLOT(recieveBreeksZoneData(bool*, const int, BreeksData)));

  addForm->show();
  const int a = -25;
  const int b = 225;
  const int x = ui->buttonAdd->pos().x() + a;
  const int y = ui->buttonAdd->pos().y() + b;
  addForm->move(x, y);

  ui->buttonAdd->setStyleSheet("border-image:url(:/images/images/addButtonHover.png)");
}

void MainWindow::recieveTimeTableZoneData(bool *daysCheck, const int arrSize, ElementData newElement)
{
  for (int i = 0; i < arrSize; i++) {
    if (daysCheck[i] == true) {
      //add new element data to array
      const int newElementIndex = addNewElementToArray(newElement, i);

      //increase scroll area of this day
      arrDays_[i].groupBoxElementsHeight += ELEMENT_HEIGHT_;
      arrDays_[i].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[i].groupBoxElementsHeight);

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

void MainWindow::recieveBreeksZoneData(bool *daysCheck, const int arrSize, BreeksData newElement)
{
//if we arleady have breeks zone with this name
  for (breeksZone_t &value : arrBreeksZones_) {
    if (value.breekText->toPlainText() == newElement.text) {

      for (int i = 0; i < DAYS_COUNT; i++) {
        if (daysCheck[i] == true && value.arrBreeks[i]->getState() == false) {
          value.arrBreeks[i]->setState(true);
          value.arrBreeks[i]->setEnabled(true);

          value.arrBreeks[i]->setEmoji(arrEmojiNormal[newElement.nEmoji], arrEmojiCompleted[newElement.nEmoji], arrEmojiDroped[newElement.nEmoji]);
          //value.arrBreeks[i]->setIndex()
          //value.arrBreeks[i]->setFlat(false);

          QPixmap pix(arrEmojiNormal[newElement.nEmoji]);
          pix = pix.scaledToWidth(value.arrBreeks[i]->width(), Qt::SmoothTransformation);
          QIcon buttonIcon(pix);
          value.arrBreeks[i]->setIcon(buttonIcon);
          value.arrBreeks[i]->setIconSize(pix.rect().size());
        }
      }

      return;
    }
  }

//if we haven't breeks zone with this name
  breeksZone_t newZone;
  newZone.zoneIndex = breeksZonesCount_;
  allocateMemoryForBreeks(&newZone);
  setBreeksZone(&newZone);
  setDaysConnect(&newZone);
  newZone.breekText->setText(newElement.text);

  for (int i = 0; i < arrSize; ++i) {
    newZone.breeksZoneLayout->addWidget(newZone.arrBreeks[i], 1, i);
    newZone.arrBreeks[i]->setEmoji(arrEmojiNormal[newElement.nEmoji], arrEmojiCompleted[newElement.nEmoji], arrEmojiDroped[newElement.nEmoji]);
    newZone.arrBreeks[i]->setIndex(newZone.zoneIndex, i);

    if (daysCheck[i] == true) {
      newZone.arrBreeks[i]->setState(true);
      newZone.arrBreeks[i]->setVisible(true);
      newZone.arrBreeks[i]->setEnabled(true);

      QPixmap pix(arrEmojiNormal[newElement.nEmoji]);
      pix = pix.scaledToWidth(newZone.arrBreeks[i]->width(), Qt::SmoothTransformation);
      QIcon buttonIcon(pix);
      newZone.arrBreeks[i]->setIcon(buttonIcon);
      newZone.arrBreeks[i]->setIconSize(pix.rect().size());
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
  arrDays_[dayElementIndex].layoutDayElements->removeItem(item);
  arrDays_[dayElementIndex].layoutDayElements->removeWidget(item->widget());
  delete item->widget();
  delete item;
  arrDays_[dayElementIndex].layoutDayElements->update();

  arrDays_[dayElementIndex].groupBoxElementsHeight -= ELEMENT_HEIGHT_;
  arrDays_[dayElementIndex].widgetDay->setFixedSize(DAY_WIDTH_, arrDays_[dayElementIndex].groupBoxElementsHeight);

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

void MainWindow::moveBreek(int zoneIndex, int dayIndex, bool right)
{
  if (right) {
    if (dayIndex < 6) {
      if (!arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->isEnabled()) {
        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->changeBreekState();
        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->changeBreekState();

        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->setFocus();
        workZoneScrollArea_->ensureVisible(arrBreeksZones_[zoneIndex].arrBreeks[dayIndex + 1]->pos().x() + 250, 0);
      }
    }
  }
  else {
    if (dayIndex >= 1) {
      if (!arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->isEnabled()) {
        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->changeBreekState();
        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex]->changeBreekState();

        arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->setFocus();
        workZoneScrollArea_->ensureVisible(arrBreeksZones_[zoneIndex].arrBreeks[dayIndex - 1]->pos().x() - 250, 0);
      }
    }
  }
}



void MainWindow::on_pushButton_clicked()
{
  loginForm_->show();
  this->close();
}
