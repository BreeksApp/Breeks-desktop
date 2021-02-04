#include "Front/mainwindow.h"

void MainWindow::on_buttonAdd_2_clicked() {
  if (ui->addBreekGB->isHidden() & breeksZonesCount_ < 30) {
    ui->addBreekGB->show();
    ui->emojiHub->showThis();
  }
  else if (!ui->addBreekGB->isHidden()) {
    ui->emojiHub->showThis();
    ui->addBreekGB->hide();
  }
}

void MainWindow::setStyleAddBreeksForm() {
  ui->addBreekGB->setStyleSheet("QGroupBox{background: #e8f7cd; border: 1px solid #C6C6C6; border-radius: 18px;}");

  ui->breekDescription->setFont(QFont("Helvetica", 12));
  ui->breekDescription->setStyleSheet(
    "background: #FFFFFF; border: 1px solid #F7F7F7; border-radius: 6px;"
    "padding-left:2;"
    "padding-top:2;"
    "padding-bottom:2;"
    "padding-right:2;"
  );

  ui->breekDescription->clear();
  ui->breekDescription->clearCharStyleVector();

  for (int i = 0; i < DAYS_COUNT; ++i) {
    arrAddBreekFormDaysCheck_[i] = false;
  }

  QString dayButtonStyleSheet =
    "QPushButton{background: #F7F7F7; border-radius: 4px;"
    "font-size: 10pt;}"
    "QPushButton:hover{background: #e6f6ff; border-radius: 4px;"
    "font-size: 10pt;}";

  ui->mnBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->mnBreekButton->setFont(QFont("Helvetica"));
  ui->tuBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->tuBreekButton->setFont(QFont("Helvetica"));
  ui->weBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->weBreekButton->setFont(QFont("Helvetica"));
  ui->thBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->thBreekButton->setFont(QFont("Helvetica"));
  ui->frBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->frBreekButton->setFont(QFont("Helvetica"));
  ui->stBreekButton->setStyleSheet(dayButtonStyleSheet);
  ui->stBreekButton->setFont(QFont("Helvetica"));

  ui->mnBreekButton->setGraphicsEffect(createShadow());
  ui->tuBreekButton->setGraphicsEffect(createShadow());
  ui->weBreekButton->setGraphicsEffect(createShadow());
  ui->thBreekButton->setGraphicsEffect(createShadow());
  ui->frBreekButton->setGraphicsEffect(createShadow());
  ui->stBreekButton->setGraphicsEffect(createShadow());

  //ui->baseBreek->setStyleSheet("background: #F7F7F7; border-radius: 4px");
  //ui->baseBreek->setGraphicsEffect(createShadow());

  ui->addBreekButton->setStyleSheet(
    "QPushButton{background: #81C4FF; border-radius: 24px; color: #e6f6ff; font-size: 12pt; font-weight: bold;} "
    "QPushButton:hover{background: #b0d7ff; border-radius: 24px; color: #e6f6ff; font-size: 12pt; font-weight: bold;}"
  );
}

QGraphicsDropShadowEffect* MainWindow::createShadow() {
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
  effect->setBlurRadius(5);
  effect->setXOffset(0);
  effect->setYOffset(0);
  effect->setColor("#BABCBE");

  return effect;
}

void MainWindow::on_mnBreekButton_clicked() {
  if (arrAddBreekFormDaysCheck_[0] == false) {
    ui->mnBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->mnBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[0] = !arrAddBreekFormDaysCheck_[0];
}

void MainWindow::on_tuBreekButton_clicked() {
  if (arrAddBreekFormDaysCheck_[1] == false) {
    ui->tuBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->tuBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[1] = !arrAddBreekFormDaysCheck_[1];
}

void MainWindow::on_weBreekButton_clicked() {
  if (arrAddBreekFormDaysCheck_[2] == false) {
    ui->weBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->weBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[2] = !arrAddBreekFormDaysCheck_[2];
}

void MainWindow::on_thBreekButton_clicked() {
  if (arrAddBreekFormDaysCheck_[3] == false) {
    ui->thBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->thBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[3] = !arrAddBreekFormDaysCheck_[3];
}

void MainWindow::on_frBreekButton_clicked()
{
  if (arrAddBreekFormDaysCheck_[4] == false) {
    ui->frBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->frBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[4] = !arrAddBreekFormDaysCheck_[4];
}

void MainWindow::on_stBreekButton_clicked()
{
  if (arrAddBreekFormDaysCheck_[5] == false) {
    ui->stBreekButton->setStyleSheet(
      "QPushButton{background: #81C4FF; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  else {
    ui->stBreekButton->setStyleSheet(
      "QPushButton{background: #F7F7F7; border-radius: 4px; font-size: 10pt;} "
      "QPushButton:hover{background: #e6f6ff; border-radius: 4px; font-size: 10pt;}"
    );
  }
  arrAddBreekFormDaysCheck_[5] = !arrAddBreekFormDaysCheck_[5];
}

void MainWindow::on_addBreekButton_clicked() {
  breeksData_t newElement;
  newElement.idOnServer = -1;
  newElement.text = ui->breekDescription->toPlainText();
  newElement.charStyleVector = ui->breekDescription->getCharStyleVector();
  for (int i = 0; i < DAYS_COUNT; ++i) {
    newElement.arrNEmoji[i] = ui->emojiButton->getEmojiIndex();
  }

  //server request
  QJsonObject json;
  json.insert("description", newElement.text);

  QJsonArray jArr;
  foreach(charStyle_t ch, newElement.charStyleVector) {
    QJsonObject jChar;
    jChar.insert("bold", ch.bold);
    jChar.insert("italic", ch.italic);
    jChar.insert("underline", ch.underline);
    jChar.insert("strike", ch.strike);
    jChar.insert("item", ch.item);
    jChar.insert("star", ch.star);
    jChar.insert("sColor", ch.sColor);
    jChar.insert("spellChecker", ch.spellChecker);
    jArr.push_back(jChar);
  }
  QJsonDocument jDoc;
  jDoc.setArray(jArr);
  json.insert("effects", QString(jDoc.toJson()));

  QString sConditions = "";
  for (int i = 0; i < DAYS_COUNT; ++i) {
    sConditions += QString::number(arrAddBreekFormDaysCheck_[i]);
  }
  bool isCovert;
  json.insert("conditions", sConditions.toShort(&isCovert, 2));

  qDebug() << "COND : " << sConditions;

  json.insert("states", QString("111111").toShort(&isCovert, 4));

  QJsonArray jArrEmojies;
  for (int i = 0; i < DAYS_COUNT; ++i) {
    QJsonObject jObj;
    jObj.insert("emojiNum", newElement.arrNEmoji[i]);
    jArrEmojies.push_back(jObj);
  }
  json.insert("emojies", jArrEmojies);

  json.insert("date", QDateTime(arrDays_[0].date).toMSecsSinceEpoch()); //first day of week

  QUrl url = QUrl(Network::serverUrl + Network::addBreeksLineUrl);
  QJsonDocument jsonDoc(json);

  server->sendPostRequestWithBearerToken(url , jsonDoc.toJson(), userData->getAccessToken());
  //---------

  emit sendBreekData(arrAddBreekFormDaysCheck_, newElement);
  setStyleAddBreeksForm();

  ui->emojiHub->showThis();
  ui->addBreekGB->hide();
}

void MainWindow::setBLIdOnServer(long id) {
  for (int i = 0; i < breeksZonesCount_; ++i ) {
    if (arrBreeksZones_[i].idOnServer == -1) {
      arrBreeksZones_[i].idOnServer = id;
      return;
    }
  }
}
