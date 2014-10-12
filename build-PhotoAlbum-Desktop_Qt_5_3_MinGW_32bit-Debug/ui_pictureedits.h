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
    QSlider *contrastSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSlider *gammaSlider;
    QRadioButton *radioButton;
    QPushButton *edgeButton;

    void setupUi(QWidget *pictureedits)
    {
        if (pictureedits->objectName().isEmpty())
            pictureedits->setObjectName(QStringLiteral("pictureedits"));
        pictureedits->resize(400, 300);
        smoothSpinBox = new QSpinBox(pictureedits);
        smoothSpinBox->setObjectName(QStringLiteral("smoothSpinBox"));
        smoothSpinBox->setGeometry(QRect(120, 190, 42, 22));
        smoothSpinBox->setSingleStep(10);
        sharpenSpinBox = new QSpinBox(pictureedits);
        sharpenSpinBox->setObjectName(QStringLiteral("sharpenSpinBox"));
        sharpenSpinBox->setGeometry(QRect(120, 220, 42, 22));
        sharpenSpinBox->setSingleStep(10);
        brightnessSlider = new QSlider(pictureedits);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setGeometry(QRect(120, 30, 160, 19));
        brightnessSlider->setMinimum(-12);
        brightnessSlider->setMaximum(12);
        brightnessSlider->setPageStep(1);
        brightnessSlider->setOrientation(Qt::Horizontal);
        contrastSlider = new QSlider(pictureedits);
        contrastSlider->setObjectName(QStringLiteral("contrastSlider"));
        contrastSlider->setGeometry(QRect(120, 60, 160, 19));
        contrastSlider->setMinimum(-12);
        contrastSlider->setMaximum(12);
        contrastSlider->setPageStep(1);
        contrastSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(pictureedits);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 61, 16));
        label_2 = new QLabel(pictureedits);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 46, 13));
        label_3 = new QLabel(pictureedits);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 160, 46, 13));
        label_4 = new QLabel(pictureedits);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 190, 46, 13));
        label_5 = new QLabel(pictureedits);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 220, 46, 13));
        label_6 = new QLabel(pictureedits);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 90, 46, 13));
        gammaSlider = new QSlider(pictureedits);
        gammaSlider->setObjectName(QStringLiteral("gammaSlider"));
        gammaSlider->setGeometry(QRect(120, 90, 160, 19));
        gammaSlider->setMinimum(-12);
        gammaSlider->setMaximum(12);
        gammaSlider->setPageStep(1);
        gammaSlider->setOrientation(Qt::Horizontal);
        radioButton = new QRadioButton(pictureedits);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(120, 160, 82, 17));
        edgeButton = new QPushButton(pictureedits);
        edgeButton->setObjectName(QStringLiteral("edgeButton"));
        edgeButton->setGeometry(QRect(30, 120, 75, 23));

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
        label_2->setText(QApplication::translate("pictureedits", "Contrast", 0));
        label_3->setText(QApplication::translate("pictureedits", "Negate", 0));
        label_4->setText(QApplication::translate("pictureedits", "Smooth", 0));
        label_5->setText(QApplication::translate("pictureedits", "Sharpen", 0));
        label_6->setText(QApplication::translate("pictureedits", "Gamma", 0));
        radioButton->setText(QString());
        edgeButton->setText(QApplication::translate("pictureedits", "Edge", 0));
    } // retranslateUi

};

namespace Ui {
    class pictureedits: public Ui_pictureedits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREEDITS_H
