#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <Qt>
#include <QKeyEvent>

class NoteTextEdit : public QTextEdit
{
  Q_OBJECT
public:
  explicit NoteTextEdit(QWidget *parent = nullptr);

  void keyPressEvent(QKeyEvent *event);

  //for work with file system, definition in filesystem.cpp
  void readFromFile();
  void writeToFile();
  void setNumberCurrentFile(int n);
  int getNumberCurrentFile() const;
  //

  //for work with char styles
  enum fontStyleValue_t {
    Normal,    // = 0
    Bold,      // = 1
    Italic,    // = 2
    Underline, // = 3
		Strike,    // = 4
		Item       // = 5
  };
  using iterator = QVector< fontStyleValue_t >::iterator;

  void fillFontStyleVector(int cursorPos, int count = 1, int style = 0);
  int getCharStyle(int index) const;
  void setCharCounter(int value);
  int getCharCounter() const;

  void setFontStyle(int style);
  void addTodoList();
  //
private:
//it is data storage
  void readFromFile(QFile &file);
  void writeToFile(QFile &file);

  int nCurrentFile_;

  const QString file1Name_ = "noteStorage_1.txt";
  const QString file2Name_ = "noteStorage_2.txt";
  const QString file3Name_ = "noteStorage_3.txt";
  const QString file4Name_ = "noteStorage_4.txt";
  const QString file5Name_ = "noteStorage_5.txt";
  const QString file6Name_ = "noteStorage_6.txt";

  QFile file1_;
  QFile file2_;
  QFile file3_;
  QFile file4_;
  QFile file5_;
  QFile file6_;
 //

  const int MAX_COUNT_CHAR_ = 1111; //fix count of chars in the one note
  int charCounter_;

  QVector< fontStyleValue_t > fontStyleVector_; //storrage of font style status of every char
  const QVector< QChar > AVAILABLE_CHARS_ = {'!', '?', '.', ',', ';', ':', '\"', '\'', '&', '*', '@', '~', '`', '#','$', '^', '/',
        '%', '(', ')', '[', ']', '{', '}', '|', '\\', '<', '>', '-', '_', '+', '='};
  const QString pointSign_ = "•";

  void detailsEraseCharsOfSelectedText(int& cursorPos);
	void detailsDeleteBackspaceRealization(Qt::KeyboardModifiers kmModifiers, QTextCursor::MoveOperation whereMove,
        int cursorPos, int blindSpot, int a = 0);
};

#endif // NOTE_H
