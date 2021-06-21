QT       += core gui charts #opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

#LIBS += -lopengl32
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS #QCUSTOMPLOT_USE_OPENGL

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./libs/QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./libs/QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./libs/QXlsx/source/  # current QXlsx source path is ./source/
include(./libs/QXlsx/QXlsx.pri)

win32 {
    #QMAKE_LFLAGS += /SUBSYSTEM:CONSOLE,5.01
    #QMAKE_CXX += /D_USING_V110_SDK71_
    LIBS *= -L"%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib"
    INCLUDEPATH += "%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include"
}

RC_ICONS = ./resources/Logos/logo.ico

SOURCES += \
    source/changelog.cpp \
    source/settingskeeper.cpp \
    source/atomconversion.cpp \
    source/banddata.cpp \
    source/basicgraphbuild.cpp \
    source/coloricondrawer.cpp \
    source/contour.cpp \
    source/crystaltopondconvertors.cpp \
    source/dosgraphbuilder.cpp \
    source/filedialogsload.cpp \
    source/fileread.cpp \
    source/filessaver.cpp \
    source/graphicsdata.cpp \
    source/helpmatrixwidget.cpp \
    source/helpwindow.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/mathsymbols.cpp \
    source/pdosparser.cpp \
    source/picturesettings.cpp \
    source/plotparameters.cpp \
    source/qcustomplot.cpp \
    source/surfdata.cpp \
    source/uiinit.cpp \
    source/zonestructgraphbuilder.cpp

HEADERS += \
    headers/changelog.h \
    headers/delegator.h \
    headers/settingsKeeper.h \
    headers/structuresHeaders.h \
    headers/atomconversion.h \
    headers/banddata.h \
    headers/basicgraphbuild.h \
    headers/coloricondrawer.h \
    headers/contour.h \
    headers/crystaltopondconvertors.h \
    headers/dosgraphbuilder.h \
    headers/filedialogsload.h \
    headers/fileread.h \
    headers/filessaver.h \
    headers/graphicsdata.h \
    headers/helpmatrixwidget.h \
    headers/helpwindow.h \
    headers/mainwindow.h \
    headers/mathsymbols.h \
    headers/pdosparser.h \
    headers/picturesettings.h \
    headers/plotparameters.h \
    headers/qcustomplot.h \
    headers/surfdata.h \
    ui_mainwindow.h \
    ui_picturesettings.h \
    headers/uiinit.h \
    headers/zonestructgraphbuilder.h

FORMS += \
    ui/changelog.ui \
    ui/mainwindow.ui\
    ui/picturesettings.ui

INCLUDEPATH += $$PWD/headers
INCLUDEPATH += $$PWD/ui
INCLUDEPATH += $$PWD/libs

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    translations/RU.ts \
    translations/EN.ts

RESOURCES += \
    resources/HELPS.qrc \
    resources/Logos.qrc

DISTFILES += \
    distfiles/qcustomplot.qch
