#if defined(QTFIREBASE_ADMOB_ENABLED)

#include "admmobinterstitial.h"
#include "platform.h"
#include "adrequest.h"
#include "firebase/admob/interstitial_ad.h"
#include "firebase/future.h"

using namespace qfb;



AdmMobInterstitial::AdmMobInterstitial(QObject *parent)
    : QObject(parent)
    , m_Interstitial(nullptr)
    , m_UnitId(nullptr)
    , m_IsVisible(false)
    , m_AdRequest(nullptr)
{
    setAdRequest(new AdRequest(this));
    connect(this, SIGNAL(adRequestChanged()), this, SLOT(onAdRequestChanged()));
}

AdmMobInterstitial::~AdmMobInterstitial()
{
    delete m_AdRequest;
    free(m_UnitId);
    cleanup();
}

void AdmMobInterstitial::setUnitId(const QString& unitId)
{
    free(m_UnitId);
    m_UnitId = strdup(unitId.toUtf8().data());
    emit unitIdChanged();
    
    cleanup();
    initialize(m_UnitId);
}

QString AdmMobInterstitial::unitId() const
{
    return (m_UnitId ? QString(m_UnitId) : "");
}

void AdmMobInterstitial::show()
{
    m_IsVisible = true;

    if (!isReady()) {
        return;
    }

    if (!isLoaded()) {
        return;
    }

    m_Interstitial->Show();
}

bool AdmMobInterstitial::isReady()
{
    return (m_Interstitial &&
            m_Interstitial->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_Interstitial->InitializeLastResult().error() == firebase::admob::kAdMobErrorNone);
}

bool AdmMobInterstitial::isLoaded()
{
    return (m_Interstitial &&
            m_Interstitial->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_Interstitial->LoadAdLastResult().error() == firebase::admob::kAdMobErrorNone);
}

void AdmMobInterstitial::setAdRequest(AdRequest* request)
{
    if (request == nullptr) {
        return;
    }
    m_AdRequest = request;
    emit adRequestChanged();
}

AdRequest* AdmMobInterstitial::adRequest()
{
    return m_AdRequest;
}

void AdmMobInterstitial::initialize(char* unitId)
{
    emit loading();

    m_Interstitial = new firebase::admob::InterstitialAd();
    m_Interstitial->Initialize(static_cast<firebase::admob::AdParent>(Platform::window()), unitId);
    m_Interstitial->InitializeLastResult().OnCompletion(AdmMobInterstitial::onInitCompletionCallback, this);
}

void AdmMobInterstitial::cleanup()
{
    if (m_Interstitial) {
        m_Interstitial->InitializeLastResult().OnCompletion(nullptr, nullptr);
        m_Interstitial->LoadAdLastResult().OnCompletion(nullptr, nullptr);
        delete m_Interstitial;
        m_Interstitial = nullptr;
    }
}

void AdmMobInterstitial::onInitCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    AdmMobInterstitial *self = static_cast<AdmMobInterstitial *>(userData);
    self->m_Interstitial->LoadAd(self->adRequest()->toAdRequest());
    self->m_Interstitial->LoadAdLastResult().OnCompletion(AdmMobInterstitial::onLoadCompletionCallback, self);
    emit self->ready();
}

void AdmMobInterstitial::onLoadCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    AdmMobInterstitial *self = static_cast<AdmMobInterstitial *>(userData);
    // Check loading status
    if (!self->isLoaded()) {
        return;
    }
    // If during loading interstitial was marked as visible - show it
    if (self->m_IsVisible) {
        self->m_Interstitial->Show();
    }
    self->loaded();
}

void AdmMobInterstitial::onAdRequestChanged()
{
    if (isReady() && m_UnitId) {
        initialize(m_UnitId);
    }
}

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
