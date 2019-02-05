#ifndef QFBPLATFORM_H
#define QFBPLATFORM_H

#include <QObject>
#include "types.h"

namespace qfb {

class Platform : public QObject
{
    Q_OBJECT
public:
    /*
     * Default constructor
     */
    explicit Platform(QObject *parent = nullptr);

    /*
     * Return platform specific window
     */
    static TWindow window();

    /*
     * Setup external platform specific window
     */
    static void setWindow(TWindow window);

    /*
     * Banner status bar offset
     */
     static int bannerStatusBarYOffset();
    
    /*
     * Device scale factor
     */
    static float scaleFactor();

private:
    static TWindow s_Window;
};

} // namespace qfb

#endif // QFBPLATFORM_H
