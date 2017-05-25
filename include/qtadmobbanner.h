#if defined(QTFIREBASE_ADMOB_ENABLED)

#ifndef QtAdMobBanner_H
#define QtAdMobBanner_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include "firebase/future.h"

namespace firebase {
    namespace admob {
        class BannerView;
    }
}

class QtAdMobBanner : public QObject
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool isReady READ isReady NOTIFY ready)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)

    Q_OBJECT
public:
    /*
     * Constructor
     */
    explicit QtAdMobBanner(QObject *parent = 0);

    /*
     * Destructor
     */
    ~QtAdMobBanner();

    /*
     * Get banner id
     */
    QString unitId() const;
    
    /*
     * Set banner id
     */
    void setUnitId(const QString& unitId);

    /*
     * Set banner size in pixels
     */
    void setSize(const QSize& size);
    
    /*
     * Get banner size in pixels
     */
    QSize size();

    /*
     * Setup banner position
     */
    void setPosition(const QPoint& position);

    /*
     * Retrieve banner position
     */
    const QPoint& position() const;

    /*
     * Show banner
     */
    void setVisible(bool isVisible);

    /*
     * Is banner showed
     */
    bool visible();

    /*
     * Is initialization donw
     */
    bool isReady();

    /*
     * Is banner loaded
     */
    bool isLoaded();

signals:
    void unitIdChanged();
    void sizeChanged();
    void positionChanged();
    void visibleChanged();
    void ready();
    void loaded();
    void loading();

private:
    void tryInitialze();
    void initialize(char* unitId, const QSize& size);
    void cleanup();
    static void onInitCompletionCallback(const firebase::Future<void>& future, void* userData);
    static void onLoadCompletionCallback(const firebase::Future<void>& future, void* userData);

private:
    firebase::admob::BannerView* m_BannerView;
    char *m_UnitId;
    QSize m_Size;
    enum InitStates{
        UnitIdReady = 0x01,
        SizeReady = 0x02,
        InitializationReady = UnitIdReady | SizeReady
    };
    int m_InitState;
    QPoint m_Position;
    bool m_IsVisible;
};

#endif // QtAdMobBanner_H

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
