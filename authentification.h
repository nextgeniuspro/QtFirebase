#if defined(QTFIREBASE_AUTHENTIFICATION_ENABLED)

#ifndef QFBAUTHENTIFICATION_H
#define QFBAUTHENTIFICATION_H

#include <QObject>


namespace firebase {
    namespace auth {
        class User;
        class Auth;
    }
    template <typename ResultType> class Future;
}

namespace qfb {
    
class User;

class Auth : public QObject
{
    Q_PROPERTY(qfb::User* user READ user)
    
    Q_OBJECT
public:
    explicit Auth(QObject *parent = nullptr);
    virtual ~Auth();

    /*
     * Sign up new user
     */
    Q_INVOKABLE void signUp(const QString& email, const QString& password);

    /*
     * Sign in current account
     */
    Q_INVOKABLE void signIn(const QString& email, const QString& password);
    
    /*
     * Sign in with Firebase token
     */
    Q_INVOKABLE void signInWithToken(const QString& token);
    
    /*
     * Sign in with Facebook token
     */
    Q_INVOKABLE void signInFacebook(const QString& accessToken);
    
    /*
     * Sign in anonymously
     */
    Q_INVOKABLE void signInAnonymous();
    
    /*
     * Log out
     */
    Q_INVOKABLE void signOut();
    
    /*
     * Get current user
     */
    qfb::User* user() const;
    

signals:
    void sinedIn(qfb::User* user);
    void signedOut();

public slots:

private:
    firebase::auth::Auth* getAuth();
    void onSignedIn(const firebase::Future<firebase::auth::User*>& result);
    void userChanged(firebase::auth::User* user);

private:
    void* m_Listener;
    qfb::User* m_CurrentUser;
};

} // namespace qfb

#endif // QFBAUTHENTIFICATION_H

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
