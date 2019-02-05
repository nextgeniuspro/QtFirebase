#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T23:28:49
#
#-------------------------------------------------

# For android target in main project assign
# ANDROID_PACKAGE_SOURCE_DIR variable to your
# manifest location

SOURCES += \
    $$PWD/platform.cpp \
    $$PWD/admmobinterstitial.cpp \
    $$PWD/admobbanner.cpp \
    $$PWD/analytics.cpp \
    $$PWD/firebase.cpp \
    $$PWD/authentification.cpp \
    $$PWD/qstringlist2cstyle.cpp \
    $$PWD/adrequest.cpp \
    $$PWD/user.cpp

OBJECTIVE_SOURCES += \
    $$PWD/platform.mm

HEADERS  += \
    $$PWD/platform.h \
    $$PWD/admmobinterstitial.h \
    $$PWD/admobbanner.h \
    $$PWD/analytics.h \
    $$PWD/firebase.h \
    $$PWD/authentification.h \
    $$PWD/types.h \
    $$PWD/qstringlist2cstyle.h \
    $$PWD/adrequest.h \
    $$PWD/user.h

INCLUDEPATH += \
    $$PWD/sdk/firebase_cpp_sdk/include

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
        -F$$PWD/sdk/firebase_cpp_sdk/frameworks/ios/universal \
        -framework firebase \
        -framework firebase_admob \
        -F$$PWD/sdk/Firebase/AdMob \
        -F$$PWD/sdk/Firebase/Analytics \
        -framework FirebaseCore \
        -framework GoogleMobileAds

# Analytics
contains(DEFINES, QTFIREBASE_ANALYTICS_ENABLED) {
    LIBS += \
        -framework firebase_analytics \
        -F$$PWD/sdk/Firebase/Analytics \
        -framework FIRAnalyticsConnector \
        -framework FirebaseAnalytics \
        -framework FirebaseCore \
        -framework FirebaseCoreDiagnostics \
        -framework FirebaseInstanceID \
        -framework GoogleAppMeasurement \
        -framework GoogleUtilities \
        -framework nanopb
}

# Authentification
contains(DEFINES, QTFIREBASE_AUTHENTIFICATION_ENABLED) {
    LIBS += \
        -framework firebase_auth \
        -F$$PWD/sdk/Firebase/Auth \
        -framework FirebaseAuth \
        -framework GTMSessionFetcher
}

} # ios

android: {
    QT += androidextras gui-private

    # link libraries
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        LIBPATH = $$PWD/sdk/firebase_cpp_sdk/libs/android/armeabi-v7a/c++
    }
    equals(ANDROID_TARGET_ARCH, armeabi-v8a) {
        LIBPATH = $$PWD/sdk/firebase_cpp_sdk/libs/android/armeabi-v8a/c++
    }
    equals(ANDROID_TARGET_ARCH, x86)  {
        LIBPATH = $$PWD/sdk/firebase_cpp_sdk/libs/android/x86/c++
    }

    LIBS += -L$$LIBPATH -lfirebase_app -lfirebase_admob
# Analytics
contains(DEFINES, QTFIREBASE_ANALYTICS_ENABLED) {
    LIBS += -lfirebase_analytics
}

    # Copy activity
    !exists($$ANDROID_PACKAGE_SOURCE_DIR/src/org/dreamdev/QtFirebase/QtFirebaseActivity.java)
    {
        copydata.commands += $(COPY_DIR) $$shell_path($$PWD/platform/android/src) $$shell_path($$ANDROID_PACKAGE_SOURCE_DIR)
    }

    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
} # android
