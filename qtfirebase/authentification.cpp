#if defined(QTFIREBASE_AUTHENTIFICATION_ENABLED)

#include "authentification.h"
#include "firebase.h"
#include "user.h"
#include "firebase/auth/user.h"
#include "firebase/auth.h"

using namespace qfb;

Auth::Auth(QObject *parent) : QObject(parent)
{

}

void Auth::signUp(const QString& email, const QString& password)
{
    auto future = getAuth()->CreateUserWithEmailAndPassword(email.toUtf8().data(), password.toUtf8().data());
    future.OnCompletion(&Auth::onSignedIn, this);
}

void Auth::signIn(const QString& email, const QString& password)
{
    auto future = getAuth()->SignInWithEmailAndPassword(email.toUtf8().data(), password.toUtf8().data());
    future.OnCompletion(&Auth::onSignedIn, this);
}

void Auth::signInFacebook(const QString& accessToken)
{
    auto credentials = firebase::auth::FacebookAuthProvider::GetCredential(accessToken.toUtf8().data());

    auto future = getAuth()->SignInWithCredential(credentials);
    future.OnCompletion(&Auth::onSignedIn, this);
}

firebase::auth::Auth* Auth::getAuth()
{
    auto app = Firebase::instance()->app();
    return firebase::auth::Auth::GetAuth(app, nullptr);
}

void Auth::onSignedIn(const firebase::Future<firebase::auth::User*>& result, void* user_data)
{
    Auth* self = static_cast<Auth *>(user_data);
    
    bool ok = (result.status() == firebase::kFutureStatusComplete &&
               result.error() == firebase::auth::kAuthErrorNone);
    
    User* user = nullptr;
    if (ok) {
        user = new User(*result.result());
    }
    
    emit self->signInCompleted(user);
}

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
