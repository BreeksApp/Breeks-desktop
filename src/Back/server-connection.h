#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>


namespace Network {
  class ServerConnection: public QObject
  {
    Q_OBJECT
  public:
    ServerConnection(QObject *parent = nullptr);
    ServerConnection(QNetworkAccessManager *, QObject *parent = nullptr);

    QString resolveAccessTokenFromRequest();
    QString resolveRefreshTokenFromRequest();

    QNetworkReply * sendRegisterRequest(QString, QString, QString);
    void sendAuthRequest(QString, QString);
    void sendPostRequestWithBearerToken(QUrl url, QByteArray data, QString token);
    void sendPutRequestWithBearerToken(QUrl url, QByteArray data, QString token);
    void sendDeleteRequestWithBearerToken(QUrl url, QString token);

    void sendBreeksDataToServer();

    // ====================================
    //  GET data from server methods below:
    // ====================================
    QNetworkReply * getBreeksLinesFromServer(long, QString);
    QNetworkReply * getTTElementsFromServer(long, QString);
    QNetworkReply * getNotesFromServer(long, short, QString);
    QNetworkReply * getImageLinkFromServer(long, QString);

  private:
    QNetworkAccessManager * networkAccessManager_;

  public slots:
    void onfinish(QNetworkReply *);

  signals:
    void initSecretData(QString, QString);
    void initTEidOnServer(long);
  };


  // ===================
  //  API Properties
  //====================
  const QString serverUrl = "http://localhost:8080";
  const QString authUrl = "/auth/signin";

  // TimetableElements
  const QString addTTElementUrl = "/timetableElement/addTimetableElement";
  const QString editTTElementUrl = "/timetableElement/editTimetableElement";
  const QString deleteTTElementUrl = "/timetableElement/deleteTimetableElement";
  const QString getTTElementsForDayUrl = "/timetableElement/listOfTimetableElements/";

  // BreeksLines
  const QString getAllLinesInWeekUrl = "/breeks/listOfLines/";

  // Notes
  const QString getNoteByDateAndPageUrl = "/note/getNoteByDateAndPage/";

  // Image
  const QString getImageUrl = "/image/getImage/";
}

#endif // SERVERCONNECTION_H
