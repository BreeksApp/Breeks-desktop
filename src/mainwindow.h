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

#include "ui_mainwindow.h"
#include "elementtemplate.h"
#include "textnewelement.h"
#include "datastructures.h"
#include "effects.hpp"
#include "breek.h"
#include "loginform.h"
#include "daywidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void mousePressEvent( QMouseEvent* event );

  LoginForm *loginForm_;

  //files of timetable
  //void writeElementsDataToFile(const int index);
  //void readElementsDataFromFile(const int index);

public slots:
//to underline image
  void setImageBackgroundView(bool);

//slot to set data which was pronted and selected by user in AddElement form for Time Table Zone
  void recieveTimeTableZoneData(bool *, const int, elementData_t);

//slot to set data which was pronted and selected by user in AddElement form for Breeks Zone
  void recieveBreeksZoneData(bool *, const int, breeksData_t);

  void recieveDayAndElementIndex(const int, const int);
  void recieveDayAndElementIndexAndTagColor(const int, const int, const QPalette);
  void recieveUsername();
  void recieveMimeData(const elementData_t, const QPixmap);

  void moveBreek(int, int, bool);
  void dropElement(const int, const int, const int, const elementData_t);
  void sendElementsHeight(const int, const int);

private slots:
//note
  //buttons to work with text
	void on_buttonMakeBold_clicked();
  void on_buttonMakeItalic_clicked();
  void on_buttonMakeUnderline_clicked();
  void on_buttonMakeStrike_clicked();
  void on_buttonAddTodoList_clicked();
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

//slot to fill original breeks positions in layout when they have been added on it(to avoid "position problem")
  void fillBreeksPositions(int);

signals:
  void sendUsername(const QString);

private:
  Ui::MainWindow *ui;

//last visit data about image and page in notes
  const QString fileLastVisitName_ = "fileLastVisit.txt";
  QFile fileLastVisit_;
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

  void writeElementsDataToFile(const int index);
  void readElementsDataFromFile(const int index);
//

//work with effects
  QPalette paletteSelectedPageButton_;
  QPalette paletteDefaultElement_;

  void setAllElementsEffects(); //this method calls in mainWindow constructor

  void setAllElementsColor(); //set color for all elements
  void setAllElementsShadow(); //set shadow
//

//for work with NOTE
  void noteMakePageButtonSelectable(QPushButton *button);
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
    QLabel *labelDate;
    QLabel *labelElementsCount;

    QScrollArea *scrollArea;
    DayWidget *widgetDay;
    QVBoxLayout *helpLayout;
    QVBoxLayout *layoutDayElements;

    int groupBoxElementsHeight;
    int elementsCount;
  };

  void buildTimeTable();
  void setDaysStructure();
  void setDayInfo();
  void allocateMemoryForDays();
  void initializeDaysParameters();

  const int WORK_ZONE_BIG_WIDGET_WIDTH = 2000;
  const int BREEKS_DESCRIPTION_ZONE_BIG_WIDGET_WIDTH = 305;

  const int DAY_WIDTH_ = 260;
  const int ELEMENT_HEIGHT_ = 130;

  const int DAYS_COUNT = 6;
  day_t arrDays_[6];


  int addNewElementToArray(const elementData_t& newElement, const int index);
  void addNewElementToLayout(const int index, const int newElementIndex);
//------------------

                        //---------BREEKSZONE---------

  const int MOVE_DURATION = 500;

  struct breeksZone_t {
    QGroupBox *breeksZoneGroupBox;
    QGridLayout *breeksZoneLayout;
    Breek *arrBreeks[6];
    QVector<QPoint> positionsOfBreeks;
    bool flagIfPosFilled;

    QGroupBox *breeksDescriptionGroupBox;
    QGridLayout *breeksDescriptionLayout;
    TextNewElement *breekText;

    QPushButton *buttonBreekDays;
    QPushButton *arrBreeksZoneDays[6];
    QPushButton *buttonDelete;

    int zoneIndex;

  };

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
};

#endif // MAINWINDOW_H
