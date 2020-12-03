//VIEW / MODEL

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
#include <QTimeEdit>

struct charStyle_t {
  bool bold;
  bool italic;
  bool underline;
  bool strike;
  bool item;
	bool spellChecker;
  bool star;
  QString sColor;
};
namespace colors { //#ade9ff is breeks color
	const QString nocolor = "";
	const QString green = "#bfffb5";
	const QString lavender = "#dcbeee";
	const QString marina = "#bcd9ef";
	const QString orange = "#ffc88e";
	const QString red = "#ff9d95";
	const QString white = "#ffffff";
};

struct elementData_t {
  QString text;
  QString tagColor;
  QString timeStart;
  QString timeEnd;
  //QString color;
  QVector<charStyle_t> charStyleVector;
};

struct breeksData_t {
  QString text;
	QVector<charStyle_t> charStyleVector;
	int arrNEmoji[6];
};

struct tagElement_t {
  bool condition;
	QString sColor;
};
namespace tag {
  const int N_COLORS = 6;
	const QString ARR_COLORS[6] = {"#0000FF", "#FF3366", "#FFFF66",
																"#CC66FF", "#ECEAEC", "#66FF66"};
}

struct textInfo_t {
  QJsonArray jArr;
  QString text;
};

enum Directions
{
	DOWNSIDE,
	UPSIDE
};
enum Conditions
{
	RED,
	GREY_FOREGROUND,
	GREY_BACKGROUND,
	GREEN,
	YELLOW,
	SHADOW
};



#endif // DATASTRUCTURES_H
