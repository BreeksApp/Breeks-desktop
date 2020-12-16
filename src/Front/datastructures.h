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

struct lastRequest_t {
  QUrl url;
  QByteArray data;
  QString reqType;
};

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
	long date;
};

struct breeksData_t {
	long idOnServer;
	QString text;
	QVector<charStyle_t> charStyleVector;
	int conditions;
	int states;
	int arrNEmoji[6];
	long date;
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

struct note_t {
	QString text;
	QVector<charStyle_t> charStyleVector;
	int page;
	long date;
};

struct image_t {
	QString imageLocation;
	long date;
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
