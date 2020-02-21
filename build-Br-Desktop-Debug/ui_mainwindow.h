/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
#include "addbuttonhover.h"
#include "imagehover.h"
#include "notetextedit.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelImageBackground;
    ImageHover *buttonImage;
    AddButtonHover *buttonAdd;
    QLabel *labelBackground;
    NoteTextEdit *note;
    QPushButton *buttonPage6;
    QPushButton *buttonPage1;
    QPushButton *buttonPage5;
    QPushButton *buttonPage3;
    QPushButton *buttonPage2;
    QPushButton *buttonPage4;
    QGroupBox *groupBox;
    QPushButton *buttonMakeBold;
    QPushButton *buttonMakeItalic;
    QPushButton *buttonMakeUnderline;
    QPushButton *buttonMakeStrike;
    QPushButton *buttonAddTodoList;
    QGroupBox *groupBoxWorkZone;
    QGroupBox *groupBoxBreeksDescreption;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1972, 1095);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelImageBackground = new QLabel(centralwidget);
        labelImageBackground->setObjectName(QStringLiteral("labelImageBackground"));
        labelImageBackground->setGeometry(QRect(80, 80, 250, 250));
        labelImageBackground->setStyleSheet(QStringLiteral("background-color: #e6f6ff;"));
        buttonImage = new ImageHover(centralwidget);
        buttonImage->setObjectName(QStringLiteral("buttonImage"));
        buttonImage->setGeometry(QRect(85, 85, 241, 241));
        buttonImage->setCursor(QCursor(Qt::PointingHandCursor));
        buttonImage->setFocusPolicy(Qt::TabFocus);
        buttonImage->setStyleSheet(QStringLiteral(""));
        buttonImage->setFlat(true);
        buttonAdd = new AddButtonHover(centralwidget);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setGeometry(QRect(400, -20, 71, 199));
        buttonAdd->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAdd->setFocusPolicy(Qt::TabFocus);
        buttonAdd->setStyleSheet(QStringLiteral("border-image:url(:/images/images/addButtonDefault.png);"));
        labelBackground = new QLabel(centralwidget);
        labelBackground->setObjectName(QStringLiteral("labelBackground"));
        labelBackground->setGeometry(QRect(-60, 0, 2081, 1121));
        labelBackground->setCursor(QCursor(Qt::ArrowCursor));
        labelBackground->setStyleSheet(QStringLiteral("background-color: #ffffff"));
        note = new NoteTextEdit(centralwidget);
        note->setObjectName(QStringLiteral("note"));
        note->setGeometry(QRect(60, 420, 351, 521));
        QFont font;
        font.setFamily(QStringLiteral("Utopia"));
        font.setPointSize(13);
        note->setFont(font);
        note->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        note->setFocusPolicy(Qt::ClickFocus);
        note->setStyleSheet(QStringLiteral("border-image:url(:/images/images/NoteBackground.png);"));
        buttonPage6 = new QPushButton(centralwidget);
        buttonPage6->setObjectName(QStringLiteral("buttonPage6"));
        buttonPage6->setGeometry(QRect(-10, 670, 51, 31));
        buttonPage6->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage6->setFocusPolicy(Qt::TabFocus);
        buttonPage1 = new QPushButton(centralwidget);
        buttonPage1->setObjectName(QStringLiteral("buttonPage1"));
        buttonPage1->setGeometry(QRect(-10, 470, 51, 31));
        buttonPage1->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage1->setFocusPolicy(Qt::TabFocus);
        buttonPage1->setAcceptDrops(false);
        buttonPage1->setAutoFillBackground(false);
        buttonPage1->setStyleSheet(QStringLiteral(""));
        buttonPage1->setAutoRepeat(false);
        buttonPage1->setAutoDefault(false);
        buttonPage1->setFlat(false);
        buttonPage5 = new QPushButton(centralwidget);
        buttonPage5->setObjectName(QStringLiteral("buttonPage5"));
        buttonPage5->setGeometry(QRect(-10, 630, 51, 31));
        buttonPage5->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage5->setFocusPolicy(Qt::TabFocus);
        buttonPage3 = new QPushButton(centralwidget);
        buttonPage3->setObjectName(QStringLiteral("buttonPage3"));
        buttonPage3->setGeometry(QRect(-10, 550, 51, 31));
        buttonPage3->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage3->setFocusPolicy(Qt::TabFocus);
        buttonPage2 = new QPushButton(centralwidget);
        buttonPage2->setObjectName(QStringLiteral("buttonPage2"));
        buttonPage2->setGeometry(QRect(-10, 510, 51, 31));
        buttonPage2->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage2->setFocusPolicy(Qt::TabFocus);
        buttonPage2->setFlat(false);
        buttonPage4 = new QPushButton(centralwidget);
        buttonPage4->setObjectName(QStringLiteral("buttonPage4"));
        buttonPage4->setGeometry(QRect(-10, 590, 51, 31));
        buttonPage4->setCursor(QCursor(Qt::PointingHandCursor));
        buttonPage4->setFocusPolicy(Qt::TabFocus);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(400, 490, 61, 181));
        groupBox->setCursor(QCursor(Qt::ArrowCursor));
        groupBox->setStyleSheet(QStringLiteral(""));
        buttonMakeBold = new QPushButton(groupBox);
        buttonMakeBold->setObjectName(QStringLiteral("buttonMakeBold"));
        buttonMakeBold->setGeometry(QRect(20, 30, 32, 25));
        buttonMakeBold->setCursor(QCursor(Qt::PointingHandCursor));
        buttonMakeBold->setFocusPolicy(Qt::TabFocus);
        buttonMakeBold->setStyleSheet(QStringLiteral("font-weight: bold;"));
        buttonMakeItalic = new QPushButton(groupBox);
        buttonMakeItalic->setObjectName(QStringLiteral("buttonMakeItalic"));
        buttonMakeItalic->setGeometry(QRect(20, 60, 32, 25));
        buttonMakeItalic->setCursor(QCursor(Qt::PointingHandCursor));
        buttonMakeItalic->setFocusPolicy(Qt::TabFocus);
        buttonMakeItalic->setStyleSheet(QStringLiteral("font-style: italic;"));
        buttonMakeUnderline = new QPushButton(groupBox);
        buttonMakeUnderline->setObjectName(QStringLiteral("buttonMakeUnderline"));
        buttonMakeUnderline->setGeometry(QRect(20, 90, 32, 25));
        buttonMakeUnderline->setCursor(QCursor(Qt::PointingHandCursor));
        buttonMakeUnderline->setFocusPolicy(Qt::TabFocus);
        buttonMakeUnderline->setStyleSheet(QStringLiteral("text-decoration: underline;"));
        buttonMakeStrike = new QPushButton(groupBox);
        buttonMakeStrike->setObjectName(QStringLiteral("buttonMakeStrike"));
        buttonMakeStrike->setGeometry(QRect(20, 120, 32, 25));
        buttonMakeStrike->setCursor(QCursor(Qt::PointingHandCursor));
        buttonMakeStrike->setFocusPolicy(Qt::TabFocus);
        buttonMakeStrike->setStyleSheet(QStringLiteral("text-decoration: line-through;"));
        buttonAddTodoList = new QPushButton(groupBox);
        buttonAddTodoList->setObjectName(QStringLiteral("buttonAddTodoList"));
        buttonAddTodoList->setGeometry(QRect(20, 150, 32, 25));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        buttonAddTodoList->setFont(font1);
        buttonAddTodoList->setCursor(QCursor(Qt::PointingHandCursor));
        buttonAddTodoList->setFocusPolicy(Qt::TabFocus);
        buttonAddTodoList->setStyleSheet(QStringLiteral("font-weight: bold;"));
        groupBoxWorkZone = new QGroupBox(centralwidget);
        groupBoxWorkZone->setObjectName(QStringLiteral("groupBoxWorkZone"));
        groupBoxWorkZone->setGeometry(QRect(520, 20, 1041, 991));
        groupBoxBreeksDescreption = new QGroupBox(centralwidget);
        groupBoxBreeksDescreption->setObjectName(QStringLiteral("groupBoxBreeksDescreption"));
        groupBoxBreeksDescreption->setGeometry(QRect(1560, 20, 351, 991));
        MainWindow->setCentralWidget(centralwidget);
        labelBackground->raise();
        groupBox->raise();
        buttonAdd->raise();
        buttonPage6->raise();
        buttonPage1->raise();
        buttonPage5->raise();
        buttonPage3->raise();
        buttonPage2->raise();
        buttonPage4->raise();
        note->raise();
        labelImageBackground->raise();
        buttonImage->raise();
        groupBoxWorkZone->raise();
        groupBoxBreeksDescreption->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1972, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        buttonImage->setDefault(false);
        buttonPage6->setDefault(false);
        buttonPage1->setDefault(false);
        buttonPage5->setDefault(false);
        buttonPage3->setDefault(false);
        buttonPage2->setDefault(false);
        buttonPage4->setDefault(false);
        buttonMakeBold->setDefault(false);
        buttonMakeItalic->setDefault(false);
        buttonMakeUnderline->setDefault(false);
        buttonMakeStrike->setDefault(false);
        buttonAddTodoList->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelImageBackground->setText(QString());
        buttonImage->setText(QString());
        buttonAdd->setText(QString());
        labelBackground->setText(QString());
        buttonPage6->setText(QString());
        buttonPage1->setText(QString());
        buttonPage5->setText(QString());
        buttonPage3->setText(QString());
        buttonPage2->setText(QString());
        buttonPage4->setText(QString());
        groupBox->setTitle(QString());
        buttonMakeBold->setText(QApplication::translate("MainWindow", "B", nullptr));
        buttonMakeItalic->setText(QApplication::translate("MainWindow", "I", nullptr));
        buttonMakeUnderline->setText(QApplication::translate("MainWindow", "U", nullptr));
        buttonMakeStrike->setText(QApplication::translate("MainWindow", "S", nullptr));
        buttonAddTodoList->setText(QApplication::translate("MainWindow", "list", nullptr));
        groupBoxWorkZone->setTitle(QString());
        groupBoxBreeksDescreption->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
