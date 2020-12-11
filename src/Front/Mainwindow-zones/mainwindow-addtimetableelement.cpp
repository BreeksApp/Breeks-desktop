#include "Front/mainwindow.h"

void MainWindow::setStyleAddTimetableElementForm()
{
	ui->addTimetableElementGb->setStyleSheet("QGroupBox{background: #cce4ff; border: 1px solid #C6C6C6; border-radius: 18px;}");

	indexCurrentTag_ = 0;
	ui->timetableElementTagColor->setStyleSheet("QPushButton{background: " + tag::ARR_COLORS[indexCurrentTag_] + "; border-radius: 6px;}");

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(10);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->timetableElementTagColor->setGraphicsEffect(effect);


	ui->timetableElementDescription->setFont(QFont("Helvetica", 12));
	ui->timetableElementDescription->setStyleSheet("background: #FFFFFF; border: 1px solid #F7F7F7; border-radius: 6px;"
																							 "padding-left:2;"
																							 "padding-top:2;"
																							 "padding-bottom:2;"
																							 "padding-right:2;");
	ui->timetableElementDescription->clear();
	ui->timetableElementDescription->clearCharStyleVector();

	for (int i = 0; i < DAYS_COUNT; ++i) {
		arrAddTimetableElementFormDaysCheck_[i] = false;
	}
	QString dayButtonStyleSheet = "QPushButton{background: #F7F7F7; border-radius: 4px;"
																"font-size: 10pt;}"
																"QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																"font-size: 10pt;}";

	ui->mnTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->mnTimetableElemnetButton->setFont(QFont("Helvetica"));
	ui->tuTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->tuTimetableElemnetButton->setFont(QFont("Helvetica"));
	ui->weTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->weTimetableElemnetButton->setFont(QFont("Helvetica"));
	ui->thTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->thTimetableElemnetButton->setFont(QFont("Helvetica"));
	ui->frTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->frTimetableElemnetButton->setFont(QFont("Helvetica"));
	ui->stTimetableElemnetButton->setStyleSheet(dayButtonStyleSheet);
	ui->stTimetableElemnetButton->setFont(QFont("Helvetica"));

	ui->mnTimetableElemnetButton->setGraphicsEffect(createShadow());
	ui->tuTimetableElemnetButton->setGraphicsEffect(createShadow());
	ui->weTimetableElemnetButton->setGraphicsEffect(createShadow());
	ui->thTimetableElemnetButton->setGraphicsEffect(createShadow());
	ui->frTimetableElemnetButton->setGraphicsEffect(createShadow());
	ui->stTimetableElemnetButton->setGraphicsEffect(createShadow());

	ui->addTimetableElementButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 20px; border: 0.2px solid #d7eba9; color: #ffffff; font-size: 12pt; font-weight: bold;} "
																							 "QPushButton:hover{background: #d2e9a0; border-radius: 20px; color: #FFFFFF; font-size: 12pt; font-weight: bold;}");

	//ui->timetableElementTimeStart->setFixedSize(50, 20);
	ui->timetableElementTimeStart->setStyleSheet("QTimeEdit{background: #F7F7F7; border-radius: 8px;}"
														"QTimeEdit::up-button {"
														"border-image:url(:/Images/Front/Images/caret-up.png);"
														"width: 15px;}"
														"QTimeEdit::down-button {"
														"border-image:url(:/Images/Front/Images/caret-down.png);"
														"width: 15px}");
	ui->timetableElementTimeStart->setGraphicsEffect(createShadow());

	//ui->timetableElementTimeEnd->setFixedSize(50, 20);
	ui->timetableElementTimeEnd->setStyleSheet("QTimeEdit{background: #F7F7F7; border-radius: 8px;}"
														"QTimeEdit::up-button {"
														"border-image:url(:/Images/Front/Images/caret-up.png);"
														"width: 15px;}"
														"QTimeEdit::down-button {"
														"border-image:url(:/Images/Front/Images/caret-down.png);"
														"width: 15px}");
	ui->timetableElementTimeEnd->setGraphicsEffect(createShadow());
}

void MainWindow::on_mnTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[0] == false) {
		ui->mnTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->mnTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[0] = !arrAddTimetableElementFormDaysCheck_[0];
}

void MainWindow::on_tuTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[1] == false) {
		ui->tuTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->tuTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[1] = !arrAddTimetableElementFormDaysCheck_[1];
}

void MainWindow::on_weTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[2] == false) {
		ui->weTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->weTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[2] = !arrAddTimetableElementFormDaysCheck_[2];
}

void MainWindow::on_thTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[3] == false) {
		ui->thTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->thTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[3] = !arrAddTimetableElementFormDaysCheck_[3];
}

void MainWindow::on_frTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[4] == false) {
		ui->frTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->frTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[4] = !arrAddTimetableElementFormDaysCheck_[4];
}

void MainWindow::on_stTimetableElemnetButton_clicked()
{
	if (arrAddTimetableElementFormDaysCheck_[5] == false) {
		ui->stTimetableElemnetButton->setStyleSheet("QPushButton{background: #b9de6f; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	else {
		ui->stTimetableElemnetButton->setStyleSheet("QPushButton{background: #F7F7F7; border-radius: 4px;"
																		 "font-size: 10pt;}"
																		 "QPushButton:hover{background: #e5f2c6; border-radius: 4px;"
																		 "font-size: 10pt;}");
	}
	arrAddTimetableElementFormDaysCheck_[5] = !arrAddTimetableElementFormDaysCheck_[5];
}

void MainWindow::on_buttonAdd_clicked()
{
	if (ui->addTimetableElementGb->isHidden() && timetableElementsCount_ < 300) {
		ui->addTimetableElementGb->show();
	}
	else if (!ui->addTimetableElementGb->isHidden()) {
		ui->addTimetableElementGb->hide();
	}
}

void MainWindow::on_timetableElementTagColor_clicked()
{
	indexCurrentTag_ = (indexCurrentTag_ + 1) % 6;
	ui->timetableElementTagColor->setStyleSheet("QPushButton{background: " + tag::ARR_COLORS[indexCurrentTag_] + "; border-radius: 6px;}");
}

void MainWindow::on_addTimetableElementButton_clicked()
{
	//check waste days and text
	bool tmpCond = false;
	for (int i = 0; i < 6; ++i) {
		tmpCond = tmpCond + arrAddTimetableElementFormDaysCheck_[i];
	}
	if (!tmpCond || ui->timetableElementDescription->toPlainText() == "") {
		return;
	}

	QString text = ui->timetableElementDescription->toPlainText();
	if (text.size() == 0) {
		return;
	}
	for (int i = 0; i < text.size(); ++i) {
		if (text[i] != ' ' && text[i] != '\t' && text[i] != '\n') {
			break;
		}
	}

	//all right
	elementData_t newElement;

	newElement.text = ui->timetableElementDescription->toPlainText();

	if ((ui->timetableElementTimeStart->time() < ui->timetableElementTimeEnd->time()) || (ui->timetableElementTimeEnd->time().toString() == "00:00:00")) {
		newElement.timeStart = ui->timetableElementTimeStart->time().toString();
		newElement.timeEnd = ui->timetableElementTimeEnd->time().toString();
	}
	else if (ui->timetableElementTimeStart == ui->timetableElementTimeEnd){
		newElement.timeStart = ui->timetableElementTimeStart->time().toString();
		newElement.timeEnd = "00:00:00";
	}
	else {
		//reverse time
		newElement.timeStart = ui->timetableElementTimeEnd->time().toString();
		newElement.timeEnd = ui->timetableElementTimeStart->time().toString();
	}

	newElement.tagColor = tag::ARR_COLORS[indexCurrentTag_];
	newElement.tagColorNum = indexCurrentTag_;
	newElement.charStyleVector = ui->timetableElementDescription->getCharStyleVector();
	newElement.idOnServer = -1;

	//server request
	QJsonObject json;
	json.insert("tagColorNum", newElement.tagColorNum);
	json.insert("mainText", newElement.text);

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

	json.insert("timeFrom", newElement.timeStart);
	json.insert("timeTo", newElement.timeEnd);

	QUrl url = QUrl(Network::serverUrl + Network::addTTElementUrl);

	for (int i = 0; i < DAYS_COUNT; ++i) {
		if (arrAddTimetableElementFormDaysCheck_[i]) {
			json.insert("date", QDateTime(arrDays_[i].date).toMSecsSinceEpoch());
			QJsonDocument jsonDoc(json);

			server->sendPostRequestWithBearerToken(url , jsonDoc.toJson(), userData->getAccessToken());
		}

	}
	//---------

	emit sendTimetableElementData(arrAddTimetableElementFormDaysCheck_, newElement);

	setStyleAddTimetableElementForm();
	ui->addTimetableElementGb->hide();
}


