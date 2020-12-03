#include "Back/server-connection.h"

#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Network::ServerConnection::ServerConnection(QObject *parent):
  QObject(parent)
{

}

Network::ServerConnection::ServerConnection(QString serverUrl, QNetworkAccessManager * networkAccessManager, QObject *parent):
  QObject(parent),
  serverUrl_(serverUrl),
  networkAccessManager_(networkAccessManager)
{

}

QString Network::ServerConnection::getServerUrl() {
  return serverUrl_;
}

void Network::ServerConnection::setServerUrl(QString serverUrl) {
  this->serverUrl_ = serverUrl;
}

void Network::ServerConnection::sendAuthRequest(QString username, QString password) {
  QNetworkRequest request(QUrl(serverUrl_ + Network::authUrl));

  QJsonObject json;
  json.insert("username", username);
  json.insert("password", password);
  QJsonDocument jsonDoc(json);
  QByteArray jsonData= jsonDoc.toJson();
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));

  connect(networkAccessManager_,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));

  networkAccessManager_->post(request, jsonData);
}

void Network::ServerConnection::sendBreeksDataToServer() {

}

void Network::ServerConnection::onfinish(QNetworkReply * reply) {
  const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
  const QJsonObject json = doc.object();
  emit initSecretData(json.value("token").toString(), json.value("tokenRefresh").toString());
}
