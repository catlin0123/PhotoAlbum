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
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DescriptionWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;

    void setupUi(QDialog *DescriptionWindow)
    {
        if (DescriptionWindow->objectName().isEmpty())
            DescriptionWindow->setObjectName(QStringLiteral("DescriptionWindow"));
        DescriptionWindow->resize(409, 237);
        buttonBox = new QDialogButtonBox(DescriptionWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 180, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DescriptionWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 46, 13));
        label_2 = new QLabel(DescriptionWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 61, 16));
        titleEdit = new QLineEdit(DescriptionWindow);
        titleEdit->setObjectName(QStringLiteral("titleEdit"));
        titleEdit->setGeometry(QRect(100, 20, 291, 20));
        descriptionEdit = new QTextEdit(DescriptionWindow);
        descriptionEdit->setObjectName(QStringLiteral("descriptionEdit"));
        descriptionEdit->setGeometry(QRect(100, 50, 291, 131));

        retranslateUi(DescriptionWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), DescriptionWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DescriptionWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(DescriptionWindow);
    } // setupUi

    void retranslateUi(QDialog *DescriptionWindow)
    {
        DescriptionWindow->setWindowTitle(QApplication::translate("DescriptionWindow", "Dialog", 0));
        label->setText(QApplication::translate("DescriptionWindow", "Title", 0));
        label_2->setText(QApplication::translate("DescriptionWindow", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class DescriptionWindow: public Ui_DescriptionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCRIPTIONWINDOW_H
