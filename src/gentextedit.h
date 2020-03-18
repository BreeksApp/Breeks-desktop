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

  void setNumberCurrentFile(int n);
  int getNumberCurrentFile();
  //

  //for work with char styles
  enum fontStyleValue_t {
    Normal,    // = 0
    Bold,      // = 1
    Italic,    // = 2
    Underline, // = 3
		Strike,    // = 4
		Item,      // = 5
		Star			 // = 6
  };
  using iterator = QVector< fontStyleValue_t >::iterator;

  void fillFontStyleVector(int cursorPos, int count = 1, int style = 0);
  int getCharStyle(int index) const;
  void setCharCounter(int value);
  int getCharCounter() const;

  void setFontStyle(int style);
	void addTodoList();
  //
public slots:
  void recieveUsername(const QString);

private:
//it is data storage
	QString username_;

  int nCurrentFile_;
	NoteInfo textInfoForWrite_;
	QString textInfoForRead_;

  QJsonObject note1_;
  QJsonObject note2_;
  QJsonObject note3_;
  QJsonObject note4_;
  QJsonObject note5_;
  QJsonObject note6_;
 //

  const int MAX_COUNT_CHAR_ = 1111; //fix count of chars in the one note
  int charCounter_;

  QVector< fontStyleValue_t > fontStyleVector_; //storrage of font style status of every char
  const QVector< QChar > AVAILABLE_CHARS_ = {'!', '?', '.', ',', ';', ':', '\"', '\'', '&', '*', '@', '~', '`', '#','$', '^', '/',
        '%', '(', ')', '[', ']', '{', '}', '|', '\\', '<', '>', '-', '_', '+', '='};

	const QString pointSign_ = "•";
	const QString minusSign_ = "-";
	const QString warrningSign_ = "❐";

	const int ITEM_LENGTH = 4;
	const int TAB_LENGTH = 5;

//keys-realization
	void deleteRealization(Qt::KeyboardModifiers kmModifiers, QTextCursor::MoveOperation whereMove,
				int cursorPos, int blindSpot, int a = 0);
	void addTodoList(const QString itemSign);

//details... - smth like namespace details
	void detailsEraseSelectedText(int& cursorPos);
	//if cursor in the middle of item and we are going to push Bs/del we should delete full item
	void detailsCheckItemPosInDeleting(int& cursorPos, bool isBS, Qt::KeyboardModifiers& mod);
	//if we write smth in the middle of item, we won't have the item it will become a regular text
	void detailsCheckItemAndCanselStatus(int cursorPos);

	void detailsCheckSelectionAndItem(int cursorPos); //to unite common checkers
};

#endif // TEXT_EDIT
