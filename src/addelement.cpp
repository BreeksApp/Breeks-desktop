#include "addelement.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

#include <iostream>

AddElement::AddElement(AddButtonHover *button, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AddElement),
  mainAddButton_(button)
{
  ui->setupUi(this);

  for (int i = 0; i < DAYS_CHECK_COUNT; i++) {
    daysCheck_[i] = false;
  }

  setAllElementsEffects();

  const int formAddElementWidth = 325;
  const int formAddElementHeight = 170;

  QFont font("Helvetica", 12);
  ui->text->setFont(font);

  breeksZoneCondition_ = true;
  timeTableZoneCondition_ = false;
  effects::setElementColor(ui->pushButtonBreeksZone, paletteSelectedElement_);
  ui->timeStart->hide();
  ui->timeEnd->hide();

  this->setFixedSize(QSize(formAddElementWidth, formAddElementHeight));
  this->setWindowModality(Qt::ApplicationModal);
}

AddElement::~AddElement()
{
  mainAddButton_->setStyleSheet("border-image:url(:/Images/Images/addButtonDefault.png)");
  delete ui;
}

void AddElement::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) {
    this->close();
  }
}

//details
bool AddElement::areSelectedDays()
{
  for (int i = 0; i < DAYS_CHECK_COUNT; i++) {
    if (daysCheck_[i] == true) {
      return true;
    }
  }
  return false;
}

void AddElement::returnButtonsInitialCondition()
{
  for (int i = 0; i < DAYS_CHECK_COUNT; i++) {
    daysCheck_[i] = false;
  }
}

//element effects
void AddElement::setAllElementsEffects()
{
  paletteSelectedElement_.setColor(QPalette::Button, effects::colorSelected); //blue
  paletteDefaultElement_.setColor(QPalette::Button, effects::colorDefault); //grey

  //DAYS
  effects::setElementColor(ui->buttonMonday, paletteDefaultElement_);
  effects::setElementColor(ui->buttonTuesday, paletteDefaultElement_);
  effects::setElementColor(ui->buttonWednesday, paletteDefaultElement_);
  effects::setElementColor(ui->buttonThursday, paletteDefaultElement_);
  effects::setElementColor(ui->buttonFriday, paletteDefaultElement_);
  effects::setElementColor(ui->buttonSaturday, paletteDefaultElement_);

  //TAG
  for (int i = 0; i < TAGS_COUNT; ++i) {
    arrTags_[i].condition = false;
    arrTags_[i].pallete.setColor(QPalette::Button, tag::ARR_COLORS[i]);
  }
  arrTags_[TAGS_COUNT - 1].condition = true;
  currentTagPalette_.setColor(QPalette::Button, tag::ARR_COLORS[TAGS_COUNT - 1]/*green*/);
	effects::setElementColor(ui->buttonTag, currentTagPalette_);
  //

  //EMOJI
  for (int i = 1; i < EMOJI_COUNT; ++i) {
    arrEmoji_[i].condition = false;

    QString sAdress = ":/Images/Images/Breeks/" + QString::number(i) + ".png";
    arrEmoji_[i].emojiAdress = sAdress;
  }

  setEmoji(1);
  currentEmoji = 1;
}

void AddElement::setEmoji(const int index)
{
  QPixmap * pix = new QPixmap(arrEmoji_[index].emojiAdress);

  *pix = pix->scaledToWidth(ui->buttonTag->width(), Qt::SmoothTransformation);
  QIcon buttonIcon(*pix);

  ui->buttonTag->setIcon(buttonIcon);
  ui->buttonTag->setIconSize((*pix).rect().size());

  arrEmoji_[index].condition = true;
}
//

//-------------------------BUTTONS-------------------------
void AddElement::on_buttonAdd_clicked()
{
  if (!(timeTableZoneCondition_ || breeksZoneCondition_)) {
    return;
  }

  QString text = ui->text->toPlainText();
  if (text.size() == 0) {
    return;
  }
  for (int i = 0; i < text.size(); ++i) {
    if (text[i] != ' ' && text[i] != '\t' && text[i] != '\n') {
      break;
    }
    if (i + 1 == text.size()) {
      ui->text->clear();
      return;
    }
  }
  if (!areSelectedDays()) {
    return;
  }

  if (timeTableZoneCondition_ == true) {
    elementData_t newElement;

    newElement.text = text;

    QString sTimeStrart = ui->timeStart->time().toString();
    QString sTimeEnd = ui->timeEnd->time().toString();

    if ((sTimeStrart < sTimeEnd) || (sTimeEnd == "00:00:00")) {
      newElement.timeStart = sTimeStrart;
      newElement.timeEnd = sTimeEnd;
    }
    else if (sTimeStrart == sTimeEnd){
      newElement.timeStart = sTimeStrart;
      newElement.timeEnd = "00:00:00";
    }
    else {
      //reverse time
      newElement.timeStart = sTimeEnd;
      newElement.timeEnd = sTimeStrart;
    }
    newElement.timeStart.remove(5, 3);
    newElement.timeEnd.remove(5, 3);

    newElement.palette = ui->buttonTag->palette();
    newElement.charStyleVector = ui->text->getCharStyleVector();

    emit sendTimeTableZoneData(daysCheck_, DAYS_CHECK_COUNT, newElement);
  }
  else if (breeksZoneCondition_ == true) {
    breeksData_t newElement;
    newElement.text = text;
    newElement.nEmoji = currentEmoji - 1;

    emit sendBreeksZoneData(daysCheck_, DAYS_CHECK_COUNT, newElement);
  }

	returnButtonsInitialCondition();
  this->close();
}

void AddElement::on_buttonMonday_clicked()
{
  if (daysCheck_[0] == false) {
    effects::setElementColor(ui->buttonMonday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonMonday, paletteDefaultElement_);
  }
  daysCheck_[0] = !daysCheck_[0];
}
void AddElement::on_buttonTuesday_clicked()
{
  if (daysCheck_[1] == false) {
    effects::setElementColor(ui->buttonTuesday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonTuesday, paletteDefaultElement_);
  }
  daysCheck_[1] = !daysCheck_[1];
}
void AddElement::on_buttonWednesday_clicked()
{
  if (daysCheck_[2] == false) {
    effects::setElementColor(ui->buttonWednesday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonWednesday, paletteDefaultElement_);
  }
  daysCheck_[2] = !daysCheck_[2];
}
void AddElement::on_buttonThursday_clicked()
{
  if (daysCheck_[3] == false) {
    effects::setElementColor(ui->buttonThursday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonThursday, paletteDefaultElement_);
  }
  daysCheck_[3] = !daysCheck_[3];
}
void AddElement::on_buttonFriday_clicked()
{
  if (daysCheck_[4] == false) {
    effects::setElementColor(ui->buttonFriday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonFriday, paletteDefaultElement_);
  }
  daysCheck_[4] = !daysCheck_[4];
}
void AddElement::on_buttonSaturday_clicked()
{
  if (daysCheck_[5] == false) {
    effects::setElementColor(ui->buttonSaturday, paletteSelectedElement_);
  }
  else {
    effects::setElementColor(ui->buttonSaturday, paletteDefaultElement_);
  }
  daysCheck_[5] = !daysCheck_[5];
}

void AddElement::on_buttonTag_clicked()
{
  if (timeTableZoneCondition_) {
    for (int i = 0; i < TAGS_COUNT; ++i) {
      if (arrTags_[i].condition == true) {
        effects::setElementColor(ui->buttonTag, arrTags_[(i + 1) % TAGS_COUNT].pallete);

        currentTagPalette_ = arrTags_[(i + 1) % TAGS_COUNT].pallete;

        if (i == TAGS_COUNT - 1) {
          arrTags_[0].condition = true;
        }
        else {
          arrTags_[i+1].condition = true;
        }

        arrTags_[i].condition = false;
        break;
      }
    }
  }
  else {
    setEmoji((currentEmoji + 1) % EMOJI_COUNT);
    arrEmoji_[(currentEmoji + 1) % EMOJI_COUNT].condition = true;

    arrEmoji_[currentEmoji].condition = false;
    currentEmoji = (currentEmoji + 1) % EMOJI_COUNT;
  }
}

void AddElement::on_pushButtonTimeTableZone_clicked()
{
  timeTableZoneCondition_ = true;
  breeksZoneCondition_ = false;

  if (timeTableZoneCondition_) {
    effects::setElementColor(ui->pushButtonTimeTableZone, paletteSelectedElement_);
    effects::setElementColor(ui->pushButtonBreeksZone, paletteDefaultElement_);

    effects::setElementColor(ui->buttonTag, currentTagPalette_);
    setEmoji(0);

    ui->timeStart->show();
    ui->timeEnd->show();
  }
	else {
    effects::setElementColor(ui->pushButtonTimeTableZone, paletteDefaultElement_);
    effects::setElementColor(ui->pushButtonBreeksZone, paletteSelectedElement_);

    effects::setElementColor(ui->buttonTag, paletteDefaultElement_);
    setEmoji(currentEmoji);

    ui->timeStart->hide();
    ui->timeEnd->hide();
	}
}

void AddElement::on_pushButtonBreeksZone_clicked()
{
  breeksZoneCondition_ = true;
  timeTableZoneCondition_ = false;

  if (breeksZoneCondition_) {
    effects::setElementColor(ui->pushButtonBreeksZone, paletteSelectedElement_);
    effects::setElementColor(ui->pushButtonTimeTableZone, paletteDefaultElement_);

    effects::setElementColor(ui->buttonTag, paletteDefaultElement_);
    setEmoji(currentEmoji);

    ui->timeStart->hide();
    ui->timeEnd->hide();
  }
  /*else {
    effects::setElementColor(ui->pushButtonBreeksZone, paletteDefaultElement_);
    effects::setElementColor(ui->pushButtonTimeTableZone, paletteSelectedElement_);

    setEmoji(0);
    effects::setElementColor(ui->buttonTag, currentTagPalette_);

    ui->timeStart->show();
    ui->timeEnd->show();
  }*/
}
