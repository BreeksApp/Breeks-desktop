#include "Back/secret-data.h"

#include <QDebug>

Network::UserData::UserData(QObject *parent) :
  QObject(parent)
{

}

Network::UserData::UserData(QString accessToken, QString refreshToken, QObject *parent) :
  QObject(parent),
  accessToken_(accessToken),
  refreshToken_(refreshToken)
{

}

QString Network::UserData::getAccessToken() {
  return accessToken_;
}

void Network::UserData::setAccessToken(QString accessToken) {
  this->accessToken_ = accessToken;
}

QString Network::UserData::getRefreshToken() {
  return refreshToken_;
}

void Network::UserData::setRefreshToken(QString refreshToken) {
  this->refreshToken_ = refreshToken;
}

void Network::UserData::initSecretData(QString accessToken, QString refreshToken)
{
  this->accessToken_ = accessToken;
  this->refreshToken_ = refreshToken;

  qDebug() << accessToken_ << refreshToken_;
}
