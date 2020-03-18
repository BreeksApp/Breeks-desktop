QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    GeneralTextEdit/gentextedit-get-set.cpp \
    GeneralTextEdit/gentextedit-keys-realization.cpp \
    breek.cpp \
    FileSystem/databaseIO.cpp \
    elementtemplate.cpp \
    FileSystem/filesystem.cpp \
    loginform.cpp \
    main.cpp \
    mainwidnow-timetable.cpp \
    mainwindow-breekszone.cpp \
    mainwindow-effects.cpp \
    mainwindow.cpp \
    mainwindow-note.cpp \
    addelement.cpp \
    textnewelement.cpp \
    imagehover.cpp \
    addbuttonhover.cpp \
    mainwindow-image.cpp \
    mainwindow-addelement.cpp \
    mainwindow-workzone.cpp \
    GeneralTextEdit/gentextedit.cpp \
    GeneralTextEdit/gentextedit-details.cpp

HEADERS += \
    breek.h \
    elementtemplate.h \
    filesystem.h \
    loginform.h \
    mainwindow.h \
    addelement.h \
    textnewelement.h \
    imagehover.h \
    addbuttonhover.h \
    datastructures.h \
    effects.hpp \
    gentextedit.h

FORMS += \
    loginform.ui \
    mainwindow.ui \
    addelement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
  images/breeks/1.1.png \
    images/breeks/1.1.png \
    images/breeks/1.2.png \
    images/breeks/1.3.png \
    images/breeks/1.4.png \
    images/breeks/2.1.png \
    images/breeks/2.2.png \
    images/breeks/2.3.png \
    images/breeks/2.4.png \
    images/breeks/3.1.png \
    images/breeks/3.2.png \
    images/breeks/3.3.png \
    images/breeks/3.4.png \
    images/breeks/4.1.png \
    images/breeks/4.2.png \
    images/breeks/4.3.png \
    images/breeks/4.4.png \
    images/breeks/5.1.png \
    images/breeks/5.2.png \
    images/breeks/5.3.png \
    images/breeks/5.4.png \
    images/breeks/6.1.png \
    images/breeks/6.2.png \
    images/breeks/6.3.png \
    images/breeks/6.4.png \
    images/breeks/7.1.png \
    images/breeks/7.2.png \
    images/breeks/7.3.png \
    images/breeks/7.4.png \
    images/breeks/8.1.png \
    images/breeks/8.2.png \
    images/breeks/8.3.png \
    images/breeks/8.4.png \
    images/breeks/9.1.png \
    images/breeks/9.2.png \
    images/breeks/9.3.png \
    images/breeks/9.4.png \
    images/breeks/10.1.png \
    images/breeks/10.2.png \
    images/breeks/10.3.png \
    images/breeks/10.4.png
