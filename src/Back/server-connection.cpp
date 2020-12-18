#include "Back/server-connection.h"

#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "Back/utils/utils.h"

Network::ServerConnection::ServerConnection(QObject *parent):
  QObject(parent),
  listOfLastRequests_(QList<lastRequest_t>())
{

}

Network::ServerConnection::ServerConnection(QNetworkAccessManager * networkAccessManager,
                                            Network::UserData * userData, QObject *parent):
  QObject(parent),
  networkAccessManager_(networkAccessManager),
  userData_(userData),
  listOfLastRequests_(QList<lastRequest_t>())
{
  connect(networkAccessManager_,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
  connect(this,SIGNAL(initSecretData(QString, QString, QString)),
          userData_,SLOT(initSecretData(QString, QString, QString)));
}

Network::UserData * Network::ServerConnection::getUserData()
{
  return userData_;
}

void Network::ServerConnection::sendAuthRequest(const QString & username, const QString & password)
{
	QNetworkRequest request(QUrl(Network::serverUrl + Network::authUrl));

  QJsonObject json;
  json.insert("username", username);
  json.insert("password", password);
  QJsonDocument jsonDoc(json);
  QByteArray jsonData= jsonDoc.toJson();
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));

  networkAccessManager_->post(request, jsonData);
}

void Network::ServerConnection::sendPostRefreshRequest(const QString & username, const QString & refreshToken)
{
  QNetworkRequest request(QUrl(Network::serverUrl + Network::refreshUrl));

  QJsonObject json;
  json.insert("username", username);
  json.insert("refreshToken", refreshToken);
  QJsonDocument jsonDoc(json);
  QByteArray jsonData= jsonDoc.toJson();
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));

	networkAccessManager_->post(request, jsonData);
}

void Network::ServerConnection::sendPostRequest(const QUrl& url, const QByteArray & data)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));

	networkAccessManager_->post(request, data);
}

void Network::ServerConnection::sendPostRequestWithBearerToken(const QUrl & url, const QByteArray & data,
							       const QString & token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	if (!mutex) listOfLastRequests_.append({url, data, "PostWithToken"});

	networkAccessManager_->post(request, data);
}

void Network::ServerConnection::sendPutRequestWithBearerToken(const QUrl & url, const QByteArray & data,
							      const QString & token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	if (!mutex) listOfLastRequests_.append({url, data, "PutWithToken"});

	networkAccessManager_->put(request, data);
}

void Network::ServerConnection::sendDeleteRequestWithBearerToken(const QUrl & url, const QString & token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	if (!mutex) listOfLastRequests_.append({url, QByteArray(), "DeleteWithToken"});

	networkAccessManager_->deleteResource(request);
}

void Network::ServerConnection::sendGetRequestWithBearerToken(const QUrl & url, const QString & token)
{
  QNetworkRequest request(url);
  auto tokenHeader = QString("Bearer %1").arg(token);
  request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

  networkAccessManager_->get(request);

  if (!mutex) {
    for (auto request : listOfLastRequests_) {
      if (request.reqType == "GetWithToken") return;
    }
    listOfLastRequests_.append({QUrl(), QByteArray(), "GetWithToken"});
  }
}

void Network::ServerConnection::onfinish(QNetworkReply * reply)
{
  const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
  const QJsonObject json = doc.object();

  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

  QString url = reply->url().toString();
  qDebug() << statusCode;
  // 400 Bad Request if the user types an invalid email when registering
  if (statusCode == 400) {
    qDebug() << "Bad email " << url;
    return;
  }

  // 403 - if accessToken has expired or is invalid
  if (statusCode == 403) {
    QString username = userData_->getUsername();
    QString refreshToken = userData_->getRefreshToken();
    if (username != "" && refreshToken != "") {
      sendPostRefreshRequest(userData_->getUsername(), userData_->getRefreshToken());
    }
    else {
      // Warning "wrong username or password"
    }

    return;
  }

  // 401 - if refreshToken has expired or is invalid
  if (statusCode == 401) {      
    if (url.contains(authUrl)) {
      emit loginReply(false);
      return;
    }
    listOfLastRequests_.clear();
    emit logout();
    return;
  }

  // 404 - endpoint not found
  if (statusCode == 404) {
    qDebug() << "URL " << url << " not found: " << statusCode << '\n';
    return;
  }

  if (statusCode >= 500) {
    // Server internal error
    qDebug() << "Server internal error: " << statusCode << '\n';
    return;
  }

  // code activation exception falls here as well
  if (statusCode == 304) {
    qDebug() << "URL " << url << " not modified: " << statusCode << '\n';
    return;
  }

  // if we don't get any data from reply
  // (only for Note and Image, line and TTE returns empty list)
  if (statusCode == 204) {
    qDebug() << "URL " << url << " no content: " << statusCode << '\n';
    return;
  }

  if (url.contains(authUrl)) {
      QString username = json.value("userName").toString();
      QString token = json.value("token").toString();
      QString tokenRefresh = json.value("tokenRefresh").toString();

      if (username != "" && token != "" && tokenRefresh != "") {
        emit initSecretData(username, token, tokenRefresh);
        emit loginReply(true);
        emit initWeekData(token);
      }
  }
  else if (url.contains(refreshUrl)) {
    QString username = json.value("userName").toString();
    QString token = json.value("token").toString();
    QString tokenRefresh = json.value("tokenRefresh").toString();

    if (username != "" && token != "" && tokenRefresh != "") {
      emit initSecretData(username, token, tokenRefresh);
      mutex = true;
      for (auto request : listOfLastRequests_) {
        if (request.reqType == "PostWithToken") {
          sendPostRequestWithBearerToken(request.url, request.data, token);
        }
        else if (request.reqType == "PutWithToken") {
          sendPutRequestWithBearerToken(request.url, request.data, token);
        }
        else if (request.reqType == "DeleteWithToken") {
          sendDeleteRequestWithBearerToken(request.url, token);
        }
        else if (request.reqType == "GetWithToken") {
          emit initWeekData(token);
        }
      }
      mutex = false;
    }
  }
  else if (url.contains(addTTElementUrl)) {
      if (json.value("elementId").toInt() != 0) {
          qDebug("ELEMENT");
          emit initTEidOnServer(json.value("elementId").toInt());
        }
  }
  else if (url.contains(addBreeksLineUrl)) {
      if (json.value("lineId").toInt() != 0) {
          qDebug() << "LINE " << json.value("lineId").toInt();
          emit initBLidOnServer(json.value("lineId").toInt());
        }
  }
  else if (url.contains(getAllLinesInWeekUrl)) {

    // парсим jsonarray в ответе
      QJsonArray jsonArrBLines = doc.array();
      if (jsonArrBLines.isEmpty()) {
        return;
      }
      else {
        QList<breeksData_t> listOfBreeksLines = QList<breeksData_t>();

        for (auto jsonIterator : jsonArrBLines) {
            QJsonObject json = jsonIterator.toObject();

            long date = json.value("date").toVariant().toDate().startOfDay().toMSecsSinceEpoch();

            QJsonArray jsonEffectsArr = jsonArrayFromString(json.value("effects").toString());

            QVector<charStyle_t> charStyleVector = QVector<charStyle_t>();
            if (!jsonEffectsArr.isEmpty()) {
              createCharStyleVector(charStyleVector, jsonEffectsArr);
            }

            int arrNEmoji[6] = {0,0,0,0,0,0};
            QJsonValue jsonEmojies = json.value("emojies");
            if (jsonEmojies.isArray()) {
              QJsonArray jsonEmojiesArr = jsonEmojies.toArray();
              createArrNEmoji(arrNEmoji, 6, jsonEmojiesArr);
            }

            breeksData_t breeksLine = {
              json.value("lineId").toInt(),
              json.value("description").toString(),
              charStyleVector,
              json.value("conditions").toInt(),
              json.value("states").toInt(),
              {0,0,0,0,0,0},
              date
            };
            for (unsigned i = 0; i < 6; ++i) breeksLine.arrNEmoji[i] = arrNEmoji[i];

            listOfBreeksLines.append(breeksLine);
        }

        emit sendBreeksLinesToGUI(listOfBreeksLines);
      }
  }
  else if (url.contains(getTTElementsForDayUrl)) {

    // парсим jsonarray в ответе
      QJsonArray jsonArrTTElements = doc.array();
      if (jsonArrTTElements.isEmpty()) {
        return;
      }
      else {
        QList<elementData_t> listOfTTElements = QList<elementData_t>();

        for (auto jsonIterator : jsonArrTTElements) {
            QJsonObject json = jsonIterator.toObject();

            long date = json.value("date").toVariant().toDate().startOfDay().toMSecsSinceEpoch();
            date += 86400000;

            QJsonArray jsonEffectsArr = jsonArrayFromString(json.value("effects").toString());

            QVector<charStyle_t> charStyleVector = QVector<charStyle_t>();
            if (!jsonEffectsArr.isEmpty()) {
              createCharStyleVector(charStyleVector, jsonEffectsArr);
            }

            int tagColorNum = json.value("tagColorNum").toInt();
            elementData_t ttelement = {
              json.value("elementId").toInt(),
              json.value("mainText").toString(),
              tag::ARR_COLORS[tagColorNum],
              tagColorNum,
              json.value("timeFrom").toString(),
              json.value("timeTo").toString(),
              charStyleVector,
              date
            };

            listOfTTElements.append(ttelement);
        }

        emit sendTTElementsToGUI(listOfTTElements);
      }
  }
  else if (url.contains(getNoteByDateAndPageUrl)) {
    // парсим jsonvalue в ответе
      if (json.isEmpty()) {
        return;
      }
      else {
          long date = json.value("date").toVariant().toDate().startOfDay().toMSecsSinceEpoch();

          QJsonArray jsonEffectsArr = jsonArrayFromString(json.value("effects").toString());

          QVector<charStyle_t> charStyleVector = QVector<charStyle_t>();
          if (!jsonEffectsArr.isEmpty()) {
            createCharStyleVector(charStyleVector, jsonEffectsArr);
          }

          note_t note = {
            json.value("text").toString(),
            charStyleVector,
            json.value("page").toInt(),
            date
          };

          emit sendNoteToGUI(note);
      }
  }
  else if (url.contains(getImageUrl)) {

    // парсим jsonvalue в ответе
      if (json.isEmpty()) {
        return;
      }
      else {
          long date = json.value("date").toVariant().toDate().startOfDay().toMSecsSinceEpoch();

          image_t image = {
            json.value("linkToImage").toString(),
            date
          };

          emit sendImageToGUI(image);
      }
  }

  if (!mutex) listOfLastRequests_.clear();
}
