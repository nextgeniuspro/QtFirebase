#include "qtfirebase.h"

#include "firebase/admob.h"
#include "firebase/admob/types.h"
#include "firebase/app.h"
#include "firebase/future.h"
#include "platform.h"

#if defined(__ANDROID__)
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#endif

char* QtFirebase::s_AdmobAppId = 0;
QtFirebase* QtFirebase::s_Instance = 0;

QtFirebase::QtFirebase()
{
    if (!s_Instance) {
#if defined(__ANDROID__)
        Platform::TWindow window = Platform::window();
        QAndroidJniEnvironment env;
        m_App = firebase::App::Create(firebase::AppOptions(), env, window);
#else
        m_App = firebase::App::Create(firebase::AppOptions());
#endif
    }
}

QtFirebase::~QtFirebase()
{
}

void QtFirebase::setAdmobAppId(const QString& appId)
{
    if (s_AdmobAppId) {
        return;
    }
    
    s_AdmobAppId = strdup(appId.toUtf8().data());
    firebase::admob::Initialize(*app(), s_AdmobAppId);
    emit admobAppIdChanged();
}

QString QtFirebase::admobAppId() const
{
    return (s_AdmobAppId ? QString(s_AdmobAppId) : "");
}

QtFirebase* QtFirebase::instance()
{
    if (!s_Instance) {
        s_Instance = new QtFirebase();
    }
    return s_Instance;
}

firebase::App* QtFirebase::app()
{
    return m_App;
}
