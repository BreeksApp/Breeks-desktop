/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QPushButton *loginButton;
    QLabel *infoLabe;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;

    void setupUi(QWidget *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QString::fromUtf8("LoginForm"));
        LoginForm->resize(400, 300);
        loginButton = new QPushButton(LoginForm);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(130, 190, 113, 32));
        infoLabe = new QLabel(LoginForm);
        infoLabe->setObjectName(QString::fromUtf8("infoLabe"));
        infoLabe->setGeometry(QRect(90, 240, 201, 16));
        layoutWidget = new QWidget(LoginForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 90, 197, 23));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        usernameLabel = new QLabel(layoutWidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));

        horizontalLayout->addWidget(usernameLabel);

        usernameLineEdit = new QLineEdit(layoutWidget);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));

        horizontalLayout->addWidget(usernameLineEdit);

        layoutWidget1 = new QWidget(LoginForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 120, 194, 23));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passwordLabel = new QLabel(layoutWidget1);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        horizontalLayout_2->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(layoutWidget1);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));

        horizontalLayout_2->addWidget(passwordLineEdit);


        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QWidget *LoginForm)
    {
        LoginForm->setWindowTitle(QCoreApplication::translate("LoginForm", "Form", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginForm", "Login", nullptr));
        infoLabe->setText(QString());
        usernameLabel->setText(QCoreApplication::translate("LoginForm", "Username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginForm", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
