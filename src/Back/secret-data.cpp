#include "Back/secret-data.h"

#include <QDebug>

Network::UserData::UserData(QObject *parent) :
  QObject(parent),
  username_(""),
  accessToken_(""),
  refreshToken_("")
{

}

Network::UserData::UserData(QString username, QString accessToken,
                            QString refreshToken, QObject *parent) :
  QObject(parent),
  username_(username),
  accessToken_(accessToken),
  refreshToken_(refreshToken)
{

}

QString Network::UserData::getUsername()
{
  return username_;
}

void Network::UserData::setUsername(QString username)
{
  this->username_ = username;
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

void Network::UserData::initSecretData(QString username, QString accessToken, QString refreshToken)
{
  this->username_ = username
  this->accessToken_ = accessToken;
  this->refreshToken_ = refreshToken;

  qDebug() << accessToken_ << refreshToken_;
}
