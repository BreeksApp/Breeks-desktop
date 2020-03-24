#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <Qt>
#include <QKeyEvent>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>
#include <QtSql>
#include "gentextedit.h"
#include "datastructures.h"

class filesystem
{
public:
  filesystem();
  static QJsonObject readTextEdidFromDB(const int currentFile);
  static void writeTextEditToDB(textInfo_t &info, const int currentFile);

private:
  static QString getDataFromDB();
	static void pushDataToDB(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &notes,
													 QJsonObject &note, textInfo_t &info, const int currentFile);

  static void parseDataBase(QJsonObject &notes);

  static QJsonObject note1_;
  static QJsonObject note2_;
  static QJsonObject note3_;
  static QJsonObject note4_;
  static QJsonObject note5_;
  static QJsonObject note6_;
};

#endif // FILESYSTEM_H
