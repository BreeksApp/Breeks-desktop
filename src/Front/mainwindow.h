#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>
#include <QVector>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QGraphicsDropShadowEffect>
#include <QDate>
#include <QScrollArea>
#include <set>
#include <QDrag>

#include <Front/MainElements/calendarweek.h>
#include <Front/MainElements/deletebreekszonebutton.h>
#include <Front/MainElements/descriptionzonedaybutton.h>

#include <Back/secret-data.h>
#include <Back/server-connection.h>

#include "ui_mainwindow.h"
#include "Front/MainElements/elementtemplate.h"
#include "Front/GeneralTextEdit/textnewelement.h"
#include "datastructures.h"
#include "effects.hpp"
#include "Front/MainElements/breek.h"
#include "Front/MainElements/daywidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

	void mousePressEvent(QMouseEvent *event);

  //files of timetable
  //void writeElementsDataToFile(const int index);
  //void readElementsDataFromFile(const int index);

public slots:
//to underline image
  void setImageBackgroundView(bool);

//slot to set data which was pronted and selected by user in AddElement form for Time Table Zone
        void recieveTimeTableZoneData(bool *, elementData_t, bool withRequest = true);

//slot to set data which was pronted and selected by user in AddElement form for Breeks Zone
	void recieveBreeksZoneData(bool *, breeksData_t, int * states = nullptr);

	void recieveUsername();

	void recieveDayAndElementIndex(const int, const int, bool);
	void recieveDayAndElementIndexAndTagColor(const int, const int, const int);
  void recieveMimeData(const elementData_t, const QPixmap);
	void recieveTimetableElementDayAndElemIndexAndTime(int, int, QString, QString);
	void recieveTimetableDayAndElementIndexAndText(int, int, QString, QVector<charStyle_t>);

	void setDayInfo(QDate = QDate::currentDate());
	void changeWeek(qint64);

	void dropNoChanges();
	void dropElement(const int, const int, const int, const elementData_t);
	void enterDayArea(int);
	void leaveDayArea(int);
	void defineDayMoveFrom(int, QString);
	void mousePressedByDragElement();

	void sendElementsHeight(const int, const int);
	void changeElementsLayoutHeight(const int, const int);

	void moveBreek(int, int, bool);

	void logout();

private slots:
// load week from server
	void clearAndInitWeekData(const QString&);

	void initBreeksLines(const QList<breeksData_t>&);
	void initTTElements(const QList<elementData_t>&);
	void initNote(note_t&);
	void initImage(const image_t&);
//timetable
	void updateTTElementIdOnServer(int, int, long);
	void sendPutRequestTte(int, int);
//note
	void sendPostRequestNote(int);

  //buttons to change pages
  void on_buttonPage1_clicked();
  void on_buttonPage2_clicked();
  void on_buttonPage3_clicked();
  void on_buttonPage4_clicked();
  void on_buttonPage5_clicked();
  void on_buttonPage6_clicked();
//
  void on_buttonImage_clicked();

//adding new elements
  void on_buttonAdd_clicked();
	void on_buttonAdd_2_clicked();

//slot to fill original breeks positions in layout when they have been added on it(to avoid "position problem")
  void fillBreeksPositions(int);
        void changeBreeksZoneLilDayState(int, int, int, bool withRequest = true);
	void setBreeksZoneLilDayShadow(int, int, bool);
	void setBreeksDescriptionZoneFocus(int, bool);
	void descriptionZoneDayDobleClick(int, int);
	void changeLilDayState(int, int);

	void deleteBreeksZone(int);

//ADD BREEKS
	void on_mnBreekButton_clicked();
	void on_tuBreekButton_clicked();
	void on_weBreekButton_clicked();
	void on_thBreekButton_clicked();
	void on_frBreekButton_clicked();
	void on_stBreekButton_clicked();

	void on_addBreekButton_clicked();

	void setBLIdOnServer(long);
	void sendPutRequestBl(int);

//ADD TIMETABLE ELEMENT
	void on_mnTimetableElemnetButton_clicked();
	void on_tuTimetableElemnetButton_clicked();
	void on_weTimetableElemnetButton_clicked();
	void on_thTimetableElemnetButton_clicked();
	void on_frTimetableElemnetButton_clicked();
	void on_stTimetableElemnetButton_clicked();

	void on_timetableElementTagColor_clicked();

	void on_addTimetableElementButton_clicked();

	void on_infoButton_clicked();
	void infoGBEnter();
	void infoGBLeave();

	void on_reg_clicked();

	void on_login_clicked();
	void loginReply(bool);

	void on_prevWeekButton_clicked();

	void on_nextWeekButton_clicked();

	void on_logoutButton_clicked();

signals:
  void sendUsername(const QString);
	void sendBreekData(bool *, breeksData_t);
	void sendTimetableElementData(bool *, elementData_t);

private:
  Ui::MainWindow *ui;

	Network::UserData *userData;
	Network::ServerConnection *server;

//last visit data about image and page in notes
  const QString fileLastVisitName_ = "fileLastVisit.txt";
  QFile fileLastVisit_;

  void initWeekData(const QString&);
  void clearWeekData();
  void deleteBreeksZoneClientOnly(int);
  // delete TTElements - recieveDayAndElementIndex
  void deleteNotes(); // clear the current page and load the current page
  void deleteImage(); // set default image

  void setStatesFromFileLastVisit();
  void writeDataToFileLastVisit();
//

//last visit data about timetable
  const QString fileMonName_ = "timetableMonStorage.txt";
  const QString fileTueName_ = "timetableTueStorage.txt";
  const QString fileWedName_ = "timetableWedStorage.txt";
  const QString fileThuName_ = "timetableThuStorage.txt";
  const QString fileFriName_ = "timetableFriStorage.txt";
  const QString fileSatName_ = "timetableSatStorage.txt";

  QFile fileMon_;
  QFile fileTue_;
  QFile fileWed_;
  QFile fileThu_;
  QFile fileFri_;
  QFile fileSat_;

  QMimeData mimeData_;
  QPixmap dragElement_;

  using iterType = QVector<elementData_t>::iterator;
  QVector<elementData_t> arrDaysData_[6]; //conteiner with elements data by days
//

//work with effects
  QPalette paletteSelectedPageButton_;
  QPalette paletteDefaultElement_;

  void setAllElementsEffects(); //this method calls in mainWindow constructor

  void setAllElementsColor(); //set color for all elements
  void setAllElementsShadow(); //set shadow
//

//for work with NOTE
  QUrl createGetNoteUrl(const int);
  QUrl createPostNoteUrl();
  QByteArray createJsonForSendingNote(int);
  void changeNotePage(const int, NoteMark*);
  void noteMakePageButtonSelectable(NoteMark *button);
  void noteMakePageButtonSelectable(int nPage);
  void noteChangePage(const int n);
//

//information about IMAGE
  QString currentImageName_;
  const QString defaultImageName_ = ":/Images/Images/sharik.jpg";

  bool openImageFromDisk(const QString& imageName);
  void setImage(const QString& imageName);
//

//-------------------------ABOUT WORK ZONE-------------------------
  void setWorkZone();
  int bigWidgetHeight_;

	void setShadow(QWidget *);

                   //---------TIMETABLE---------
  enum eDay {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
  };

  enum charStyle {
    Normal,    // = 0
    Bold,      // = 1
    Italic,    // = 2
    Underline, // = 3
		Strike,    // = 4
		Item,      // = 5
		Star			 // = 6
	};

  struct day_t {
    QGroupBox *groupBoxDay;
    QVBoxLayout *layoutFullDay;

    QHBoxLayout *layoutDayInfo;
		QDate date;
    QLabel *labelDate;
    QLabel *labelElementsCount;

    QScrollArea *scrollArea;
    DayWidget *widgetDay;
    QVBoxLayout *helpLayout;
    QVBoxLayout *layoutDayElements;

    int groupBoxElementsHeight;
    int elementsCount;
		int elementsScaledCount;
  };

  void buildTimeTable();
  void setDaysStructure();
	//void setDayInfo();
  void allocateMemoryForDays();
  void initializeDaysParameters();

  const int WORK_ZONE_BIG_WIDGET_WIDTH = 2000;
  const int BREEKS_DESCRIPTION_ZONE_BIG_WIDGET_WIDTH = 305;

  const int DAY_WIDTH_ = 260;
	const int ELEMENT_HEIGHT_ = 115;

	const int DAYS_COUNT = 6;
	day_t arrDays_[6];

	int timetableElementsCount_;

	QDate currentDate_;
	int iCurrentDay_;
	QTimer *timer_;

	bool isElementDrag_;
	QString oldStyle_;

  int addNewElementToArray(const elementData_t& newElement, const int index, bool withRequest);
  void addNewElementToLayout(const int index, const int newElementIndex);

	void moveTimetableElement();
//------------------

                        //---------BREEKSZONE---------

  const int MOVE_DURATION = 350;

  struct breeksZone_t {
		long idOnServer;

    QGroupBox *breeksZoneGroupBox;
    QGridLayout *breeksZoneLayout;
    Breek *arrBreeks[6];
    QVector<QPoint> positionsOfBreeks;
    bool flagIfPosFilled;

    QGroupBox *breeksDescriptionGroupBox;
    QGridLayout *breeksDescriptionLayout;
		TimetableTextEdit *breekText;

    QPushButton *buttonBreekDays;
		DescriptionZoneDayButton *arrBreeksZoneDays[6];
		DeleteBreeksZoneButton *buttonDelete;

    int zoneIndex;
  };

	QTimer *breeksLineTimer_;

  QVector<breeksZone_t> arrBreeksZones_;

  const int EMOJI_COUNT = 11;
  QString arrEmojiNormal[11];
  QString arrEmojiCompleted[11];
  QString arrEmojiDroped[11];
  QString arrEmojiProcess[11];

	void setEmoji(const QString emoji);

  void allocateMemoryForBreeks(breeksZone_t *breeksZone);
  void setBreeksZone(breeksZone_t *breeksZone);
	void setDaysConnect(breeksZone_t *breeksZone);
  void buildBreeksDescriptionZone();
  void delay(int);

  QPoint descreptionZoneGeometry_;
  int breeksZonesCount_;

  QWidget *bigWidgetInWorkZone_;
  QWidget *bigWidgetInBreeksDescriptionZone_;

  QScrollArea *workZoneScrollArea_;
  QGridLayout *workZoneLayout_;

  QScrollArea *breeksDescriptionZoneScrollArea_;
  QGridLayout *breeksDescriptionZoneLayout_;
//------------------

	QGraphicsDropShadowEffect* createShadow();

	QVector<CalendarWeek*> calendarWeeks;

//--------- ADD BREEK-LINE---------
	void setStyleAddBreeksForm();
	bool arrAddBreekFormDaysCheck_[6];
//--------- Add TIMETABLE ELEMENT -
	void setStyleAddTimetableElementForm();
	bool arrAddTimetableElementFormDaysCheck_[6];
	int indexCurrentTag_;

// INFO BUTTONS
	void setInfoButtonsStyle();
	void setInfoButtonColor(QString sColor);

	const int TAGS_COUNT = 6;
	tagElement_t arrTags_[6];
	int infoButtonColorNum;

//CALENDAR
	QScrollArea *calendarScrollArea;
};

#endif // MAINWINDOW_H
