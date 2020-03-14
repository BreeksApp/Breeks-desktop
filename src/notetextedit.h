#ifndef NOTE_H
#define NOTE_H

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
#include "filesystem.h"
#include "datastructures.h"

class NoteTextEdit : public QTextEdit
{
  Q_OBJECT
public:
  explicit NoteTextEdit(QWidget *parent = nullptr);

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
  int nCurrentFile_;

  NoteInfo noteInfoForWrite_;

  QJsonObject note1_;
  QJsonObject note2_;
  QJsonObject note3_;
  QJsonObject note4_;
  QJsonObject note5_;
  QJsonObject note6_;

  QString username_;
  QString noteInfoForRead_;

 //

  const int MAX_COUNT_CHAR_ = 1111; //fix count of chars in the one note
  int charCounter_;

  QVector< fontStyleValue_t > fontStyleVector_; //storrage of font style status of every char
  const QVector< QChar > AVAILABLE_CHARS_ = {'!', '?', '.', ',', ';', ':', '\"', '\'', '&', '*', '@', '~', '`', '#','$', '^', '/',
        '%', '(', ')', '[', ']', '{', '}', '|', '\\', '<', '>', '-', '_', '+', '='};

	const QString pointSign_ = "•";
	const QString minusSign_ = "-";

	const int ITEM_LENGTH = 4;
	const int TAB_LENGTH = 5;

	void addTodoList(const QString itemSign);

  void detailsEraseCharsOfSelectedText(int& cursorPos);
	void detailsDeleteBackspaceRealization(Qt::KeyboardModifiers kmModifiers, QTextCursor::MoveOperation whereMove,
        int cursorPos, int blindSpot, int a = 0);
	void detailsItemCheckInDeleting(int& cursorPos, bool isBS, Qt::KeyboardModifiers& mod);
	void detailsItemCheckAndCanselStatus(int cursorPose);
};

#endif // NOTE_H
