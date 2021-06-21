/********************************************************************************
** Form generated from reading UI file 'picturesettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURESETTINGS_H
#define UI_PICTURESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PictureSettings
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSlider *scaleSlider;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *resetScaleButton;
    QSlider *qualitySlider;
    QLabel *label;
    QLabel *label_4;
    QPushButton *resetQualityButton;
    QLabel *label_5;
    QLabel *label_6;
    QRadioButton *pngRadioButton;
    QRadioButton *jpgRadioButton;
    QRadioButton *bmpRadioButton;
    QLabel *label_7;

    void setupUi(QDialog *PictureSettings)
    {
        if (PictureSettings->objectName().isEmpty())
            PictureSettings->setObjectName(QString::fromUtf8("PictureSettings"));
        PictureSettings->resize(325, 176);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        PictureSettings->setFont(font);
        layoutWidget = new QWidget(PictureSettings);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 135, 281, 33));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        layoutWidget->setFont(font1);
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setFont(font1);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setFont(font1);

        hboxLayout->addWidget(cancelButton);

        scaleSlider = new QSlider(PictureSettings);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setGeometry(QRect(99, 15, 151, 22));
        scaleSlider->setFont(font1);
        scaleSlider->setMinimum(1);
        scaleSlider->setMaximum(11);
        scaleSlider->setValue(6);
        scaleSlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(PictureSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 37, 51, 16));
        label_2->setFont(font1);
        label_3 = new QLabel(PictureSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 37, 51, 16));
        label_3->setFont(font1);
        resetScaleButton = new QPushButton(PictureSettings);
        resetScaleButton->setObjectName(QString::fromUtf8("resetScaleButton"));
        resetScaleButton->setGeometry(QRect(280, 15, 21, 23));
        resetScaleButton->setFont(font1);
        qualitySlider = new QSlider(PictureSettings);
        qualitySlider->setObjectName(QString::fromUtf8("qualitySlider"));
        qualitySlider->setGeometry(QRect(99, 55, 151, 22));
        qualitySlider->setFont(font1);
        qualitySlider->setMinimum(40);
        qualitySlider->setMaximum(100);
        qualitySlider->setValue(90);
        qualitySlider->setOrientation(Qt::Horizontal);
        label = new QLabel(PictureSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 54, 91, 21));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(PictureSettings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 8, 81, 31));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        resetQualityButton = new QPushButton(PictureSettings);
        resetQualityButton->setObjectName(QString::fromUtf8("resetQualityButton"));
        resetQualityButton->setGeometry(QRect(280, 55, 21, 23));
        resetQualityButton->setFont(font1);
        label_5 = new QLabel(PictureSettings);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 77, 51, 16));
        label_5->setFont(font1);
        label_6 = new QLabel(PictureSettings);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(220, 77, 51, 16));
        label_6->setFont(font1);
        pngRadioButton = new QRadioButton(PictureSettings);
        pngRadioButton->setObjectName(QString::fromUtf8("pngRadioButton"));
        pngRadioButton->setGeometry(QRect(110, 101, 51, 21));
        pngRadioButton->setFont(font1);
        jpgRadioButton = new QRadioButton(PictureSettings);
        jpgRadioButton->setObjectName(QString::fromUtf8("jpgRadioButton"));
        jpgRadioButton->setGeometry(QRect(160, 101, 51, 21));
        jpgRadioButton->setFont(font1);
        bmpRadioButton = new QRadioButton(PictureSettings);
        bmpRadioButton->setObjectName(QString::fromUtf8("bmpRadioButton"));
        bmpRadioButton->setGeometry(QRect(210, 101, 51, 21));
        bmpRadioButton->setFont(font1);
        label_7 = new QLabel(PictureSettings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 100, 61, 21));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(PictureSettings);
        QObject::connect(okButton, SIGNAL(clicked()), PictureSettings, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PictureSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(PictureSettings);
    } // setupUi

    void retranslateUi(QDialog *PictureSettings)
    {
        PictureSettings->setWindowTitle(QCoreApplication::translate("PictureSettings", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("PictureSettings", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("PictureSettings", "Cancel", nullptr));
        label_2->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\265\320\275\321\214\321\210\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("PictureSettings", "\320\221\320\276\320\273\321\214\321\210\320\265", nullptr));
        resetScaleButton->setText(QCoreApplication::translate("PictureSettings", "\320\245", nullptr));
        label->setText(QCoreApplication::translate("PictureSettings", "\320\232\320\260\321\207\320\265\321\201\321\202\320\262\320\276 (JPG)", nullptr));
        label_4->setText(QCoreApplication::translate("PictureSettings", "\320\240\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        resetQualityButton->setText(QCoreApplication::translate("PictureSettings", "\320\245", nullptr));
        label_5->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\265\320\275\321\214\321\210\320\265", nullptr));
        label_6->setText(QCoreApplication::translate("PictureSettings", "\320\221\320\276\320\273\321\214\321\210\320\265", nullptr));
        pngRadioButton->setText(QCoreApplication::translate("PictureSettings", "PNG", nullptr));
        jpgRadioButton->setText(QCoreApplication::translate("PictureSettings", "JPG", nullptr));
        bmpRadioButton->setText(QCoreApplication::translate("PictureSettings", "BMP", nullptr));
        label_7->setText(QCoreApplication::translate("PictureSettings", "\320\244\320\276\321\200\320\274\320\260\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PictureSettings: public Ui_PictureSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURESETTINGS_H
