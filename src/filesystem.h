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

  static QJsonArray readTimeTableFromDB(const int index);
  static void writeTimeTableToDB(QJsonArray &JDayElements, const int index);

private:
  static QString getDataFromDB(QString queryStr);

  static void pushDataToDBTextEdit(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &notes, QJsonObject &note,
                           textInfo_t &info, const int currentFile);
  static void pushDataToDBTimeTable(QJsonDocument &jDoc, QJsonObject &jObject, QJsonObject &timeTable,
                                    QJsonArray &JDayElements, const int index);

  static void parseDataBaseTextEdit(QJsonObject &notes);
  static void parseDataBaseTimeTable(QJsonObject &timeTable);

  static QJsonObject note1_;
  static QJsonObject note2_;
  static QJsonObject note3_;
  static QJsonObject note4_;
  static QJsonObject note5_;
  static QJsonObject note6_;
};

#endif // FILESYSTEM_H
