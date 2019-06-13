#include "platform.h"
#include <QGuiApplication>

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#if defined(__ANDROID__)
#include <qpa/qplatformnativeinterface.h>

TWindow Platform::s_Window = nullptr;
#else
TWindow Platform::s_Window;
#endif

using namespace qfb;



Platform::Platform(QObject *parent) : QObject(parent)
{

}

Platform::TWindow Platform::window()
{
    if (!s_Window) {
#if defined(__ANDROID__)
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    s_Window = static_cast<jobject>(interface->nativeResourceForIntegration("QtActivity"));
#endif
    }
    return s_Window;
}

void Platform::setWindow(Platform::TWindow window)
{
    s_Window = window;
}

int Platform::bannerStatusBarYOffset()
{
    // Android doesn't allow to show banner overlapped with status bar
    return 0;
}

float Platform::scaleFactor()
{
    return 1.0f;
}

const QString& Platform::documentsPath()
{
#if defined(__ANDROID__)
    static QString defaultDir;
    if (defaultDir.isEmpty())
    {
        QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
        defaultDir = mediaDir.toString();
    }
#else
    static QString defaultDir = "/";
#endif
    
    return defaultDir;
}

#endif // #if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
