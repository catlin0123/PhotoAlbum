/********************************************************************************
** Form generated from reading UI file 'resize.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIZE_H
#define UI_RESIZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Resize
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *heightSpinBox;
    QSpinBox *widthSpinBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *Resize)
    {
        if (Resize->objectName().isEmpty())
            Resize->setObjectName(QStringLiteral("Resize"));
        Resize->resize(400, 205);
        buttonBox = new QDialogButtonBox(Resize);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 160, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        heightSpinBox = new QSpinBox(Resize);
        heightSpinBox->setObjectName(QStringLiteral("heightSpinBox"));
        heightSpinBox->setGeometry(QRect(120, 60, 71, 22));
        widthSpinBox = new QSpinBox(Resize);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));
        widthSpinBox->setGeometry(QRect(120, 100, 71, 22));
        label = new QLabel(Resize);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 60, 46, 13));
        label_2 = new QLabel(Resize);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 100, 46, 13));

        retranslateUi(Resize);
        QObject::connect(buttonBox, SIGNAL(accepted()), Resize, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Resize, SLOT(reject()));

        QMetaObject::connectSlotsByName(Resize);
    } // setupUi

    void retranslateUi(QDialog *Resize)
    {
        Resize->setWindowTitle(QApplication::translate("Resize", "Dialog", 0));
        label->setText(QApplication::translate("Resize", "Height", 0));
        label_2->setText(QApplication::translate("Resize", "Width", 0));
    } // retranslateUi

};

namespace Ui {
    class Resize: public Ui_Resize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIZE_H
