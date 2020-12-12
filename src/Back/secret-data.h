#ifndef SECRETDATA_H
#define SECRETDATA_H

#include <QObject>
#include <QString>

namespace Network {
  class UserData : public QObject {
    Q_OBJECT
  public:
    UserData(QObject *parent = nullptr);
    UserData(QString, QString, QString, QObject *parent = nullptr);

    QString getUsername();
    void setUsername(QString);

    QString getAccessToken();
    void setAccessToken(QString);

    QString getRefreshToken();
    void setRefreshToken(QString);

  public slots:
    void initSecretData(QString, QString, QString);

  private:
    QString username_;
    QString accessToken_;
    QString refreshToken_;
  };
}

#endif // SECRETDATA_H
