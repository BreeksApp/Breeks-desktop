#include "Back/server-connection.h"

#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Network::ServerConnection::ServerConnection(QObject *parent):
  QObject(parent)
{

}

Network::ServerConnection::ServerConnection(QNetworkAccessManager * networkAccessManager, QObject *parent):
  QObject(parent),
  networkAccessManager_(networkAccessManager)
{
  connect(networkAccessManager_,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
}

void Network::ServerConnection::sendAuthRequest(QString username, QString password) {
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

void Network::ServerConnection::sendPostRequestWithBearerToken(QUrl url, QByteArray data, QString token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	networkAccessManager_->post(request, data);
}

void Network::ServerConnection::sendPutRequestWithBearerToken(QUrl url, QByteArray data, QString token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.size()));
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	networkAccessManager_->put(request, data);
}

void Network::ServerConnection::sendDeleteRequestWithBearerToken(QUrl url, QString token)
{
	qDebug() << url.toString();

	QNetworkRequest request(url);
	auto tokenHeader = QString("Bearer %1").arg(token);
	request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

	networkAccessManager_->deleteResource(request);
}

void Network::ServerConnection::sendBreeksDataToServer() {

}

QNetworkReply *Network::ServerConnection::getBreeksLinesFromServer(long timeInMs, QString token)
{
  QString sTimeInMs;
  sTimeInMs.setNum(timeInMs);

  QNetworkRequest request(getAllLinesInWeekUrl + sTimeInMs);
  auto tokenHeader = QString("Bearer %1").arg(token);
  request.setRawHeader(QByteArray("Authorization"), tokenHeader.toUtf8());

  networkAccessManager_->get(request);
}

void Network::ServerConnection::onfinish(QNetworkReply * reply) {
  const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
  const QJsonObject json = doc.object();

	qDebug() << reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
	qDebug() << doc;

	if (json.value("token").toString() != "" && json.value("tokenRefresh").toString() != "") {
		emit initSecretData(json.value("token").toString(), json.value("tokenRefresh").toString());
	}
	else if (json.value("id").toInt() != 0) {
		emit initTEidOnServer(json.value("id").toInt());
	}
}
