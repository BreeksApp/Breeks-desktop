#ifndef ELEMENTTEMPLATE_H
#define ELEMENTTEMPLATE_H

#include "gentextedit.h"
#include "datastructures.h"

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimeEdit>

class ElementTemplate : public QGroupBox
{
  Q_OBJECT
public:
  explicit ElementTemplate(QGroupBox *parent = nullptr);

  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);

  void setText(QString text);
  void setTime(QString timeStart, QString timeEnd);
  void setPalette(const QPalette palette);

  void setDayAndElementIndex(const int dayIndex, const int elementIndex);
  void setElementIndex(const int index);

  QString getText() const;
  QPalette getColor() const;

private slots:
  void deleteElement();
  void changeTagColor();

private:
  const int ELEMENT_WIDTH = 245;
  const int ELEMENT_HEIGHT = 120;

  QPushButton *tagButton_;
  QPushButton *settingsButton_;
  QPushButton *deleteButton_;

  QGridLayout *elementLayout_;
	GenTextEdit *text_;
  QLineEdit *timeStart_;
  QLineEdit *timeEnd_;

  int dayIndex_;
  int elementIndex_;

  const int TAGS_COUNT = 6;
  tagElement_t arrTags_[6];

signals:
  void sendDayAndElementIndex(const int dayIndex, const int elementIndex);
  void sendDayAndElementIndexAndTagColor(const int, const int, const QPalette);

public slots:
};

#endif // ELEMENTTEMPLATE_H
