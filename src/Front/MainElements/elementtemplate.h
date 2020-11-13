#ifndef ELEMENTTEMPLATE_H
#define ELEMENTTEMPLATE_H

#include "Front/GeneralTextEdit/TimeTable/timetabletextedit.h"
#include "Front/datastructures.h"

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimeEdit>
#include <QApplication>
#include <QDrag>


class ElementTemplate : public QGroupBox
{
  Q_OBJECT
public:
  explicit ElementTemplate(QGroupBox *parent = nullptr);

  void mousePressEvent( QMouseEvent* event );
  void mouseMoveEvent(QMouseEvent*event);

  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);

	int getWidth();

  void setText(QString text, const QVector<charStyle_t>& charArr);
  void setTime(QString timeStart, QString timeEnd);
	void setTagColor(const QString sColor);

  void setDayAndElementIndex(const int dayIndex, const int elementIndex);
  void setElementIndex(const int index);

  QVector<charStyle_t> getCharStyleVector();

  QString getText() const;
	QString getTagColor() const;

private slots:
  void deleteElement();
  void changeTagColor();
	void scaleTextEdit();

private:

	const int ELEMENT_WIDTH = 245;
	int ELEMENT_HEIGHT = 100;
	int TEXT_HEIGHT = 62;

  QPoint dragStartPosition_;

	bool isScaled_;

  QPushButton *tagButton_;
	QString tagColor_;

	QPushButton *scaleButton_;
  QPushButton *deleteButton_;

  QGridLayout *elementLayout_;
  TimetableTextEdit *text_;
	QLineEdit *timeStart_;
  QLineEdit *timeEnd_;

  int dayIndex_;
  int elementIndex_;

  const int TAGS_COUNT = 6;
  tagElement_t arrTags_[6];

signals:
  void sendDayAndElementIndex(const int dayIndex, const int elementIndex);
	void sendDayAndElementIndexAndTagColor(const int, const int, const QString);
  void sendMimeData(const elementData_t, const QPixmap);
	void dropNoChanges(); //for drop after drag beyond dayWidget
	void deleteItem(int, int);
	void defineDayMoveFrom(int, QString);
	void changeElementsLayoutHeight(const int, const int);
};

#endif // ELEMENTTEMPLATE_H
