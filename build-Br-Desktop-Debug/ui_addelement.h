/********************************************************************************
** Form generated from reading UI file 'addelement.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
#include "textnewelement.h"

QT_BEGIN_NAMESPACE

class Ui_AddElement
{
public:
    QGroupBox *groupBox;
    TextNewElement *text;
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
            AddElement->setObjectName(QStringLiteral("AddElement"));
        AddElement->resize(336, 177);
        groupBox = new QGroupBox(AddElement);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, -20, 331, 191));
        text = new TextNewElement(groupBox);
        text->setObjectName(QStringLiteral("text"));
        text->setGeometry(QRect(0, 70, 331, 71));
        QFont font;
        font.setFamily(QStringLiteral("Roboto Condensed Medium"));
        font.setPointSize(12);
        text->setFont(font);
        text->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        buttonAdd = new QPushButton(groupBox);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setGeometry(QRect(280, 150, 41, 31));
        buttonAdd->setFocusPolicy(Qt::TabFocus);
        buttonMonday = new QPushButton(groupBox);
        buttonMonday->setObjectName(QStringLiteral("buttonMonday"));
        buttonMonday->setGeometry(QRect(10, 30, 30, 30));
        buttonMonday->setFocusPolicy(Qt::TabFocus);
        buttonTuesday = new QPushButton(groupBox);
        buttonTuesday->setObjectName(QStringLiteral("buttonTuesday"));
        buttonTuesday->setGeometry(QRect(43, 30, 30, 30));
        buttonTuesday->setFocusPolicy(Qt::TabFocus);
        buttonWednesday = new QPushButton(groupBox);
        buttonWednesday->setObjectName(QStringLiteral("buttonWednesday"));
        buttonWednesday->setGeometry(QRect(76, 30, 30, 30));
        buttonWednesday->setFocusPolicy(Qt::TabFocus);
        buttonThursday = new QPushButton(groupBox);
        buttonThursday->setObjectName(QStringLiteral("buttonThursday"));
        buttonThursday->setGeometry(QRect(109, 30, 30, 30));
        buttonThursday->setFocusPolicy(Qt::TabFocus);
        buttonFriday = new QPushButton(groupBox);
        buttonFriday->setObjectName(QStringLiteral("buttonFriday"));
        buttonFriday->setGeometry(QRect(142, 30, 30, 30));
        buttonFriday->setFocusPolicy(Qt::TabFocus);
        buttonSaturday = new QPushButton(groupBox);
        buttonSaturday->setObjectName(QStringLiteral("buttonSaturday"));
        buttonSaturday->setGeometry(QRect(175, 30, 30, 30));
        buttonSaturday->setFocusPolicy(Qt::TabFocus);
        timeEnd = new QTimeEdit(groupBox);
        timeEnd->setObjectName(QStringLiteral("timeEnd"));
        timeEnd->setGeometry(QRect(260, 45, 61, 22));
        timeStart = new QTimeEdit(groupBox);
        timeStart->setObjectName(QStringLiteral("timeStart"));
        timeStart->setGeometry(QRect(260, 23, 61, 22));
        buttonTag = new QPushButton(groupBox);
        buttonTag->setObjectName(QStringLiteral("buttonTag"));
        buttonTag->setGeometry(QRect(240, 150, 31, 31));
        buttonTag->setFocusPolicy(Qt::TabFocus);
        pushButtonBreeksZone = new QPushButton(groupBox);
        pushButtonBreeksZone->setObjectName(QStringLiteral("pushButtonBreeksZone"));
        pushButtonBreeksZone->setGeometry(QRect(10, 150, 113, 32));
        pushButtonBreeksZone->setFocusPolicy(Qt::TabFocus);
        pushButtonTimeTableZone = new QPushButton(groupBox);
        pushButtonTimeTableZone->setObjectName(QStringLiteral("pushButtonTimeTableZone"));
        pushButtonTimeTableZone->setGeometry(QRect(120, 150, 113, 32));
        pushButtonTimeTableZone->setFocusPolicy(Qt::TabFocus);

        retranslateUi(AddElement);

        QMetaObject::connectSlotsByName(AddElement);
    } // setupUi

    void retranslateUi(QWidget *AddElement)
    {
        AddElement->setWindowTitle(QApplication::translate("AddElement", "Form", nullptr));
        groupBox->setTitle(QString());
        buttonAdd->setText(QApplication::translate("AddElement", "Add", nullptr));
        buttonMonday->setText(QApplication::translate("AddElement", "Mon", nullptr));
        buttonTuesday->setText(QApplication::translate("AddElement", "Tue", nullptr));
        buttonWednesday->setText(QApplication::translate("AddElement", "Wed", nullptr));
        buttonThursday->setText(QApplication::translate("AddElement", "Thu", nullptr));
        buttonFriday->setText(QApplication::translate("AddElement", "Fri", nullptr));
        buttonSaturday->setText(QApplication::translate("AddElement", "Sat", nullptr));
        buttonTag->setText(QString());
        pushButtonBreeksZone->setText(QApplication::translate("AddElement", "Breeks", nullptr));
        pushButtonTimeTableZone->setText(QApplication::translate("AddElement", "Time Table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddElement: public Ui_AddElement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDELEMENT_H
