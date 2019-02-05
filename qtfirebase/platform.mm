#include "platform.h"
#include <QGuiApplication>

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <qpa/qplatformnativeinterface.h>
#include <UIKit/UIKit.h>
#include <QStandardPaths>

using namespace qfb;



TWindow Platform::s_Window = 0;

Platform::Platform(QObject *parent) : QObject(parent)
{

}

TWindow Platform::window()
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
    }
    return s_Window;
}

void Platform::setWindow(TWindow window)
{
    s_Window = window;
}

int Platform::bannerStatusBarYOffset()
{
    return static_cast<int>([UIApplication sharedApplication].statusBarFrame.size.height);
}

float Platform::scaleFactor()
{
    return [UIScreen mainScreen].scale;
}

const QString& Platform::documentsPath()
{
    static QString defaultDir = QStandardPaths::standardLocations(QStandardPaths::TempLocation).value(0);
    return defaultDir;
}

#endif // #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
