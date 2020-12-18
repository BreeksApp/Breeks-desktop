QT       += core gui sql qml quick quickwidgets network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = eeicon.ico

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Back/FileSystem/databaseIO.cpp \
    Back/FileSystem/filesystem.cpp \
    Back/secret-data.cpp \
    Back/server-connection.cpp \
    Back/utils/utils.cpp \
    Front/Dictionary/russiandictionary.cpp \
    Front/GeneralTextEdit/TimeTable/timetable-write-read.cpp \
    Front/GeneralTextEdit/TimeTable/timetabletextedit.cpp \
    Front/GeneralTextEdit/gentextedit-details.cpp \
    Front/GeneralTextEdit/gentextedit-get-set.cpp \
    Front/GeneralTextEdit/gentextedit-keys-realization.cpp \
    Front/GeneralTextEdit/gentextedit-write-read.cpp \
    Front/GeneralTextEdit/gentextedit.cpp \
    Front/GeneralTextEdit/notemark.cpp \
    Front/GeneralTextEdit/textnewelement.cpp \
    Front/GeneralTextEdit/undoredotext.cpp \
    Front/MainElements/EmojiHub/emojibutton.cpp \
    Front/MainElements/addbreekgb.cpp \
    Front/MainElements/addbuttonhover.cpp \
    Front/MainElements/addtimetableelementgb.cpp \
    Front/MainElements/breek.cpp \
    Front/MainElements/calendarweek.cpp \
    Front/MainElements/daywidget.cpp \
    Front/MainElements/deletebreekszonebutton.cpp \
    Front/MainElements/deletetimetableelementbutton.cpp \
    Front/MainElements/demobreek.cpp \
    Front/MainElements/descriptionzonedaybutton.cpp \
    Front/MainElements/elementtemplate.cpp \
    Front/MainElements/imagehover.cpp \
    Front/MainElements/infogb.cpp \
    Front/MainElements/timeedit.cpp \
    Front/Mainwindow-zones/mainwidnow-timetable.cpp \
    Front/Mainwindow-zones/mainwindow-addbreek.cpp \
    Front/Mainwindow-zones/mainwindow-addelement.cpp \
    Front/Mainwindow-zones/mainwindow-addtimetableelement.cpp \
    Front/Mainwindow-zones/mainwindow-breekszone.cpp \
    Front/Mainwindow-zones/mainwindow-effects.cpp \
    Front/Mainwindow-zones/mainwindow-image.cpp \
    Front/Mainwindow-zones/mainwindow-infobuttons.cpp \
    Front/Mainwindow-zones/mainwindow-note.cpp \
    Front/Mainwindow-zones/mainwindow-workzone.cpp \
    Front/MainElements/EmojiHub/emojihub.cpp \
    Front/mainwindow.cpp \
    main.cpp

HEADERS += \
    Back/filesystem.h \
    Back/secret-data.h \
    Back/server-connection.h \
    Back/utils/utils.h \
    Front/Dictionary/russiandictionary.h \
    Front/GeneralTextEdit/TimeTable/timetabletextedit.h \
    Front/GeneralTextEdit/gentextedit.h \
    Front/GeneralTextEdit/notemark.h \
    Front/GeneralTextEdit/textnewelement.h \
    Front/GeneralTextEdit/undoredotext.h \
    Front/MainElements/EmojiHub/emojibutton.h \
    Front/MainElements/addbreekgb.h \
    Front/MainElements/addbuttonhover.h \
    Front/MainElements/addtimetableelementgb.h \
    Front/MainElements/breek.h \
    Front/MainElements/calendarweek.h \
    Front/MainElements/daywidget.h \
    Front/MainElements/deletebreekszonebutton.h \
    Front/MainElements/deletetimetableelementbutton.h \
    Front/MainElements/demobreek.h \
    Front/MainElements/descriptionzonedaybutton.h \
    Front/MainElements/elementtemplate.h \
    Front/MainElements/imagehover.h \
    Front/MainElements/infogb.h \
    Front/MainElements/timeedit.h \
    Front/datastructures.h \
    Front/effects.hpp \
    Front/MainElements/EmojiHub/emojihub.h \
    Front/mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  resources.qrc

DISTFILES += \
    Back/FileSystem/BreeksInfo.db \
    Front/Images/Breeks/1.1.png \
    Front/Images/Breeks/1.2.png \
    Front/Images/Breeks/1.3.png \
    Front/Images/Breeks/1.4.png \
    Front/Images/Breeks/1.png \
    Front/Images/Breeks/10.1.png \
    Front/Images/Breeks/10.2.png \
    Front/Images/Breeks/10.3.png \
    Front/Images/Breeks/10.4.png \
    Front/Images/Breeks/10.png \
    Front/Images/Breeks/2.1.png \
    Front/Images/Breeks/2.2.png \
    Front/Images/Breeks/2.3.png \
    Front/Images/Breeks/2.4.png \
    Front/Images/Breeks/2.png \
    Front/Images/Breeks/3.1.png \
    Front/Images/Breeks/3.2.png \
    Front/Images/Breeks/3.3.png \
    Front/Images/Breeks/3.4.png \
    Front/Images/Breeks/3.png \
    Front/Images/Breeks/4.1.png \
    Front/Images/Breeks/4.2.png \
    Front/Images/Breeks/4.3.png \
    Front/Images/Breeks/4.4.png \
    Front/Images/Breeks/4.png \
    Front/Images/Breeks/5.1.png \
    Front/Images/Breeks/5.2.png \
    Front/Images/Breeks/5.3.png \
    Front/Images/Breeks/5.4.png \
    Front/Images/Breeks/5.png \
    Front/Images/Breeks/6.1.png \
    Front/Images/Breeks/6.2.png \
    Front/Images/Breeks/6.3.png \
    Front/Images/Breeks/6.4.png \
    Front/Images/Breeks/6.png \
    Front/Images/Breeks/7.1.png \
    Front/Images/Breeks/7.2.png \
    Front/Images/Breeks/7.3.png \
    Front/Images/Breeks/7.4.png \
    Front/Images/Breeks/7.png \
    Front/Images/Breeks/8.1.png \
    Front/Images/Breeks/8.2.png \
    Front/Images/Breeks/8.3.png \
    Front/Images/Breeks/8.4.png \
    Front/Images/Breeks/8.png \
    Front/Images/Breeks/9.1.png \
    Front/Images/Breeks/9.2.png \
    Front/Images/Breeks/9.3.png \
    Front/Images/Breeks/9.4.png \
    Front/Images/Breeks/9.png \
    Front/Images/NoteBackground.png \
    Front/Images/add-background.png \
    Front/Images/add.png \
    Front/Images/addButtonDefault.png \
    Front/Images/addButtonHover.png \
    Front/Images/calendar-and-clock.png \
    Front/Images/col.png \
    Front/Images/recycle-bin.png \
    Front/Images/sharik.jpg \
    Front/Images/trash.png \
    Front/Qml/qml_for_breeks.qml \
    Front/RusDic/RusDic.txt
