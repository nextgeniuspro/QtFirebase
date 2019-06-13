#if defined(QTFIREBASE_ADMOB_ENABLED)

#include "admobbanner.h"
#include "platform.h"
#include "adrequest.h"
#include "firebase/admob/banner_view.h"
#include "firebase/future.h"

using namespace qfb;



AdMobBanner::AdMobBanner(QObject *parent)
    : QObject(parent)
    , m_BannerView(nullptr)
    , m_UnitId(nullptr)
    , m_Size(QSize(0, 0))
    , m_InitState(0)
    , m_Position(QPoint(0, 0))
    , m_IsVisible(false)
    , m_AdRequest(nullptr)
{
    setAdRequest(new AdRequest(parent));
    connect(this, SIGNAL(adRequestChanged()), this, SLOT(onAdRequestChanged()));
}

AdMobBanner::~AdMobBanner()
{
    delete m_AdRequest;
    free(m_UnitId);
    cleanup();
}

void AdMobBanner::setUnitId(const QString& unitId)
{
    if (this->unitId() == unitId) {
        return;
    }

    free(m_UnitId);
    m_UnitId = strdup(unitId.toUtf8().data());
    emit unitIdChanged();

    m_InitState |= UnitIdReady;
    tryInitialze();
}

QString AdMobBanner::unitId() const
{
    return (m_UnitId ? QString(m_UnitId) : "");
}

void AdMobBanner::setSize(const QSize& size)
{
    if (m_Size == size) {
        return;
    }

    m_Size = size;
    emit sizeChanged();

    m_InitState |= SizeReady;
    tryInitialze();
}

QSize AdMobBanner::size()
{
    return m_Size;
}

void AdMobBanner::setPosition(const QPoint& position)
{
    m_Position = position;
    emit positionChanged();

    if (!isReady()) {
        return;
    }

    if (!isLoaded()) {
        return;
    }

    m_BannerView->MoveTo(position.x() * Platform::scaleFactor(),
                         (position.y() + Platform::bannerStatusBarYOffset()) * Platform::scaleFactor());
}

const QPoint& AdMobBanner::position() const
{
    return m_Position;
}

void AdMobBanner::setVisible(bool isVisible)
{
    m_IsVisible = isVisible;
    emit visibleChanged();

    if (!isReady()) {
        return;
    }

    if (!isLoaded()) {
        return;
    }

    if (isVisible) {
        m_BannerView->Show();
    } else {
        m_BannerView->Hide();
    }
}

bool AdMobBanner::visible()
{
    return m_IsVisible;
}

bool AdMobBanner::isReady()
{
    return (m_BannerView &&
            m_BannerView->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_BannerView->InitializeLastResult().error() == firebase::admob::kAdMobErrorNone);
}

bool AdMobBanner::isLoaded()
{
    return (m_BannerView &&
            m_BannerView->InitializeLastResult().status() == firebase::kFutureStatusComplete &&
            m_BannerView->LoadAdLastResult().error() == firebase::admob::kAdMobErrorNone);
}

void AdMobBanner::setAdRequest(AdRequest* request)
{
    if (request == nullptr) {
        return;
    }
    if (m_AdRequest) {
        disconnect(m_AdRequest, SIGNAL(changed()), this, SIGNAL(adRequestChanged()));
    }
    m_AdRequest = request;
    connect(m_AdRequest, SIGNAL(changed()), this, SIGNAL(adRequestChanged()));

    emit adRequestChanged();
}

AdRequest* AdMobBanner::adRequest()
{
    return m_AdRequest;
}

void AdMobBanner::initialize(char* unitId, const QSize& size)
{
    emit loading();

    m_BannerView = new firebase::admob::BannerView();

    firebase::admob::AdSize adSize;
    adSize.ad_size_type = firebase::admob::kAdSizeStandard;
    adSize.width = size.width();
    adSize.height = size.height();

    m_BannerView->Initialize(static_cast<firebase::admob::AdParent>(Platform::window()), unitId, adSize);
    m_BannerView->InitializeLastResult().OnCompletion(AdMobBanner::onInitCompletionCallback, this);
}

void AdMobBanner::tryInitialze()
{
    if (m_InitState == InitializationReady) {
        cleanup();
        initialize(m_UnitId, m_Size);
    }
}

void AdMobBanner::cleanup()
{
    if (m_BannerView) {
        m_BannerView->InitializeLastResult().OnCompletion(nullptr, nullptr);
        m_BannerView->LoadAdLastResult().OnCompletion(nullptr, nullptr);
        delete m_BannerView;
        m_BannerView = nullptr;
    }
}

void AdMobBanner::onInitCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);


    AdMobBanner *self = static_cast<AdMobBanner *>(userData);
    self->m_BannerView->LoadAd(self->adRequest()->toAdRequest());
    self->m_BannerView->LoadAdLastResult().OnCompletion(AdMobBanner::onLoadCompletionCallback, self);
    emit self->ready();
}

void AdMobBanner::onLoadCompletionCallback(const firebase::Future<void>& future, void* userData) {

    Q_UNUSED(future);

    AdMobBanner *self = static_cast<AdMobBanner *>(userData);
    // Check loading status
    if (!self->isLoaded()) {
        return;
    }
    // If during loading banner was marked as visible - show it
    if (self->visible()) {
        self->m_BannerView->Show();
    }
    self->setPosition(self->position());
    self->loaded();
}

void AdMobBanner::onAdRequestChanged()
{
    if (isReady()) {
        tryInitialze();
    }
}

#endif // #if defined(QTFIREBASE_ADMOB_ENABLED)
