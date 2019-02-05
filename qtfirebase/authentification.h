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
    Q_OBJECT
public:
    explicit Auth(QObject *parent = nullptr);

    /*
     * Sign Up new user
     */
    Q_INVOKABLE void signUp(const QString& email, const QString& password);

    /*
     * Sign Up new user
     */
    Q_INVOKABLE void signIn(const QString& email, const QString& password);
    
    /*
     * Login with Facebook token
     */
    Q_INVOKABLE void signInFacebook(const QString& accessToken);

signals:
    void signInCompleted(qfb::User* user);

public slots:

private:
    firebase::auth::Auth* getAuth();
    static void onSignedIn(const firebase::Future<firebase::auth::User*>& result, void* user_data);

private:
//    firebase::Future<firebase::auth::User*> m_Future;
};

} // namespace qfb

#endif // QFBAUTHENTIFICATION_H

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
