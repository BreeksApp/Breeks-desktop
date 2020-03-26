#include "mainwindow.h"

void MainWindow::setStatesFromFileLastVisit()
{
  if (!fileLastVisit_.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "FILE LAST_VISIT OPENING CRASHED";
  }
  QString text = fileLastVisit_.readAll();
  QTextStream stream(&text);

  int nLastNotePage = 1;
  int iTmp = 0;
  stream >> iTmp;
  if (iTmp >= 1 && iTmp <= 6) {
    nLastNotePage = iTmp;
  }
  noteChangePage(nLastNotePage);

  QString imageName = defaultImageName_;
  QString sTmp = "";
  stream >> sTmp;
  if (QString::compare(sTmp, defaultImageName_) != 0) {
    if (openImageFromDisk(sTmp)) {
      imageName = sTmp;
    }
  }
  setImage(imageName);

  fileLastVisit_.flush();
  fileLastVisit_.close();
}

void MainWindow::writeDataToFileLastVisit()
{
  if (!fileLastVisit_.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
    qDebug() << "FILE LAST_VISIT OPENING CRASHED";
  }
  QTextStream out(&fileLastVisit_);

    const int nNotePage = ui->note->getNumberCurrentFile();
  out << nNotePage << " ";

    out << currentImageName_;

    fileLastVisit_.flush();
  fileLastVisit_.close();
}
