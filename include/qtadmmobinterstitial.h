#if defined(QTFIREBASE_ADMOB_ENABLED)

#ifndef QTADMMOBINTERSTITIAL_H
#define QTADMMOBINTERSTITIAL_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include "firebase/future.h"

namespace firebase {
    namespace admob {
        class InterstitialAd;
    }
}

class QtAdmMobInterstitial : public QObject
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(bool isReady READ isReady NOTIFY ready)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)

    Q_OBJECT
public:
    /*
     * Constructor
     */
    explicit QtAdmMobInterstitial(QObject *parent = 0);

    /*
     * Destructor
     */
    ~QtAdmMobInterstitial();

    /*
     * Set interstitial id
     */
    void setUnitId(const QString& unitId);
    
    /*
     * Get interstitial id
     */
    QString unitId() const;

    /*
     * Show interstitial
     */
    Q_INVOKABLE void show();

    /*
     * Is initialization done
     */
    bool isReady();

    /*
     * Is banner loaded
     */
    bool isLoaded();

signals:
    void unitIdChanged();
    void ready();
    void loaded();
    void loading();

private:
    void initialize(char* unitId);
    void cleanup();
    static void onInitCompletionCallback(const firebase::Future<void>& future, void* userData);
    static void onLoadCompletionCallback(const firebase::Future<void>& future, void* userData);

private:
    firebase::admob::InterstitialAd* m_Interstitial;
    char* m_UnitId;
    bool m_IsVisible;
};

#endif // QTADMMOBINTERSTITIAL_H

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
