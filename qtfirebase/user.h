#if defined(QTFIREBASE_AUTHENTIFICATION_ENABLED)

#ifndef AUTHUSER_H
#define AUTHUSER_H

#include <QObject>

namespace firebase {
    namespace auth {
       class User;
    }
}

namespace qfb {

class User : public QObject
{
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString photoURL READ photoURL WRITE setPhotoURL NOTIFY photoURLChanged)
    Q_PROPERTY(QString email READ email)
    Q_PROPERTY(QString providerName READ providerName)
    Q_PROPERTY(QString phoneNumber READ phoneNumber)

    Q_OBJECT
public:
    explicit User(firebase::auth::User* user = nullptr, QObject* parent = nullptr);

    /*
     * Get full name
     */
    QString fullName() const;

    /*
     * Set full name
     */
    void setFullName(const QString& fullName);

    /*
     * Get photo URL
     */
    QString photoURL() const;

    /*
     * Set photo URL
     */
    void setPhotoURL(const QString& photoURL);

    /*
     * Get email
     */
    QString email() const;

    /*
     * Get provider name
     */
    QString providerName() const;

    /*
     * Get phone number
     */
    QString phoneNumber() const;
    
    /*
     * Get auth token
     */
    Q_INVOKABLE void requestToken(bool refresh, std::function<void(QString token)> callback);
    
    /*
     * Internal
     */
    firebase::auth::User* firebaseUser() const;

signals:
    void fullNameChanged();
    void photoURLChanged();

public slots:

private:
    QString m_Email;
    QString m_FullName;
    QString m_PhotoURL;
    QString m_ProviderName;
    QString m_PhoneNumber;

    firebase::auth::User* m_User;
};

} // namespace qfb

#endif // AUTHUSER_H

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
