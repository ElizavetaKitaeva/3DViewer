QT       += core gui svg openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affine.c \
    glscene.cpp \
    main.cpp \
    mainwindow.cpp \
    parsSavedSettings.c \
    settings.cpp \
    fileReader.c


HEADERS += \
    affine.h \
    glscene.h \
    mainwindow.h \
    parsSavedSettings.h \
    settings.h \
    fileReader.h


FORMS += \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc

DISTFILES += \
    savedSettings.txt

DEFINES += SETTINGSNAME=\\\"$(HOME)/Desktop/3DViewerSettings.txt\\\"

SUBDIRS += \
    QtGifImage/gifimage.pro


