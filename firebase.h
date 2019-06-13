#ifndef QFBFIREBASE_H
#define QFBFIREBASE_H

#include <QObject>

namespace firebase {
    class App;
}

namespace qfb {

class Firebase : public QObject
{
    Q_PROPERTY(QString admobAppId READ admobAppId WRITE setAdmobAppId NOTIFY admobAppIdChanged)
    
    Q_OBJECT
public:
    /*
     * Constructor
     */
    Firebase();

    /*
     * Destructor
     */
    ~Firebase();

    /*
     * Set Admob app ID
     */
    void setAdmobAppId(const QString& appId);

    /*
     * Get Admob app ID
     */
    QString admobAppId() const;
    
    /*
     * Instance
     */
    static Firebase* instance();

    /*
     * Get firebase app object
     */
    firebase::App* app();
    
signals:
    void admobAppIdChanged();

private:
    firebase::App* m_App;
    static char *s_AdmobAppId;
    bool m_IsAdmobInitialized;

    static Firebase* s_Instance;
};
    
} // namespace qfb

#endif // QFBFIREBASE_H
