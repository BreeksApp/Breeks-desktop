#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "QString"
#include "QPalette"

struct charStyle_t {
  bool bold;
  bool italic;
  bool underline;
  bool strike;
  bool item;
  bool star;
  //QString sColor;
};

struct elementData_t {
  QString text;
  QPalette palette;
  QString timeStart;
  QString timeEnd;
};

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
  int charCount;
  QString charState;
  QString text;
};


#endif // DATASTRUCTURES_H
