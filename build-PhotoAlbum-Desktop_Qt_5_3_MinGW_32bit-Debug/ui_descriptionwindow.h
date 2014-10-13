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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DescriptionWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *locationEdit;
    QLineEdit *descriptionEdit;
    QLabel *label_3;
    QCalendarWidget *calendarWidget;

    void setupUi(QDialog *DescriptionWindow)
    {
        if (DescriptionWindow->objectName().isEmpty())
            DescriptionWindow->setObjectName(QStringLiteral("DescriptionWindow"));
        DescriptionWindow->resize(409, 284);
        buttonBox = new QDialogButtonBox(DescriptionWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(180, 240, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DescriptionWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 46, 13));
        label_2 = new QLabel(DescriptionWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 61, 16));
        locationEdit = new QLineEdit(DescriptionWindow);
        locationEdit->setObjectName(QStringLiteral("locationEdit"));
        locationEdit->setGeometry(QRect(100, 20, 291, 20));
        descriptionEdit = new QLineEdit(DescriptionWindow);
        descriptionEdit->setObjectName(QStringLiteral("descriptionEdit"));
        descriptionEdit->setGeometry(QRect(100, 50, 291, 20));
        label_3 = new QLabel(DescriptionWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 46, 13));
        calendarWidget = new QCalendarWidget(DescriptionWindow);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(100, 80, 256, 155));

        retranslateUi(DescriptionWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), DescriptionWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DescriptionWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(DescriptionWindow);
    } // setupUi

    void retranslateUi(QDialog *DescriptionWindow)
    {
        DescriptionWindow->setWindowTitle(QApplication::translate("DescriptionWindow", "Dialog", 0));
        label->setText(QApplication::translate("DescriptionWindow", "Location", 0));
        label_2->setText(QApplication::translate("DescriptionWindow", "Description", 0));
        label_3->setText(QApplication::translate("DescriptionWindow", "Date", 0));
    } // retranslateUi

};

namespace Ui {
    class DescriptionWindow: public Ui_DescriptionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCRIPTIONWINDOW_H
