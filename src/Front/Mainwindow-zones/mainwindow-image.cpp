#include "Front/mainwindow.h"

#include <iostream>
#include <cstdlib>

bool MainWindow::openImageFromDisk(const QString& imageName)
{
  if ( QString::compare(imageName, QString()) != 0 ) {
    QImage image;
    bool valid = image.load(imageName);

		if (valid) {
			qDebug("IMAGE");
//			QByteArray ba;
//			QBuffer bu(&ba);
//			image.save(&bu, "PNG");
			QJsonObject json;
			json.insert("linkToImage", imageName);
			json.insert("date", QDateTime(arrDays_[0].date).toMSecsSinceEpoch());

			QUrl url = QUrl(Network::serverUrl + "/image/addImage");
			QJsonDocument jsonDoc(json);
			server->sendPostRequestWithBearerToken(url , jsonDoc.toJson(), userData->getAccessToken());

      return true;
    }
    else {
      qDebug() << "CAN'T OPEN IMAGE";
    }
  }
  return false;
}
void MainWindow::setImage(const QString& imageName)
{
  if (QString::compare(imageName, QString()) != 0) {
    QPixmap pix(imageName);
    pix = pix.scaledToWidth(ui->buttonImage->width(), Qt::SmoothTransformation);
    QIcon buttonIcon(pix);
    ui->buttonImage->setIcon(buttonIcon);
    ui->buttonImage->setIconSize(pix.rect().size());

    currentImageName_ = imageName;
  }
}

//image like button
void MainWindow::on_buttonImage_clicked()
{
  setImageBackgroundView(true);

  QString newImageName = QFileDialog::getOpenFileName(this, tr("Chose your image"), "", tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));

  if (openImageFromDisk(newImageName)) {
    setImage(newImageName);
    //writeDataToFileLastVisit();
  }

  setImageBackgroundView(false);
}

void MainWindow::setImageBackgroundView(bool status)
{
	QString stylesheet = "background-color: #e6f6ff; border-radius: 6px;"; //default
  if (status == true) {
		stylesheet = "background-color: #abdfff; border-radius: 6px;";
  }
	ui->buttonImage->setStyleSheet(stylesheet);
  ui->labelImageBackground->setStyleSheet(stylesheet);
}
