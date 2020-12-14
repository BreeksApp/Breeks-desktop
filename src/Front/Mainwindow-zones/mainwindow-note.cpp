#include "Front/mainwindow.h"
#include "Front/GeneralTextEdit/notemark.h"

void MainWindow::noteMakePageButtonSelectable(NoteMark *button)
{
  //set previous button in default state
  switch (ui->note->getNumberCurrentFile()) {
    case 1 :
			ui->buttonPage1->setDefaultStyle();
      break;
    case 2 :
			ui->buttonPage2->setDefaultStyle();
			break;
    case 3 :
			ui->buttonPage3->setDefaultStyle();
			break;
    case 4 :
			ui->buttonPage4->setDefaultStyle();
			break;
    case 5 :
			ui->buttonPage5->setDefaultStyle();
			break;
    case 6 :
			ui->buttonPage6->setDefaultStyle();
			break;
  }
  //make selected
 button->setSelectableStyle();
}

void MainWindow::noteMakePageButtonSelectable(int nPage)
{
  switch (nPage) {
    case 1 :
			ui->buttonPage1->setSelectableStyle();
			break;
    case 2 :
			ui->buttonPage2->setSelectableStyle();
			break;
    case 3 :
			ui->buttonPage3->setSelectableStyle();
			break;
    case 4 :
			ui->buttonPage4->setSelectableStyle();
			break;
    case 5 :
			ui->buttonPage5->setSelectableStyle();
			break;
    case 6 :
			ui->buttonPage6->setSelectableStyle();
			break;
  }
}

void MainWindow::noteChangePage(const int n)
{
  ui->note->setNumberCurrentFile(n);
  ui->note->clear();
  ui->note->readFromDB(ui->note->getNumberCurrentFile());
}

//-------------------------BUTTONS-------------------------
void MainWindow::on_buttonPage1_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 1;
  noteMakePageButtonSelectable(ui->buttonPage1);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage2_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 2;
  noteMakePageButtonSelectable(ui->buttonPage2);
  noteChangePage(nButton);

  writeDataToFileLastVisit();

}
void MainWindow::on_buttonPage3_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 3;
  noteMakePageButtonSelectable(ui->buttonPage3);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage4_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 4;
  noteMakePageButtonSelectable(ui->buttonPage4);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage5_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 5;
  noteMakePageButtonSelectable(ui->buttonPage5);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}
void MainWindow::on_buttonPage6_clicked()
{
  ui->note->writeToDB(ui->note->getNumberCurrentFile());

  const int nButton = 6;
  noteMakePageButtonSelectable(ui->buttonPage6);
  noteChangePage(nButton);

  writeDataToFileLastVisit();
}


void MainWindow::sendPutRequestNote(int page)
{
	QJsonObject json;

	QString noteText = ui->note->toPlainText();
	json.insert("text", noteText);

	QJsonArray jArr;
	foreach(charStyle_t ch, ui->note->getCharStyleVector()) {
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

	json.insert("page", page);
	json.insert("date", QDateTime(arrDays_[0].date).toMSecsSinceEpoch());

	QJsonDocument jsonDoc(json);

	QUrl url = QUrl(Network::serverUrl + Network::editNoteUrl);
	server->sendPutRequestWithBearerToken(url , jsonDoc.toJson(), userData->getAccessToken());
}
