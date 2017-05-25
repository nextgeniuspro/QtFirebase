#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T11:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFirebaseWidgets
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


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DEFINES += QTFIREBASE_ADMOB_ENABLED QTFIREBASE_ANALYTICS_ENABLED

QTFIREBASE_CPP_SDK_PATH = $$PWD/../../sdk/firebase_cpp_sdk
QTFIREBASE_IOS_SDK_PATH = $$PWD/../../sdk/Firebase

include($$PWD/../../QtFirebase.pri)

ios: {
    QMAKE_IOS_DEPLOYMENT_TARGET = 7.0
    QMAKE_IOS_TARGETED_DEVICE_FAMILY = 1,2

    GOOGLE_SERVICE_INFO.files = $$PWD/../platform/ios/GoogleService-Info.plist
    GOOGLE_SERVICE_INFO.path = /
    QMAKE_BUNDLE_DATA += GOOGLE_SERVICE_INFO
}
