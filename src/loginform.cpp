#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
  ui->setupUi(this);

  mydb = QSqlDatabase::addDatabase("QSQLITE"); //Choose driver for work work with SqlLite DB
  mydb.setDatabaseName("/Users/ruby/Desktop/breeks/Breeks-App/src/BreeksInfo.db"); // Set Path to our DB file

  if (!mydb.open()) {
    qDebug()<<"Failed to open DataBase";
  }
}

LoginForm::~LoginForm()
{
  delete ui;
}

void LoginForm::on_loginButton_clicked()
{
  if (!mydb.isOpen()) {
    qDebug() << "Failed";
    return;
  }

  QString username = ui->usernameLineEdit->text();
  QString password = ui->passwordLineEdit->text();

  QSqlQuery qry;
  if (qry.exec("SELECT * FROM Employee WHERE Username='"+username+"' AND Password='"+password+"'")) {  //make a query to our DB to find a required user
    int count = 0;
    while (qry.next()) {
      count ++;
    }
    if (count==1) {
      this->close();
      emit firstWindow();
    }
    else {
      ui->infoLabe->setText("Wrong username or password");
    }
  }
}
