/********************************************************************************
** Form generated from reading UI file 'pictureedits.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREEDITS_H
#define UI_PICTUREEDITS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pictureedits
{
public:
    QSpinBox *smoothSpinBox;
    QSpinBox *sharpenSpinBox;
    QSlider *brightnessSlider;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QRadioButton *radioButton;
    QPushButton *edgeButton;
    QPushButton *contrastButton;
    QPushButton *gammaButton;
    QPushButton *smoothButton;
    QPushButton *sharpenButton;

    void setupUi(QWidget *pictureedits)
    {
        if (pictureedits->objectName().isEmpty())
            pictureedits->setObjectName(QStringLiteral("pictureedits"));
        pictureedits->resize(357, 222);
        smoothSpinBox = new QSpinBox(pictureedits);
        smoothSpinBox->setObjectName(QStringLiteral("smoothSpinBox"));
        smoothSpinBox->setGeometry(QRect(120, 140, 42, 22));
        smoothSpinBox->setMaximum(100);
        smoothSpinBox->setSingleStep(10);
        sharpenSpinBox = new QSpinBox(pictureedits);
        sharpenSpinBox->setObjectName(QStringLiteral("sharpenSpinBox"));
        sharpenSpinBox->setGeometry(QRect(120, 170, 42, 22));
        sharpenSpinBox->setSingleStep(10);
        brightnessSlider = new QSlider(pictureedits);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(120, 30, 160, 19));
        brightnessSlider->setMinimum(-12);
        brightnessSlider->setMaximum(12);
        brightnessSlider->setPageStep(1);
        brightnessSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(pictureedits);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 61, 16));
        label_3 = new QLabel(pictureedits);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 110, 46, 13));
        label_4 = new QLabel(pictureedits);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 140, 46, 13));
        label_5 = new QLabel(pictureedits);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 170, 46, 13));
        radioButton = new QRadioButton(pictureedits);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(120, 110, 82, 17));
        edgeButton = new QPushButton(pictureedits);
        edgeButton->setObjectName(QStringLiteral("edgeButton"));
        edgeButton->setGeometry(QRect(250, 70, 75, 23));
        contrastButton = new QPushButton(pictureedits);
        contrastButton->setObjectName(QStringLiteral("contrastButton"));
        contrastButton->setGeometry(QRect(30, 70, 75, 23));
        gammaButton = new QPushButton(pictureedits);
        gammaButton->setObjectName(QStringLiteral("gammaButton"));
        gammaButton->setGeometry(QRect(140, 70, 75, 23));
        smoothButton = new QPushButton(pictureedits);
        smoothButton->setObjectName(QStringLiteral("smoothButton"));
        smoothButton->setGeometry(QRect(180, 140, 75, 23));
        sharpenButton = new QPushButton(pictureedits);
        sharpenButton->setObjectName(QStringLiteral("sharpenButton"));
        sharpenButton->setGeometry(QRect(180, 170, 75, 23));

        retranslateUi(pictureedits);

        QMetaObject::connectSlotsByName(pictureedits);
    } // setupUi

    void retranslateUi(QWidget *pictureedits)
    {
        pictureedits->setWindowTitle(QApplication::translate("pictureedits", "Form", 0));
        smoothSpinBox->setSuffix(QApplication::translate("pictureedits", "%", 0));
        sharpenSpinBox->setSuffix(QApplication::translate("pictureedits", "%", 0));
        sharpenSpinBox->setPrefix(QString());
        label->setText(QApplication::translate("pictureedits", "Brightness", 0));
        label_3->setText(QApplication::translate("pictureedits", "Negate", 0));
        label_4->setText(QApplication::translate("pictureedits", "Smooth", 0));
        label_5->setText(QApplication::translate("pictureedits", "Sharpen", 0));
        radioButton->setText(QString());
        edgeButton->setText(QApplication::translate("pictureedits", "Edge", 0));
        contrastButton->setText(QApplication::translate("pictureedits", "Contrast", 0));
        gammaButton->setText(QApplication::translate("pictureedits", "Gamma", 0));
        smoothButton->setText(QApplication::translate("pictureedits", "Apply", 0));
        sharpenButton->setText(QApplication::translate("pictureedits", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class pictureedits: public Ui_pictureedits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREEDITS_H
