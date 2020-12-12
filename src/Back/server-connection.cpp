#include "Back/server-connection.h"

#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Network::ServerConnection::ServerConnection(QObject *parent):
  QObject(parent)
{

}

Network::ServerConnection::ServerConnection(QNetworkAccessManager * networkAccessManager,
                                            Network::UserData * userData, QObject *parent):
  QObject(parent),
  networkAccessManager_(networkAccessManager),
  userData_(userData)
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

void Network::ServerConnection::sendPostRequestWithBearerToken(const QUrl & url, const QByteArray & data,
							       const QString & token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	networkAccessManager_->post(request, data);
}

void Network::ServerConnection::sendBreeksDataToServer()
{

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

	networkAccessManager_->put(request, data);
}

void Network::ServerConnection::sendDeleteRequestWithBearerToken(const QUrl & url, const QString & token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	networkAccessManager_->deleteResource(request);
}

void Network::ServerConnection::sendGetRequestWithBearerToken(const QUrl & url, const QString & token)
{
  QNetworkRequest request(url);
  auto tokenHeader = QString("Bearer %1").arg(token);
  request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

  networkAccessManager_->get(request);
}

void Network::ServerConnection::onfinish(QNetworkReply * reply)
{
  const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
  const QJsonObject json = doc.object();

//  qDebug() << doc;

  bool ok = true;
  int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&ok);
  QString url = reply->url().toString();

  // 403 - if accessToken has expired or is invalid
  if (ok && statusCode == 403) {
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
  if (ok && statusCode == 401) {
    // Close mainwindow and redirect to auth form
    return;
  }

  // 404 - endpoint not found
  if (ok && statusCode == 404) {
    qDebug() << "URL " << url << " not found: " << statusCode << '\n';
    return;
  }

  if (ok && statusCode >= 500) {
    // Server internal error
    qDebug() << "Server internal error: " << statusCode << '\n';
    return;
  }

  if (ok && statusCode == 304) {
    qDebug() << "URL " << url << " not modified: " << statusCode << '\n';
    return;
  }

  if (json.value("userName").toString() != "" && json.value("token").toString() != "" &&
    json.value("tokenRefresh").toString() != "") {
    emit initSecretData(json.value("userName").toString(), json.value("token").toString(),
                        json.value("tokenRefresh").toString());
  }
  else if (json.value("elementId").toInt() != 0) {
    qDebug("ELEMENT");
    emit initTEidOnServer(json.value("elementId").toInt());
  }
  else if (json.value("lineId").toInt() != 0) {
    qDebug() << "LINE " << json.value("lineId").toInt();
    emit initBLidOnServer(json.value("lineId").toInt());
  }
  else if (url.contains(getAllLinesInWeekUrl)) {
      qDebug() << "url success";
    // парсим jsonarray в ответе
  }
  else if (url.contains(getTTElementsForDayUrl)) {
    // парсим jsonarray в ответе
  }
  else if (url.contains(getNoteByDateAndPageUrl)) {
    // парсим jsonvalue в ответе
  }
  else if (url.contains(getImageUrl)) {
    // парсим jsonvalue в ответе
  }
}
