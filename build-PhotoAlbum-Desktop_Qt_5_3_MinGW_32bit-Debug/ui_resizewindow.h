/********************************************************************************
** Form generated from reading UI file 'resizewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIZEWINDOW_H
#define UI_RESIZEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ResizeWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *heightSpinBox;
    QSpinBox *widthSpinBox;
    QPushButton *testButton;

    void setupUi(QDialog *ResizeWindow)
    {
        if (ResizeWindow->objectName().isEmpty())
            ResizeWindow->setObjectName(QStringLiteral("ResizeWindow"));
        ResizeWindow->resize(263, 220);
        buttonBox = new QDialogButtonBox(ResizeWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 170, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ResizeWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 50, 46, 13));
        label_2 = new QLabel(ResizeWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 100, 46, 13));
        heightSpinBox = new QSpinBox(ResizeWindow);
        heightSpinBox->setObjectName(QStringLiteral("heightSpinBox"));
        heightSpinBox->setGeometry(QRect(100, 50, 81, 22));
        widthSpinBox = new QSpinBox(ResizeWindow);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setGeometry(QRect(100, 100, 81, 22));
        testButton = new QPushButton(ResizeWindow);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setGeometry(QRect(170, 10, 75, 23));

        retranslateUi(ResizeWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResizeWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResizeWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(ResizeWindow);
    } // setupUi

    void retranslateUi(QDialog *ResizeWindow)
    {
        ResizeWindow->setWindowTitle(QApplication::translate("ResizeWindow", "Dialog", 0));
        label->setText(QApplication::translate("ResizeWindow", "Height", 0));
        label_2->setText(QApplication::translate("ResizeWindow", "Width", 0));
        testButton->setText(QApplication::translate("ResizeWindow", "test", 0));
    } // retranslateUi

};

namespace Ui {
    class ResizeWindow: public Ui_ResizeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIZEWINDOW_H
