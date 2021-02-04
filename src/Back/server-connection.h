#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include "Back/secret-data.h"
#include "Front/datastructures.h"

namespace Network {
  class ServerConnection: public QObject
  {
    Q_OBJECT
  public:
    ServerConnection(QObject *parent = nullptr);
    ServerConnection(QNetworkAccessManager *, Network::UserData * , QObject *parent = nullptr);

    Network::UserData * getUserData();

    QString resolveAccessTokenFromRequest();
    QString resolveRefreshTokenFromRequest();

    // ====================================
    //  Auth requests below:
    // ====================================
    void sendAuthRequest(const QString&, const QString&);
    void sendPostRefreshRequest(const QString&, const QString&);

    // ====================================
    //  POST data to server methods below:
    // ====================================
    void sendPostRequest(const QUrl&, const QByteArray&);
    void sendPostRequestWithBearerToken(const QUrl&, const QByteArray&, const QString&); // !

    // ====================================
    //  PUT data to server methods below:
    // ====================================
    void sendPutRequestWithBearerToken(const QUrl&, const QByteArray&, const QString&); // !

    // ====================================
    //  DELETE data from server methods below:
    // ====================================
    void sendDeleteRequestWithBearerToken(const QUrl&, const QString&); // !

    // ====================================
    //  GET data from server methods below:
    // ====================================    
    void sendGetRequestWithBearerToken(const QUrl&, const QString&); // !

  private:
    QNetworkAccessManager * networkAccessManager_;
    Network::UserData * userData_;
    QList<lastRequest_t> listOfLastRequests_;
    bool mutex = false;

  public slots:
    void onfinish(QNetworkReply *);

  signals:
    void initSecretData(QString, QString, QString);
    void initTEidOnServer(long);
    void initBLidOnServer(long);
    void loginReply(bool);
    void sendBreeksLinesToGUI(const QList<breeksData_t>&);
    void sendTTElementsToGUI(const QList<elementData_t>&);
    void sendNoteToGUI(note_t&);
    void sendImageToGUI(const image_t&);

    // this signal is emitted whenever we want to (re-)load all data of the week
    void initWeekData(const QString&);

    void logout();

    void sendDataToRfrshFile(const QString&, const QString&);
  };


  // ===================
  //  API Properties
  //====================
  const QString serverUrl = "https://breeks.cf";
  const QString registrationUrl = "/user/registration";
  const QString authUrl = "/auth/signin";
  const QString refreshUrl = "/auth/refresh";

  // TimetableElements
  const QString addTTElementUrl = "/timetableElement/addTimetableElement";
  const QString editTTElementUrl = "/timetableElement/editTimetableElement";
  const QString deleteTTElementUrl = "/timetableElement/deleteTimetableElement";
  const QString getTTElementsForDayUrl = "/timetableElement/listOfTimetableElements/";

  // BreeksLines
  const QString addBreeksLineUrl = "/breeks/addLine";
  const QString editBreeksLineUrl = "/breeks/editLine";
  const QString deleteBreeksLineUrl = "/breeks/deleteLine";
  const QString getAllLinesInWeekUrl = "/breeks/listOfLines/";

  // Notes
  const QString addNoteUrl = "/note/addNote";
  const QString editNoteUrl = "/note/editNote";
  const QString getNoteByDateAndPageUrl = "/note/getNoteByDateAndPage/";

  // Image
  const QString addImageUrl = "/image/addImage";
  const QString getImageUrl = "/image/getImage/";
}

#endif // SERVERCONNECTION_H
