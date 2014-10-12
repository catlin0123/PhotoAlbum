/********************************************************************************
** Form generated from reading UI file 'descriptionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESCRIPTIONWINDOW_H
#define UI_DESCRIPTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DescriptionWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QPushButton *OKButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *DescriptionWindow)
    {
        if (DescriptionWindow->objectName().isEmpty())
            DescriptionWindow->setObjectName(QStringLiteral("DescriptionWindow"));
        DescriptionWindow->resize(445, 227);
        label = new QLabel(DescriptionWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 46, 13));
        label_2 = new QLabel(DescriptionWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 61, 16));
        titleEdit = new QLineEdit(DescriptionWindow);
        titleEdit->setObjectName(QStringLiteral("titleEdit"));
        titleEdit->setGeometry(QRect(100, 20, 311, 20));
        descriptionEdit = new QTextEdit(DescriptionWindow);
        descriptionEdit->setObjectName(QStringLiteral("descriptionEdit"));
        descriptionEdit->setGeometry(QRect(100, 50, 311, 121));
        OKButton = new QPushButton(DescriptionWindow);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setGeometry(QRect(250, 190, 75, 23));
        OKButton->setDefault(true);
        cancelButton = new QPushButton(DescriptionWindow);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(340, 190, 75, 23));

        retranslateUi(DescriptionWindow);

        QMetaObject::connectSlotsByName(DescriptionWindow);
    } // setupUi

    void retranslateUi(QWidget *DescriptionWindow)
    {
        DescriptionWindow->setWindowTitle(QApplication::translate("DescriptionWindow", "Form", 0));
        label->setText(QApplication::translate("DescriptionWindow", "Title", 0));
        label_2->setText(QApplication::translate("DescriptionWindow", "Description", 0));
        OKButton->setText(QApplication::translate("DescriptionWindow", "OK", 0));
        cancelButton->setText(QApplication::translate("DescriptionWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DescriptionWindow: public Ui_DescriptionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCRIPTIONWINDOW_H
