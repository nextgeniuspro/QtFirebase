#include "platform.h"
#include <QGuiApplication>

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <qpa/qplatformnativeinterface.h>
#include <UIKit/UIKit.h>

Platform::TWindow Platform::s_Window = 0;

Platform::Platform(QObject *parent) : QObject(parent)
{

}

Platform::TWindow Platform::window()
{
    if (!s_Window) {
        
        UIApplication *application = [UIApplication sharedApplication];
        NSArray *windows = [application windows];
        UIViewController * __block rootViewController = nil;
        [windows enumerateObjectsUsingBlock:^(UIWindow * _Nonnull window, NSUInteger, BOOL * _Nonnull stop) {
            rootViewController = [window rootViewController];
            *stop = (rootViewController != nil);
        }];
        s_Window = (__bridge  void*)rootViewController.view;
        
        //QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
        //s_Window = reinterpret_cast<void *>(interface->nativeResourceForWindow("uiview", QGuiApplication::focusWindow()));
    }
    return s_Window;
}

void Platform::setWindow(Platform::TWindow window)
{
    s_Window = window;
}

QSize Platform::statusBarSize()
{
    CGSize size = [UIApplication sharedApplication].statusBarFrame.size;
    return QSize(size.width, size.height);
}

float Platform::scaleFactor()
{
    return [UIScreen mainScreen].scale;
}

#endif // #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
