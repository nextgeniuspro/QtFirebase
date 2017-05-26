#if defined(QTFIREBASE_ADMOB_ENABLED)

#include "qtadmobbanner.h"
#include "firebase/admob/banner_view.h"
#include "platform.h"


QtAdMobBanner::QtAdMobBanner(QObject *parent)
    : QObject(parent)
    , m_BannerView(0)
    , m_UnitId(0)
    , m_Size(QSize(0, 0))
    , m_Position(QPoint(0, 0))
    , m_IsVisible(false)
{
}

QtAdMobBanner::~QtAdMobBanner()
{
    free(m_UnitId);
    cleanup();
}

void QtAdMobBanner::setUnitId(const QString& unitId)
{
    if (this->unitId() == unitId) {
        return;
    }
    
    m_UnitId = strdup(unitId.toUtf8().data());
    emit unitIdChanged();
    
    m_InitState |= UnitIdReady;
    tryInitialze();
}

QString QtAdMobBanner::unitId() const
{
    return (m_UnitId ? QString(m_UnitId) : "");
}

void QtAdMobBanner::setSize(const QSize& size)
{
    if (m_Size == size) {
        return;
    }
    
    m_Size = size;
    emit sizeChanged();
    
    m_InitState |= SizeReady;
    tryInitialze();
}

QSize QtAdMobBanner::size()
{
    return m_Size;
}

void QtAdMobBanner::setPosition(const QPoint& position)
{
    m_Position = position;
    emit positionChanged();

    if (!isReady()) {
        return;
    }

    if (!isLoaded()) {
        return;
    }

    int x = position.x() * Platform::scaleFactor();
    int y = (position.y() + Platform::statusBarSize().height()) * Platform::scaleFactor();
    m_BannerView->MoveTo(x, y);
}

const QPoint& QtAdMobBanner::position() const
{
    return m_Position;
}

void QtAdMobBanner::setVisible(bool isVisible)
{
    m_IsVisible = isVisible;
    emit visibleChanged();

    if (!isReady()) {
        return;
    }

    if (!isLoaded()) {
        return;
    }

    setPosition(position());
    if (isVisible) {
        m_BannerView->Show();
    } else {
        m_BannerView->Hide();
    }
}

bool QtAdMobBanner::visible()
{
    return m_IsVisible;
}

bool QtAdMobBanner::isReady()
{
    return (m_BannerView &&
            m_BannerView->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_BannerView->InitializeLastResult().error() == firebase::admob::kAdMobErrorNone);
}

bool QtAdMobBanner::isLoaded()
{
    return (m_BannerView &&
            m_BannerView->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_BannerView->LoadAdLastResult().error() == firebase::admob::kAdMobErrorNone);
}

void QtAdMobBanner::initialize(char* unitId, const QSize& size)
{
    emit loading();
    
    m_BannerView = new firebase::admob::BannerView();
    
    firebase::admob::AdSize adSize;
    adSize.ad_size_type = firebase::admob::kAdSizeStandard;
    adSize.width = size.width();
    adSize.height = size.height();
    
    m_BannerView->Initialize(static_cast<firebase::admob::AdParent>(Platform::window()), unitId, adSize);
    m_BannerView->InitializeLastResult().OnCompletion(QtAdMobBanner::onInitCompletionCallback, this);
}

void QtAdMobBanner::tryInitialze()
{
    if (m_InitState == InitializationReady) {
        cleanup();
        initialize(m_UnitId, m_Size);
    }
}

void QtAdMobBanner::cleanup()
{
    if (m_BannerView) {
        m_BannerView->InitializeLastResult().OnCompletion(0, 0);
        m_BannerView->LoadAdLastResult().OnCompletion(0, 0);
        delete m_BannerView;
    }
}

void QtAdMobBanner::onInitCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    QtAdMobBanner *self = static_cast<QtAdMobBanner *>(userData);
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
    static const char* kTestDeviceIDs[] = {"ba7c0f6367a9caf3a1f045e0539fe987"};
    adRequest.test_device_id_count = sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
    adRequest.test_device_ids = kTestDeviceIDs;

    
    
    self->m_BannerView->LoadAd(adRequest);
    self->m_BannerView->LoadAdLastResult().OnCompletion(QtAdMobBanner::onLoadCompletionCallback, self);
    emit self->ready();
}

void QtAdMobBanner::onLoadCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    QtAdMobBanner *self = static_cast<QtAdMobBanner *>(userData);
    // Check loading status
    if (!self->isLoaded()) {
        return;
    }
    // If during loading banner was marked as visible - show it
    if (self->visible()) {
        self->m_BannerView->Show();
        self->setPosition(self->position());
    }
    self->m_BannerView->MoveTo(self->position().x(), self->position().y());
    self->loaded();
}

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
