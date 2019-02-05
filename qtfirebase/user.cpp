#if defined(QTFIREBASE_AUTHENTIFICATION_ENABLED)

#include "user.h"
#include <QString>
#include "firebase/auth/user.h"

using namespace qfb;


User::User(firebase::auth::User* user, QObject* parent)
    : QObject(parent)
    , m_User(user)
{
    if (user) {
        m_FullName = QString::fromUtf8(user->display_name().c_str());
        m_PhotoURL = QString::fromUtf8(user->photo_url().c_str());
        m_Email = QString::fromUtf8(user->email().c_str());
        m_ProviderName = QString::fromUtf8(user->provider_id().c_str());
        m_PhoneNumber = QString::fromUtf8(user->phone_number().c_str());
    }
}

QString User::fullName() const
{
    return m_FullName;
}

void User::setFullName(const QString& value)
{
    m_FullName = value;
    emit fullNameChanged();
}

QString User::photoURL() const
{
    return m_PhotoURL;
}

void User::setPhotoURL(const QString& value)
{
    m_PhotoURL = value;
    emit photoURLChanged();
}

QString User::email() const
{
    return m_Email;
}

QString User::providerName() const
{
    return m_ProviderName;
}

QString User::phoneNumber() const
{
    return m_PhoneNumber;
}

#endif // QTFIREBASE_AUTHENTIFICATION_ENABLED
