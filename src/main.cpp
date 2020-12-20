#include "Front/mainwindow.h"
#include <QApplication>
#include "Back/server-connection.h"
#include <Back/secret-data.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QString path = QDir::current().path() + "/eeicon.ico"; //Release
  QIcon icon(path);
  a.setWindowIcon(icon);
  MainWindow w;

  return a.exec();
}
