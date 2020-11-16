/********************************************************************************
** Form generated from reading UI file 'addelement.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDELEMENT_H
#define UI_ADDELEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include "Front/GeneralTextEdit/TimeTable/timetabletextedit.h"

QT_BEGIN_NAMESPACE

class Ui_AddElement
{
public:
    QGroupBox *groupBox;
    TimetableTextEdit *text;
    QPushButton *buttonAdd;
    QPushButton *buttonMonday;
    QPushButton *buttonTuesday;
    QPushButton *buttonWednesday;
    QPushButton *buttonThursday;
    QPushButton *buttonFriday;
    QPushButton *buttonSaturday;
    QTimeEdit *timeEnd;
    QTimeEdit *timeStart;
    QPushButton *buttonTag;
    QPushButton *pushButtonBreeksZone;
    QPushButton *pushButtonTimeTableZone;

    void setupUi(QWidget *AddElement)
    {
        if (AddElement->objectName().isEmpty())
            AddElement->setObjectName(QString::fromUtf8("AddElement"));
        AddElement->resize(336, 177);
        groupBox = new QGroupBox(AddElement);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, -20, 331, 191));
        text = new TimetableTextEdit(groupBox);
        text->setObjectName(QString::fromUtf8("text"));
        text->setGeometry(QRect(0, 70, 331, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto Condensed Medium"));
        font.setPointSize(12);
        text->setFont(font);
        text->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        text->setFocusPolicy(Qt::ClickFocus);
        buttonAdd = new QPushButton(groupBox);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));
        buttonAdd->setGeometry(QRect(280, 150, 41, 31));
        buttonAdd->setFocusPolicy(Qt::TabFocus);
        buttonMonday = new QPushButton(groupBox);
        buttonMonday->setObjectName(QString::fromUtf8("buttonMonday"));
        buttonMonday->setGeometry(QRect(10, 30, 30, 30));
        buttonMonday->setFocusPolicy(Qt::TabFocus);
        buttonTuesday = new QPushButton(groupBox);
        buttonTuesday->setObjectName(QString::fromUtf8("buttonTuesday"));
        buttonTuesday->setGeometry(QRect(43, 30, 30, 30));
        buttonTuesday->setFocusPolicy(Qt::TabFocus);
        buttonWednesday = new QPushButton(groupBox);
        buttonWednesday->setObjectName(QString::fromUtf8("buttonWednesday"));
        buttonWednesday->setGeometry(QRect(76, 30, 30, 30));
        buttonWednesday->setFocusPolicy(Qt::TabFocus);
        buttonThursday = new QPushButton(groupBox);
        buttonThursday->setObjectName(QString::fromUtf8("buttonThursday"));
        buttonThursday->setGeometry(QRect(109, 30, 30, 30));
        buttonThursday->setFocusPolicy(Qt::TabFocus);
        buttonFriday = new QPushButton(groupBox);
        buttonFriday->setObjectName(QString::fromUtf8("buttonFriday"));
        buttonFriday->setGeometry(QRect(142, 30, 30, 30));
        buttonFriday->setFocusPolicy(Qt::TabFocus);
        buttonSaturday = new QPushButton(groupBox);
        buttonSaturday->setObjectName(QString::fromUtf8("buttonSaturday"));
        buttonSaturday->setGeometry(QRect(175, 30, 31, 31));
        buttonSaturday->setFocusPolicy(Qt::TabFocus);
        timeEnd = new QTimeEdit(groupBox);
        timeEnd->setObjectName(QString::fromUtf8("timeEnd"));
        timeEnd->setGeometry(QRect(260, 45, 61, 22));
        timeStart = new QTimeEdit(groupBox);
        timeStart->setObjectName(QString::fromUtf8("timeStart"));
        timeStart->setGeometry(QRect(260, 23, 61, 22));
        buttonTag = new QPushButton(groupBox);
        buttonTag->setObjectName(QString::fromUtf8("buttonTag"));
        buttonTag->setGeometry(QRect(240, 150, 31, 31));
        buttonTag->setFocusPolicy(Qt::TabFocus);
        pushButtonBreeksZone = new QPushButton(groupBox);
        pushButtonBreeksZone->setObjectName(QString::fromUtf8("pushButtonBreeksZone"));
        pushButtonBreeksZone->setGeometry(QRect(10, 150, 113, 32));
        pushButtonBreeksZone->setFocusPolicy(Qt::TabFocus);
        pushButtonTimeTableZone = new QPushButton(groupBox);
        pushButtonTimeTableZone->setObjectName(QString::fromUtf8("pushButtonTimeTableZone"));
        pushButtonTimeTableZone->setGeometry(QRect(120, 150, 113, 32));
        pushButtonTimeTableZone->setFocusPolicy(Qt::TabFocus);

        retranslateUi(AddElement);

        QMetaObject::connectSlotsByName(AddElement);
    } // setupUi

    void retranslateUi(QWidget *AddElement)
    {
        AddElement->setWindowTitle(QCoreApplication::translate("AddElement", "Form", nullptr));
        groupBox->setTitle(QString());
        buttonAdd->setText(QCoreApplication::translate("AddElement", "Add", nullptr));
        buttonMonday->setText(QCoreApplication::translate("AddElement", "Mon", nullptr));
        buttonTuesday->setText(QCoreApplication::translate("AddElement", "Tue", nullptr));
        buttonWednesday->setText(QCoreApplication::translate("AddElement", "Wed", nullptr));
        buttonThursday->setText(QCoreApplication::translate("AddElement", "Thu", nullptr));
        buttonFriday->setText(QCoreApplication::translate("AddElement", "Fri", nullptr));
        buttonSaturday->setText(QCoreApplication::translate("AddElement", "Sat", nullptr));
        buttonTag->setText(QString());
        pushButtonBreeksZone->setText(QCoreApplication::translate("AddElement", "Breeks", nullptr));
        pushButtonTimeTableZone->setText(QCoreApplication::translate("AddElement", "Time Table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddElement: public Ui_AddElement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDELEMENT_H
