#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "QString"
#include "QPalette"

struct CharStyle {
  bool bold;
  bool italic;
  bool underline;
  bool strikeOut;
  bool item;
  bool star;
  QString sColor;
};

struct ElementData {
  QString text;
  QPalette palette;
  QString timeStart;
  QString timeEnd;
};

struct BreeksData {
  QString text;
  int nEmoji;
};

struct tagElement {
  bool condition;
  QPalette pallete;
};
namespace tag {
  const int N_COLORS = 6;
  const QColor ARR_COLORS[6] = {"#0000FF", "#FF3366", "#FFFF66", "#CC66FF", "#ECEAEC", "#66FF66"};
}

struct NoteInfo {
  int charCount;
  QString charState;
  QString text;
};


#endif // DATASTRUCTURES_H
