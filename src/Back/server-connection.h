#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>


namespace Network {
  class ServerConnection: public QObject {
    Q_OBJECT
  public:
    ServerConnection(QObject *parent = nullptr);
    ServerConnection(QString, QNetworkAccessManager *, QObject *parent = nullptr);

    QString getServerUrl();
    void setServerUrl(QString);

    QString resolveAccessTokenFromRequest();
    QString resolveRefreshTokenFromRequest();

    QNetworkReply * sendRegisterRequest(QString, QString, QString);
    void sendAuthRequest(QString, QString);

    void sendBreeksDataToServer();

  private:
    QString serverUrl_;
    QNetworkAccessManager * networkAccessManager_;

  public slots:
    void onfinish(QNetworkReply *);

  signals:
    void initSecretData(QString, QString);
  };


  // ===================
  // API Properties
  //====================
  const QString authUrl = "/auth/signin";
}

#endif // SERVERCONNECTION_H
