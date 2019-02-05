#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T11:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFirebase
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

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/platform/android
IOS_PACKAGE_SOURCE_DIR = $$PWD/platform/ios
DEFINES += QTFIREBASE_ADMOB_ENABLED QTFIREBASE_ANALYTICS_ENABLED QTFIREBASE_AUTHENTIFICATION_ENABLED
include(QtFirebase/QtFirebase.pri)

# Core
ios: {
    QMAKE_IOS_DEPLOYMENT_TARGET = 8.0
    QMAKE_IOS_TARGETED_DEVICE_FAMILY = 1,2
    QMAKE_INFO_PLIST = $$IOS_PACKAGE_SOURCE_DIR/Info.plist

    BUNDLE.files = $$IOS_PACKAGE_SOURCE_DIR/GoogleService-Info.plist
    QMAKE_BUNDLE_DATA += BUNDLE
}

android: {
    DISTFILES += \
        $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml \
        $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.jar \
        $$ANDROID_PACKAGE_SOURCE_DIR/gradlew \
        $$ANDROID_PACKAGE_SOURCE_DIR/res/values/libs.xml \
        $$ANDROID_PACKAGE_SOURCE_DIR/build.gradle \
        $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.properties \
        $$ANDROID_PACKAGE_SOURCE_DIR/gradlew.bat \
        $$ANDROID_PACKAGE_SOURCE_DIR/src/org/dreamdev/QtFirebase/QtFirebaseActivity.java
}
