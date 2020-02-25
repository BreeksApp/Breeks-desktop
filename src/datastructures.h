#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "QString"
#include "QPalette"

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


#endif // DATASTRUCTURES_H
