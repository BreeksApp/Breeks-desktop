#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QtSql>
#include <QFileInfo>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
  Q_OBJECT

public:
  explicit LoginForm(QWidget *parent = nullptr);
  ~LoginForm();

signals:
  void firstWindow();
  void sendUsername(const QString);

private slots:

  void on_loginButton_clicked();

private:
  Ui::LoginForm *ui;
  QSqlDatabase mydb;
};

#endif // LOGINFORM_H
