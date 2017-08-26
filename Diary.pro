#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T13:58:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diary
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        diarywindow.cpp \
    database.cpp \
    userdata.cpp \
    pugixml.cpp

HEADERS += \
        diarywindow.hpp \
    database.hpp \
    userdata.hpp \
    pugiconfig.hpp \
    pugixml.hpp

FORMS += \
        diarywindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/boost/boost_1_64_0/stage/lib/ -lboost_filesystem-vc141-mt-gd-1_64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/boost/boost_1_64_0/stage/lib/ -lboost_filesystem-vc141-mt-gd-1_64

INCLUDEPATH += $$PWD/../../libs/boost/boost_1_64_0
DEPENDPATH += $$PWD/../../libs/boost/boost_1_64_0
