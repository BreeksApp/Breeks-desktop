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
	long idOnServer;
  QString text;
  QString tagColor;
	int tagColorNum;
  QString timeStart;
  QString timeEnd;
  //QString color;
  QVector<charStyle_t> charStyleVector;
};

struct breeksData_t {
	long idOnServer;
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
	const QString ARR_COLORS[6] = {"#ffa542", "#FF6666", "#81c4ff",
																"#cAcAcA", "#beff5a", "#CC66FF"};
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
