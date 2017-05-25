#ifndef QTFIREBASE_H
#define QTFIREBASE_H

#include <QObject>

namespace firebase {
    class App;
}

class QtFirebase : public QObject
{
    Q_PROPERTY(QString admobAppId READ admobAppId WRITE setAdmobAppId NOTIFY admobAppIdChanged)
    
    Q_OBJECT
public:
    QtFirebase();
    ~QtFirebase();

    void setAdmobAppId(const QString& appId);
    QString admobAppId() const;
    
    static QtFirebase* instance();
    firebase::App* app();
    
signals:
    void admobAppIdChanged();

private:
    firebase::App* m_App;
    static char *s_AdmobAppId;
    bool m_IsAdmobInitialized;

    static QtFirebase* s_Instance;
};

#endif // QTFIREBASE_H
