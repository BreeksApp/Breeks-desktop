#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include "filesystem.h"
#include "datastructures.h"

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

class GenTextEdit : public QTextEdit
{
  Q_OBJECT
public:
	explicit GenTextEdit(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event);

  //for work with file system, definition in filesystem.cpp
  void readFromDB(const int currentFile);
  void writeToDB(const int currentFile);

  void setNumberCurrentFile(const int n);
  int getNumberCurrentFile();

  void clearCharStyleVector();

  QVector<charStyle_t> getCharStyleVector();
  //

  //for work with char styles
  enum charStyle {
    Normal,    // = 0
    Bold,      // = 1
    Italic,    // = 2
    Underline, // = 3
		Strike,    // = 4
		Item,      // = 5
		Star			 // = 6
	};
	using iterator = QVector< charStyle_t >::iterator;

//in ...-get-set.cpp
    void fillCharStyleVector(int cursorPos, int count, charStyle_t ch);
    void fillCharStyleVector(charStyle_t ch);
  int getCharStyle(const int index) const;
  void setCharCounter(const int value);
	int getCharCounter() const;

//in ...-keys-realization.cpp
	void setCharStyle(const int style);
	void addTodoList();

    static void detailsSetCharStyle(charStyle_t& ch, const int style = charStyle::Normal);
    static void detailsSetCharStyle(charStyle_t& ch, const int style, int& status);
    static void detailsSetBoolByStatus(bool& a, int& status);

    void fillCharsAndSetText(QString text, const QJsonArray jArr);
public slots:
  void recieveUsername(const QString);

private:
//it is data storage
	QString username_;
  int nCurrentFile_;

  QJsonObject note1_;
  QJsonObject note2_;
  QJsonObject note3_;
  QJsonObject note4_;
  QJsonObject note5_;
  QJsonObject note6_;
 //

	const int MAX_COUNT_CHAR_ = 999; //fix count of chars in the one note
  int charCounter_;

  QVector< charStyle_t > charStyleVector_; //storrage of font style status of every char
  const QVector< QChar > AVAILABLE_CHARS_ = {'!', '?', '.', ',', ';', ':', '\"', '\'', '&', '*', '@', '~', '`', '#','$', '^', '/',
        '%', '(', ')', '[', ']', '{', '}', '|', '\\', '<', '>', '-', '_', '+', '='};

	const QString pointSign_ = "•";
	const QString minusSign_ = "-";
	const QString warrningSign_ = "❐";

	const int ITEM_LENGTH = 4;
	const int TAB_LENGTH = 4;

//keys-realization.cpp
	void deleteRealization(const Qt::KeyboardModifiers kmModifiers, const QTextCursor::MoveOperation whereMove,
				int& cursorPos, const int blindSpot, const int a = 0);
	void addTodoList(const QString itemSign);
	void tabRealization(int& cursorPos);

//details.cpp - smth like namespace details
	void detailsEraseSelectedText(int& cursorPos);

	//if cursor in the middle of item and we are going to push Bs/del we should delete full item
	void detailsCheckItemPosInDeleting(int& cursorPos, const bool isBS, Qt::KeyboardModifiers& mod);
	//if we write smth in the middle of item, we won't have the item it will become a regular text
	void detailsCheckItemAndCanselStatus(int& cursorPos);
	void detailsCheckSelectionAndItem(int& cursorPos); //to unite common checkers

	void detailsSetCharStyleByNeighbours(charStyle_t& ch, const int index);
};

#endif // TEXT_EDIT
