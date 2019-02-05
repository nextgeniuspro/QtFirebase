#if defined(QTFIREBASE_ADMOB_ENABLED)

#ifndef QFBADMMOBINTERSTITIAL_H
#define QFBADMMOBINTERSTITIAL_H

#include <QObject>
#include <QPoint>
#include <QSize>

namespace firebase {
    namespace admob {
        class InterstitialAd;
    }
    template <typename ResultType> class Future;
}

namespace qfb {

class AdRequest;

class AdmMobInterstitial : public QObject
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(bool isReady READ isReady NOTIFY ready)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)
    Q_PROPERTY(AdRequest* adRequest READ adRequest WRITE setAdRequest NOTIFY adRequestChanged)

    Q_OBJECT
public:
    /*
     * Constructor
     */
    explicit AdmMobInterstitial(QObject *parent = nullptr);

    /*
     * Destructor
     */
    ~AdmMobInterstitial();

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

    /*
     * Set ad request
     */
    void setAdRequest(AdRequest* request);

    /*
     * Get ad request
     */
    AdRequest* adRequest();

signals:
    void unitIdChanged();
    void adRequestChanged();
    void ready();
    void loaded();
    void loading();
    
private slots:
    void onAdRequestChanged();

private:
    void initialize(char* unitId);
    void cleanup();
    static void onInitCompletionCallback(const firebase::Future<void>& future, void* userData);
    static void onLoadCompletionCallback(const firebase::Future<void>& future, void* userData);

private:
    firebase::admob::InterstitialAd* m_Interstitial;
    char* m_UnitId;
    bool m_IsVisible;
    AdRequest* m_AdRequest;
};

} // namespace qfb

#endif // QFBADMMOBINTERSTITIAL_H

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
