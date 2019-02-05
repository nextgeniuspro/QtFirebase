#if defined(QTFIREBASE_AUTHENTIFICATION_ENABLED)

#include "authentification.h"
#include "firebase.h"
#include "user.h"
#include "firebase/auth/user.h"
#include "firebase/auth.h"

using namespace qfb;

class AuthStateListener : public firebase::auth::AuthStateListener {
public:
    typedef std::function<void(firebase::auth::Auth* auth)> AuthChanged_t;
    
    AuthStateListener(AuthChanged_t callback)
    : m_Callback(callback)
    {
        
    };
    
    void OnAuthStateChanged(firebase::auth::Auth* auth) override
    {
        m_Callback(auth);
    }
    
private:
     AuthChanged_t m_Callback;
};


Auth::Auth(QObject *parent)
    : QObject(parent)
    , m_CurrentUser(nullptr)
{
    m_Listener = new AuthStateListener([&](firebase::auth::Auth* auth){
        firebase::auth::User* user = auth->current_user();
        userChanged(user);
        
        if (user != nullptr) {
            emit sinedIn(m_CurrentUser);
        } else {
            emit signedOut();
        }
    });
    getAuth()->AddAuthStateListener(static_cast<AuthStateListener*>(m_Listener));
}

Auth::~Auth()
{
    delete static_cast<AuthStateListener*>(m_Listener);
    delete m_CurrentUser;
}

void Auth::signUp(const QString& email, const QString& password)
{
    auto future = getAuth()->CreateUserWithEmailAndPassword(email.toUtf8().data(), password.toUtf8().data());
    future.OnCompletion(std::bind(&Auth::onSignedIn, this, std::placeholders::_1));
}

void Auth::signIn(const QString& email, const QString& password)
{
    auto future = getAuth()->SignInWithEmailAndPassword(email.toUtf8().data(), password.toUtf8().data());
    future.OnCompletion(std::bind(&Auth::onSignedIn, this, std::placeholders::_1));
}

void Auth::signInWithToken(const QString& token)
{
    static char* ss;
    ss = strdup(token.toUtf8().data());
    
    auto future = getAuth()->SignInWithCustomToken(ss);
    future.OnCompletion(std::bind(&Auth::onSignedIn, this, std::placeholders::_1));
}

void Auth::signInFacebook(const QString& accessToken)
{
    auto credentials = firebase::auth::FacebookAuthProvider::GetCredential(accessToken.toUtf8().data());

    auto future = getAuth()->SignInWithCredential(credentials);
    future.OnCompletion(std::bind(&Auth::onSignedIn, this, std::placeholders::_1));
}

void Auth::signInAnonymous()
{
    auto future = getAuth()->SignInAnonymously();
    future.OnCompletion(std::bind(&Auth::onSignedIn, this, std::placeholders::_1));
}

void Auth::signOut()
{
    getAuth()->SignOut();
}

qfb::User* Auth::user() const
{
    return m_CurrentUser;
}

firebase::auth::Auth* Auth::getAuth()
{
    auto app = Firebase::instance()->app();
    return firebase::auth::Auth::GetAuth(app, nullptr);
}

void Auth::onSignedIn(const firebase::Future<firebase::auth::User*>& result)
{
    bool ok = (result.status() == firebase::kFutureStatusComplete &&
               result.error() == firebase::auth::kAuthErrorNone);
    
    userChanged(ok ? *result.result() : nullptr);
    
    emit sinedIn(m_CurrentUser);
}

void Auth::userChanged(firebase::auth::User* user)
{
    if (m_CurrentUser && user != m_CurrentUser->firebaseUser()) {
        delete m_CurrentUser;
        m_CurrentUser = nullptr;
    }
    
    if (user) {
        m_CurrentUser = new User(user);
    }
}

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
