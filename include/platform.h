#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

#if defined(__ANDROID__)
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#endif

class Platform : public QObject
{
    Q_OBJECT
public:
#if defined(__ANDROID__)
    typedef jobject TWindow;
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    typedef void* TWindow;
#else
    typedef void TWindow;
#endif

    /*
     * Default constructor
     */
    explicit Platform(QObject *parent = 0);

    /*
     * Return platform specific window
     */
    static TWindow window();

    /*
     * Setup external platform specific window
     */
    static void setWindow(TWindow window);

    /*
     * Get size for status bar
     */
    static QSize statusBarSize();
    
    /*
     * Returns device scale factor
     */
    static float scaleFactor();

private:
    static TWindow s_Window;
};

#endif // PLATFORM_H
