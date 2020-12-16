#include "Front/mainwindow.h"
#include "Front/GeneralTextEdit/notemark.h"

QUrl MainWindow::createGetNoteUrl(const int numPage)
{
  QString date = "";
  date.setNum(QDateTime(arrDays_[0].date).toMSecsSinceEpoch());
  qDebug() << "Notes date in MS: " << date;
  QString sNumPage = "";
  sNumPage.setNum(numPage);

  return QUrl(Network::serverUrl + Network::getNoteByDateAndPageUrl + date + "/" + sNumPage);
}

QUrl MainWindow::createPostNoteUrl()
{
  return QUrl(Network::serverUrl + Network::addNoteUrl);
}

QByteArray MainWindow::createJsonForSendingNote(int page)
{
  QJsonObject json;

  QString noteText = ui->note->toPlainText();
  json.insert("text", noteText);

	qDebug() << "PUTREQUEST" << noteText;

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

  return jsonDoc.toJson();
}

void MainWindow::changeNotePage(const int nButton, NoteMark * buttonPage)
{
  //  ui->note->writeToDB(ui->note->getNumberCurrentFile());

//  QTimer timer;
//  timer.setInterval(10000);
//  timer.setSingleShot(true);

//  QEventLoop loop;

//  QNetworkReply * reply =
//    server->sendPostRequestWhenSwitchingNotePages(
//          createPostNoteUrl(),
//          createJsonForSendingNote(ui->note->getNumberCurrentFile()),
//          userData->getAccessToken()
//    );

//  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//  QObject::connect(&timer, &QTimer::timeout, reply, &QNetworkReply::abort);

//  timer.start();
//  loop.exec();

//  if (reply->isFinished() && reply->error() == QNetworkReply::NoError) {
    noteMakePageButtonSelectable(buttonPage);
    noteChangePage(nButton);

    writeDataToFileLastVisit();
//  }
//  else {
//    // GUI warning "no connection with server"
//  }

//  reply->deleteLater();
}

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

//  ui->note->readFromDB(ui->note->getNumberCurrentFile());

  server->sendGetRequestWithBearerToken(createGetNoteUrl(n), userData->getAccessToken());
}

//-------------------------BUTTONS-------------------------
void MainWindow::on_buttonPage1_clicked()
{
  changeNotePage(1, ui->buttonPage1);
}
void MainWindow::on_buttonPage2_clicked()
{
  changeNotePage(2, ui->buttonPage2);
}
void MainWindow::on_buttonPage3_clicked()
{
  changeNotePage(3, ui->buttonPage3);
}
void MainWindow::on_buttonPage4_clicked()
{
  changeNotePage(4, ui->buttonPage4);
}
void MainWindow::on_buttonPage5_clicked()
{
  changeNotePage(5, ui->buttonPage5);
}
void MainWindow::on_buttonPage6_clicked()
{
  changeNotePage(6, ui->buttonPage6);
}


void MainWindow::sendPostRequestNote(int page)
{
  server->sendPostRequestWithBearerToken(createPostNoteUrl(), createJsonForSendingNote(page),
                                         userData->getAccessToken());
}
