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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_PictureSettings
{
public:
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
    QRadioButton *pdfRadioButton;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QPushButton *resetScaleTButton;
    QLabel *label_8;
    QSlider *scaleSliderT;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QDialog *PictureSettings)
    {
        if (PictureSettings->objectName().isEmpty())
            PictureSettings->setObjectName(QString::fromUtf8("PictureSettings"));
        PictureSettings->resize(340, 200);
        PictureSettings->setMinimumSize(QSize(340, 200));
        PictureSettings->setMaximumSize(QSize(340, 200));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        PictureSettings->setFont(font);
        scaleSlider = new QSlider(PictureSettings);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setGeometry(QRect(131, 15, 151, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        scaleSlider->setFont(font1);
        scaleSlider->setMinimum(1);
        scaleSlider->setMaximum(11);
        scaleSlider->setValue(6);
        scaleSlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(PictureSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(112, 37, 51, 16));
        label_2->setFont(font1);
        label_3 = new QLabel(PictureSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(252, 37, 51, 16));
        label_3->setFont(font1);
        resetScaleButton = new QPushButton(PictureSettings);
        resetScaleButton->setObjectName(QString::fromUtf8("resetScaleButton"));
        resetScaleButton->setGeometry(QRect(312, 15, 21, 23));
        resetScaleButton->setFont(font1);
        qualitySlider = new QSlider(PictureSettings);
        qualitySlider->setObjectName(QString::fromUtf8("qualitySlider"));
        qualitySlider->setGeometry(QRect(131, 55, 151, 22));
        qualitySlider->setFont(font1);
        qualitySlider->setMinimum(40);
        qualitySlider->setMaximum(100);
        qualitySlider->setValue(90);
        qualitySlider->setOrientation(Qt::Horizontal);
        label = new QLabel(PictureSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(18, 54, 105, 21));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(PictureSettings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(2, 8, 121, 31));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        resetQualityButton = new QPushButton(PictureSettings);
        resetQualityButton->setObjectName(QString::fromUtf8("resetQualityButton"));
        resetQualityButton->setGeometry(QRect(312, 55, 21, 23));
        resetQualityButton->setFont(font1);
        label_5 = new QLabel(PictureSettings);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(112, 77, 51, 16));
        label_5->setFont(font1);
        label_6 = new QLabel(PictureSettings);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(252, 77, 51, 16));
        label_6->setFont(font1);
        pngRadioButton = new QRadioButton(PictureSettings);
        pngRadioButton->setObjectName(QString::fromUtf8("pngRadioButton"));
        pngRadioButton->setGeometry(QRect(126, 136, 51, 21));
        pngRadioButton->setFont(font1);
        jpgRadioButton = new QRadioButton(PictureSettings);
        jpgRadioButton->setObjectName(QString::fromUtf8("jpgRadioButton"));
        jpgRadioButton->setGeometry(QRect(176, 136, 51, 21));
        jpgRadioButton->setFont(font1);
        bmpRadioButton = new QRadioButton(PictureSettings);
        bmpRadioButton->setObjectName(QString::fromUtf8("bmpRadioButton"));
        bmpRadioButton->setGeometry(QRect(226, 136, 51, 21));
        bmpRadioButton->setFont(font1);
        label_7 = new QLabel(PictureSettings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(56, 135, 61, 21));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pdfRadioButton = new QRadioButton(PictureSettings);
        pdfRadioButton->setObjectName(QString::fromUtf8("pdfRadioButton"));
        pdfRadioButton->setGeometry(QRect(276, 136, 51, 21));
        pdfRadioButton->setFont(font1);
        cancelButton = new QPushButton(PictureSettings);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(248, 164, 80, 23));
        cancelButton->setFont(font1);
        okButton = new QPushButton(PictureSettings);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(164, 164, 80, 23));
        okButton->setFont(font1);
        resetScaleTButton = new QPushButton(PictureSettings);
        resetScaleTButton->setObjectName(QString::fromUtf8("resetScaleTButton"));
        resetScaleTButton->setGeometry(QRect(312, 93, 21, 23));
        resetScaleTButton->setFont(font1);
        label_8 = new QLabel(PictureSettings);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 92, 113, 21));
        label_8->setFont(font1);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        scaleSliderT = new QSlider(PictureSettings);
        scaleSliderT->setObjectName(QString::fromUtf8("scaleSliderT"));
        scaleSliderT->setGeometry(QRect(131, 93, 151, 22));
        scaleSliderT->setFont(font1);
        scaleSliderT->setMinimum(3);
        scaleSliderT->setMaximum(9);
        scaleSliderT->setSingleStep(1);
        scaleSliderT->setPageStep(1);
        scaleSliderT->setValue(6);
        scaleSliderT->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(PictureSettings);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(112, 115, 51, 16));
        label_9->setFont(font1);
        label_10 = new QLabel(PictureSettings);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(252, 115, 51, 16));
        label_10->setFont(font1);

        retranslateUi(PictureSettings);
        QObject::connect(okButton, SIGNAL(clicked()), PictureSettings, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), PictureSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(PictureSettings);
    } // setupUi

    void retranslateUi(QDialog *PictureSettings)
    {
        PictureSettings->setWindowTitle(QCoreApplication::translate("PictureSettings", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\265\320\275\321\214\321\210\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("PictureSettings", "\320\221\320\276\320\273\321\214\321\210\320\265", nullptr));
        resetScaleButton->setText(QCoreApplication::translate("PictureSettings", "\320\245", nullptr));
        label->setText(QCoreApplication::translate("PictureSettings", "\320\232\320\260\321\207\320\265\321\201\321\202\320\262\320\276 (JPG)", nullptr));
        label_4->setText(QCoreApplication::translate("PictureSettings", "\320\240\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260", nullptr));
        resetQualityButton->setText(QCoreApplication::translate("PictureSettings", "\320\245", nullptr));
        label_5->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\265\320\275\321\214\321\210\320\265", nullptr));
        label_6->setText(QCoreApplication::translate("PictureSettings", "\320\221\320\276\320\273\321\214\321\210\320\265", nullptr));
        pngRadioButton->setText(QCoreApplication::translate("PictureSettings", "PNG", nullptr));
        jpgRadioButton->setText(QCoreApplication::translate("PictureSettings", "JPG", nullptr));
        bmpRadioButton->setText(QCoreApplication::translate("PictureSettings", "BMP", nullptr));
        label_7->setText(QCoreApplication::translate("PictureSettings", "\320\244\320\276\321\200\320\274\320\260\321\202", nullptr));
        pdfRadioButton->setText(QCoreApplication::translate("PictureSettings", "PDF", nullptr));
        cancelButton->setText(QCoreApplication::translate("PictureSettings", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        okButton->setText(QCoreApplication::translate("PictureSettings", "OK", nullptr));
        resetScaleTButton->setText(QCoreApplication::translate("PictureSettings", "\320\245", nullptr));
        label_8->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261 \320\263\321\200\320\260\321\204\320\270\320\272\320\260", nullptr));
        label_9->setText(QCoreApplication::translate("PictureSettings", "\320\234\320\265\320\275\321\214\321\210\320\265", nullptr));
        label_10->setText(QCoreApplication::translate("PictureSettings", "\320\221\320\276\320\273\321\214\321\210\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PictureSettings: public Ui_PictureSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURESETTINGS_H
