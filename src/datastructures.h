#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "QString"
#include "QPalette"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>
#include <QtSql>

struct charStyle_t {
  bool bold;
  bool italic;
  bool underline;
  bool strike;
  bool item;
  bool star;
  QString sColor;
};
namespace colors {
	const QString black = "#000000";
	const QString red = "#FF3366";
};

struct elementData_t {
  QString text;
  QPalette palette;
  QString timeStart;
  QString timeEnd;
  QString color;
  QVector<charStyle_t> charStyleVector;
};
\
struct breeksData_t {
  QString text;
  int nEmoji;
};

struct tagElement_t {
  bool condition;
  QPalette pallete;
};
namespace tag {
  const int N_COLORS = 6;
  const QColor ARR_COLORS[6] = {"#0000FF", "#FF3366", "#FFFF66", "#CC66FF", "#ECEAEC", "#66FF66"};
}

struct textInfo_t {
  QJsonArray jArr;
  QString text;
};



#endif // DATASTRUCTURES_H
