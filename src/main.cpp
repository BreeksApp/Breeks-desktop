#include "Front/mainwindow.h"
#include "loginform.h"
#include <QApplication>
#include "Back/server-connection.h"
#include <Back/secret-data.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
	w.loginForm_->show();

  return a.exec();
}
