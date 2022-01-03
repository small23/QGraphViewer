/********************************************************************************
** Form generated from reading UI file 'changelog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGELOG_H
#define UI_CHANGELOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_changelog
{
public:
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QLabel *logo;

    void setupUi(QDialog *changelog)
    {
        if (changelog->objectName().isEmpty())
            changelog->setObjectName(QString::fromUtf8("changelog"));
        changelog->resize(408, 301);
        changelog->setMinimumSize(QSize(408, 301));
        changelog->setMaximumSize(QSize(408, 301));
        pushButton = new QPushButton(changelog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(324, 270, 81, 23));
        textBrowser = new QTextBrowser(changelog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(80, 10, 321, 251));
        logo = new QLabel(changelog);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(10, 10, 71, 61));

        retranslateUi(changelog);

        QMetaObject::connectSlotsByName(changelog);
    } // setupUi

    void retranslateUi(QDialog *changelog)
    {
        changelog->setWindowTitle(QCoreApplication::translate("changelog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("changelog", "\320\224\320\260 \320\277\320\276\320\275\321\217\320\273 \321\217...", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("changelog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">1.1 - Wat, you still use this?!</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\236\320\261\321\211\320\270\320\265 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\233\320\236\320\232\320\220\320\233\320\230\320\227"
                        "\320\220\320\246\320\230\320\257 \320\237\320\236\320\224\320\252\320\225\320\245\320\220\320\233\320\220!</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- 64-\321\205 \320\261\320\270\321\202\320\275\320\260\321\217 \320\262\320\265\321\200\321\201\320\270\321\217</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\236\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\260</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 \321\202\320\265\320\277\320\265\321\200\321\214 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\320\276 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\216\321\202\321\201\321"
                        "\217 \320\275\320\260 \320\264\320\270\321\201\320\277\320\273\320\265\321\217\321\205 \321\201 \320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\276\320\274 \320\261\320\276\320\273\321\214\321\210\320\265 100%</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\222\320\275\321\203\321\202\321\200\320\265\320\275\320\275\321\217\321\217 \320\272\321\203\321\205\320\275\321\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\275\321\213\320\265 \320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\272\320\270 \320\272\320\276\320\264\320\276\320\262\320\276\320\271 \320\261\320\260\320\267\321\213:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-- \320"
                        "\240\320\265\320\276\321\200\320\263\320\260\320\275\320\270\320\267\320\276\320\262\320\260\320\275\320\276 \321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\321\205 \321\204\320\260\320\271\320\273\320\276\320\262</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-- \320\236\321\204\320\276\321\200\320\274\320\273\320\265\320\275\320\270\320\265 \320\272\320\276\320\264\320\260 \320\277\321\200\320\270\320\262\320\265\320\264\320\265\320\275\320\276 \320\272 \320\265\320\264\320\270\320\275\320\276\320\276\320\261\321\200\320\260\320\267\320\275\320\276\320\274\321\203 \321\201\321\202\320\260\320\275\320\264\320\260\321\200\321\202\321\203 CammelCase</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-- \320\243\321\201\321\202\321\200\320\260\320\275\320\265\320\275\320\276 \320\274"
                        "\320\275\320\276\320\266\320\265\321\201\321\202\320\262\320\276 \320\277\320\276\321\202\320\265\320\275\321\206\320\270\320\260\320\273\321\214\320\275\321\213\321\205 \321\203\321\202\320\265\321\207\320\265\320\272 \320\277\320\260\320\274\321\217\321\202\320\270</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-- \320\237\320\265\321\200\320\265\320\264\320\265\320\273\320\260\320\275\321\213 \320\272\320\273\320\260\321\201\321\201\321\213 \320\276\321\202\321\200\320\270\321\201\320\276\320\262\320\272\320\270 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262, \321\202\320\265\320\277\320\265\321\200\321\214 \320\275\320\260\321\201\320\273\320\265\320\264\320\270\320\265 \320\270 \320\236\320\236\320\237</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\235\320\265\320\274\320\275\320\276\320\263\320\276 \321\203\320\262\320"
                        "\265\320\273\320\270\321\207\320\265\320\275\320\260 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \321\200\320\260\320\261\320\276\321\202\321\213 \320\277\321\200\320\270\320\273\320\276\320\266\320\265\320\275\320\270\321\217</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\237\320\265\321\200\320\265\320\265\320\267\320\264 \320\275\320\260 MSVC2019</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\237\320\265\321\200\320\265\320\265\320\267\320\264 \320\275\320\260 Windows SDK 10.0.20348.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\236\320\261\320\275\320\276\320\262\320\273\320\265\320\275\320\270\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270 QCustomPlot \320\264\320\276 \320\262\320"
                        "\265\321\200\321\201\320\270\320\270 2.1.0</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">1.0.2 - La Grande Finale!</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\221\320\260\320\263\321\204\320\270\320\272\321\201\321\213</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">1.0.1 - La Grande Finale!</span></p>\n"
"<p style=\" margin-top:0px; margin"
                        "-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\230\321\201\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\276 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \321\207\320\265\320\272-\320\261\320\276\320\272\321\201\320\276\320\262 \320\262\321\213\320\261\320\276\321\200\320\260 \321\203\321\200\320\276\320\262\320\275\321\217 \320\244\320\265\321\200\320\274\320\270</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\237\320\265\321\200\320\265\320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\275\321\213 \320\264\320\265\321\204\320\276\320\273\321\202\320\275\321\213\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\277\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\321\217 \320\275\320\260 2 \320\262\320\272\320\273\320\260\320\264\320\272\320\265</p>\n"
"<p sty"
                        "le=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\222\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\213\320\265 \320\264\320\273\321\217 \320\277\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\321\217 \320\263\321\200\320\260\321\204\320\270\320\272\320\270 \320\262 DOS\\COOP\\COHP \321\202\320\265\320\277\320\265\321\200\321\214 \320\277\320\276\320\264\321\201\320\262\320\265\321\207\320\270\320\262\320\260\321\216\321\202\321\201\321\217 \320\262 \320\262\321\213\320\277\320\260\320\264\320\260\321\216\321\211\320\265\320\274 \321\201\320\277\320\270\321\201\320\272\320\265</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\225\321\201\320\273\320\270 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275 \320\275\320\270 \320\276\320\264\320\270\320\275 \320\263\321\200\320\260\321\204\320\270\320\272 \320\262 "
                        "DOS\\COOP\\COHP \320\261\321\203\320\264\320\265\321\202 \321\201\321\202\321\200\320\276\320\270\321\202\321\214\321\201\321\217 \321\202\320\265\320\272\321\203\321\211\320\270\320\271 \320\262\321\213\320\261\321\200\320\260\320\275\321\213\320\271</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">1.0 - La Grande Finale!</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- \320\237\320\265\321\200\320\262\321\213\320\271 \321\200\320\265\320\273\320\270\320\267</p></body></html>", nullptr));
        logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class changelog: public Ui_changelog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGELOG_H
