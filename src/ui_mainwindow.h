/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <Front/GeneralTextEdit/gentextedit.h>
#include "Front/MainElements/addbuttonhover.h"
#include "Front/MainElements/imagehover.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    GenTextEdit *note;
    QPushButton *buttonPage6;
    QPushButton *buttonPage1;
    QPushButton *buttonPage5;
    QPushButton *buttonPage3;
    QPushButton *buttonPage2;
    QPushButton *buttonPage4;
    QGroupBox *groupBoxWorkZone;
    QGroupBox *groupBoxBreeksDescreption;
    QWidget *shadowWidget;
    AddButtonHover *buttonAdd;
    ImageHover *buttonImage;
    QLabel *labelImageBackground;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1972, 1095);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        note = new GenTextEdit(centralwidget);
        note->setObjectName(QString::fromUtf8("note"));
        note->setGeometry(QRect(60, 130, 311, 531));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(12);
        note->setFont(font);
        note->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        note->setFocusPolicy(Qt::ClickFocus);
        note->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"   border-radius: 12px;\n"
"   padding-left:10; \n"
"   padding-top:10; \n"
"   padding-bottom:10; \n"
"   padding-right:10;\n"
"}"));
        buttonPage6 = new QPushButton(centralwidget);
        buttonPage6->setObjectName(QString::fromUtf8("buttonPage6"));
        buttonPage6->setGeometry(QRect(20, 380, 51, 31));
        buttonPage6->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage6->setFocusPolicy(Qt::TabFocus);
        buttonPage1 = new QPushButton(centralwidget);
        buttonPage1->setObjectName(QString::fromUtf8("buttonPage1"));
        buttonPage1->setGeometry(QRect(20, 180, 51, 31));
        buttonPage1->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage1->setFocusPolicy(Qt::TabFocus);
        buttonPage1->setAcceptDrops(false);
        buttonPage1->setAutoFillBackground(false);
        buttonPage1->setStyleSheet(QString::fromUtf8(""));
        buttonPage1->setAutoRepeat(false);
        buttonPage1->setAutoDefault(false);
        buttonPage1->setFlat(false);
        buttonPage5 = new QPushButton(centralwidget);
        buttonPage5->setObjectName(QString::fromUtf8("buttonPage5"));
        buttonPage5->setGeometry(QRect(20, 340, 51, 31));
        buttonPage5->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage5->setFocusPolicy(Qt::TabFocus);
        buttonPage3 = new QPushButton(centralwidget);
        buttonPage3->setObjectName(QString::fromUtf8("buttonPage3"));
        buttonPage3->setGeometry(QRect(20, 260, 51, 31));
        buttonPage3->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage3->setFocusPolicy(Qt::TabFocus);
        buttonPage2 = new QPushButton(centralwidget);
        buttonPage2->setObjectName(QString::fromUtf8("buttonPage2"));
        buttonPage2->setGeometry(QRect(20, 220, 51, 31));
        buttonPage2->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage2->setFocusPolicy(Qt::TabFocus);
        buttonPage2->setFlat(false);
        buttonPage4 = new QPushButton(centralwidget);
        buttonPage4->setObjectName(QString::fromUtf8("buttonPage4"));
        buttonPage4->setGeometry(QRect(20, 300, 51, 31));
        buttonPage4->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage4->setFocusPolicy(Qt::TabFocus);
        groupBoxWorkZone = new QGroupBox(centralwidget);
        groupBoxWorkZone->setObjectName(QString::fromUtf8("groupBoxWorkZone"));
        groupBoxWorkZone->setGeometry(QRect(450, 20, 1041, 991));
        groupBoxWorkZone->setStyleSheet(QString::fromUtf8(""));
        groupBoxBreeksDescreption = new QGroupBox(centralwidget);
        groupBoxBreeksDescreption->setObjectName(QString::fromUtf8("groupBoxBreeksDescreption"));
        groupBoxBreeksDescreption->setGeometry(QRect(1520, 20, 351, 991));
        shadowWidget = new QWidget(centralwidget);
        shadowWidget->setObjectName(QString::fromUtf8("shadowWidget"));
        shadowWidget->setGeometry(QRect(449, 19, 1041, 991));
        buttonAdd = new AddButtonHover(centralwidget);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(420, 10, 61, 61));
        buttonAdd->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAdd->setFocusPolicy(Qt::TabFocus);
        buttonAdd->setStyleSheet(QString::fromUtf8("border-image:url(:/Images/Front/Images/pluss.png);\n"
"background: none;"));
        buttonImage = new ImageHover(centralwidget);
        buttonImage->setObjectName(QString::fromUtf8("buttonImage"));
        buttonImage->setGeometry(QRect(70, 720, 291, 181));
        buttonImage->setCursor(QCursor(Qt::PointingHandCursor));
        buttonImage->setFocusPolicy(Qt::TabFocus);
        buttonImage->setStyleSheet(QString::fromUtf8(""));
        buttonImage->setFlat(true);
        labelImageBackground = new QLabel(centralwidget);
        labelImageBackground->setObjectName(QString::fromUtf8("labelImageBackground"));
        labelImageBackground->setGeometry(QRect(60, 710, 311, 201));
        labelImageBackground->setStyleSheet(QString::fromUtf8("background-color: #e6f6ff;"));
        MainWindow->setCentralWidget(centralwidget);
        labelImageBackground->raise();
        shadowWidget->raise();
        buttonPage6->raise();
        buttonPage1->raise();
        buttonPage5->raise();
        buttonPage3->raise();
        buttonPage2->raise();
        buttonPage4->raise();
        note->raise();
        groupBoxWorkZone->raise();
        groupBoxBreeksDescreption->raise();
        buttonImage->raise();
        buttonAdd->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1972, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        buttonPage6->setDefault(false);
        buttonPage1->setDefault(false);
        buttonPage5->setDefault(false);
        buttonPage3->setDefault(false);
        buttonPage2->setDefault(false);
        buttonPage4->setDefault(false);
        buttonImage->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        buttonPage6->setText(QString());
        buttonPage1->setText(QString());
        buttonPage5->setText(QString());
        buttonPage3->setText(QString());
        buttonPage2->setText(QString());
        buttonPage4->setText(QString());
        groupBoxWorkZone->setTitle(QString());
        groupBoxBreeksDescreption->setTitle(QString());
        buttonAdd->setText(QString());
        buttonImage->setText(QString());
        labelImageBackground->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
