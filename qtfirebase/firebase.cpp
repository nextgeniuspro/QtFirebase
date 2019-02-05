#include "firebase.h"

#include "platform.h"
#include "firebase/admob.h"
#include "firebase/admob/types.h"
#include "firebase/app.h"
#include "firebase/future.h"

#if defined(__ANDROID__)
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#endif

using namespace qfb;



char* Firebase::s_AdmobAppId = nullptr;
Firebase* Firebase::s_Instance = nullptr;

Firebase::Firebase()
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

Firebase::~Firebase()
{
}

void Firebase::setAdmobAppId(const QString& appId)
{
    if (s_AdmobAppId) {
        return;
    }
    
    s_AdmobAppId = strdup(appId.toUtf8().data());
    firebase::admob::Initialize(*app(), s_AdmobAppId);
    emit admobAppIdChanged();
}

QString Firebase::admobAppId() const
{
    return (s_AdmobAppId ? QString(s_AdmobAppId) : "");
}

Firebase* Firebase::instance()
{
    if (!s_Instance) {
        s_Instance = new Firebase();
    }
    return s_Instance;
}

firebase::App* Firebase::app()
{
    return m_App;
}
