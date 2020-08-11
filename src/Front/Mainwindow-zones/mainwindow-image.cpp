#include "Front/mainwindow.h"

bool MainWindow::openImageFromDisk(const QString& imageName)
{
  if ( QString::compare(imageName, QString()) != 0 ) {
    QImage image;
    bool valid = image.load(imageName);
    if (valid) {
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
  QString stylesheet = "background-color: #e6f6ff"; //default
  if (status == true) {
    stylesheet = "background-color: #abdfff";
  }
  ui->labelImageBackground->setStyleSheet(stylesheet);
}
