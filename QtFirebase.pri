#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T11:52:30
#
#-------------------------------------------------

SOURCES += $$PWD/src/qtfirebase.cpp \
    $$PWD/src/platform.cpp \
    $$PWD/src/platform.mm \
    $$PWD/src/qtadmobbanner.cpp \
    $$PWD/src/qtadmmobinterstitial.cpp \
    $$PWD/src/qtanalytics.cpp

HEADERS  += $$PWD/include/qtfirebase.h \
    $$PWD/include/platform.h \
    $$PWD/include/qtadmobbanner.h \
    $$PWD/include/qtadmmobinterstitial.h \
    $$PWD/include/qtanalytics.h

INCLUDEPATH += $$PWD/include \
        $$QTFIREBASE_CPP_SDK_PATH/include

# Core
ios: {
    QMAKE_CXXFLAGS += -fobjc-arc
    QMAKE_CFLAGS += -fobjc-arc
    QT += gui_private
    QMAKE_LFLAGS += -ObjC
    LIBS += \
        -lsqlite3 -lz \
        -framework AVFoundation \
        -framework AudioToolbox \
        -framework CoreTelephony \
        -framework MessageUI \
        -framework SystemConfiguration \
        -framework CoreGraphics \
        -framework AdSupport \
        -framework StoreKit \
        -framework EventKit \
        -framework EventKitUI \
        -framework CoreMedia \
        -framework CFNetwork \
        -framework CoreVideo \
        -framework MediaPlayer \
        -framework CoreMotion \
        -framework GLKit \
        -F$$QTFIREBASE_CPP_SDK_PATH/frameworks/ios/universal \
        -framework firebase \
}

# AdMob
contains(DEFINES, QTFIREBASE_ADMOB_ENABLED) {
    ios: {
        LIBS += \
            -framework firebase_admob \
            -F$$QTFIREBASE_IOS_SDK_PATH/AdMob \
            -F$$QTFIREBASE_IOS_SDK_PATH/Analytics \
            -framework FirebaseCore \
            -framework GoogleMobileAds
    }
}

# Analytics
contains(DEFINES, QTFIREBASE_ANALYTICS_ENABLED) {
    ios: {
        LIBS += \
            -framework firebase_analytics \
            -F$$QTFIREBASE_IOS_SDK_PATH/Analytics \
            -framework FirebaseCore \
            -framework FirebaseAnalytics \
            -framework FirebaseInstanceID \
            -framework GoogleToolboxForMac
    }
}
