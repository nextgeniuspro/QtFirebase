#if defined(QTFIREBASE_ADMOB_ENABLED)

#include "qtadmmobinterstitial.h"
#include "firebase/admob/interstitial_ad.h"
#include "platform.h"


QtAdmMobInterstitial::QtAdmMobInterstitial(QObject *parent)
    : QObject(parent)
    , m_Interstitial(0)
    , m_UnitId(0)
    , m_IsVisible(false)
{
    
}

QtAdmMobInterstitial::~QtAdmMobInterstitial()
{
    free(m_UnitId);
    cleanup();
}

void QtAdmMobInterstitial::setUnitId(const QString& unitId)
{
    if (this->unitId() == unitId) {
        return;
    }
    
    m_UnitId = strdup(unitId.toUtf8().data());
    emit unitIdChanged();
    
    cleanup();
    initialize(m_UnitId);
}

QString QtAdmMobInterstitial::unitId() const
{
    return (m_UnitId ? QString(m_UnitId) : "");
}

void QtAdmMobInterstitial::show()
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

bool QtAdmMobInterstitial::isReady()
{
    return (m_Interstitial &&
            m_Interstitial->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_Interstitial->InitializeLastResult().error() == firebase::admob::kAdMobErrorNone);
}

bool QtAdmMobInterstitial::isLoaded()
{
    return (m_Interstitial &&
            m_Interstitial->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_Interstitial->LoadAdLastResult().error() == firebase::admob::kAdMobErrorNone);
}

void QtAdmMobInterstitial::initialize(char* unitId)
{
    emit loading();

    m_Interstitial = new firebase::admob::InterstitialAd();
    m_Interstitial->Initialize(static_cast<firebase::admob::AdParent>(Platform::window()), unitId);
    m_Interstitial->InitializeLastResult().OnCompletion(QtAdmMobInterstitial::onInitCompletionCallback, this);
    m_Interstitial->SetListener(this);
}

void QtAdmMobInterstitial::cleanup()
{
    if (m_Interstitial) {
        m_Interstitial->InitializeLastResult().OnCompletion(0, 0);
        m_Interstitial->LoadAdLastResult().OnCompletion(0, 0);
        m_Interstitial->SetListener(0);
        delete m_Interstitial;
    }
}

void QtAdmMobInterstitial::load()
{
    firebase::admob::AdRequest adRequest = {};
    
    adRequest.gender = firebase::admob::kGenderUnknown;
    
    // The user's birthday, if known. Note that months are indexed from one.
    adRequest.birthday_day = 10;
    adRequest.birthday_month = 11;
    adRequest.birthday_year = 1976;
    
    // Additional keywords to be used in targeting.
    static const char* kKeywords[] = {"AdMob", "C++", "Fun"};
    adRequest.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
    adRequest.keywords = kKeywords;
    
    // "Extra" key value pairs can be added to the request as well.
    static const firebase::admob::KeyValuePair kRequestExtras[] = {{"the_name_of_an_extra", "the_value_for_that_extra"}};
    adRequest.extras_count = sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
    adRequest.extras = kRequestExtras;
    
    // Register the device IDs associated with any devices that will be used to
    // test your app. Below are sample test device IDs used for making the ad request.
    static const char* kTestDeviceIDs[] = {"09c57fb538d2911f489c6b2c55dbf495"};
    adRequest.test_device_id_count = sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
    adRequest.test_device_ids = kTestDeviceIDs;
    
    m_Interstitial->LoadAd(adRequest);
    m_Interstitial->LoadAdLastResult().OnCompletion(QtAdmMobInterstitial::onLoadCompletionCallback, this);
}

void QtAdmMobInterstitial::onInitCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    QtAdmMobInterstitial *self = static_cast<QtAdmMobInterstitial *>(userData);
    self->load();
    emit self->ready();
}

void QtAdmMobInterstitial::onLoadCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    QtAdmMobInterstitial *self = static_cast<QtAdmMobInterstitial *>(userData);
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

void QtAdmMobInterstitial::OnPresentationStateChanged(firebase::admob::InterstitialAd* /*interstitial_ad*/,
                                                      firebase::admob::InterstitialAd::PresentationState state)
{
    if (state == firebase::admob::InterstitialAd::kPresentationStateHidden) {
        m_IsVisible = false;
        emit closed();
        initialize(m_UnitId);
    }
}

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
