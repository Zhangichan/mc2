#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T09:45:35
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = PagesTextEdit
TARGET = OFD_design
TEMPLATE = app

QT += printsupport

LIBS += -L./quazip/ -lquazip5
INCLUDEPATH +=  ./quazip
DEPENDPATH += ./quazip


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    PagesTextEdit.cpp \
    PageMetrics.cpp

HEADERS  += mainwindow.h \
    widget.h \
    PagesTextEdit.h \
    PageMetrics.h

RESOURCES += \
    myimages.qrc

FORMS += \
    mainwindow.ui
