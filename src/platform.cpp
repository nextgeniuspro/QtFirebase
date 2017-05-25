#include "platform.h"
#include <QGuiApplication>

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#if defined(__ANDROID__)
#include <qpa/qplatformnativeinterface.h>

Platform::TWindow Platform::s_Window = 0;
#else
Platform::TWindow Platform::s_Window;
#endif

Platform::Platform(QObject *parent) : QObject(parent)
{

}

Platform::TWindow Platform::window()
{
    if (!s_Window) {
#if defined(__ANDROID__)
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    s_Window = (jobject)interface->nativeResourceForIntegration("QtActivity");
#endif
    }
    return s_Window;
}

void Platform::setWindow(Platform::TWindow window)
{
    s_Window = window;
}

QSize Platform::statusBarSize()
{
    // TODO: Add implementation
    return QSize();
}

#endif // #if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
