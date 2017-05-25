#if defined(QTFIREBASE_ANALYTICS_ENABLED)

#ifndef QTANALYTICS_H
#define QTANALYTICS_H

#include <QObject>

class QtAnalytics : public QObject
{
    Q_OBJECT
public:
    explicit QtAnalytics(QObject *parent = 0);

    void setUserId(const QString& userId);
    QString userId() const;

public slots:
    void logEvent(const QString& name);
    void logEvent(const QString& name, const QString& parameterName, const QString& parameterValue);
    void logEvent(const QString& name, const QString& parameterName, double parameterValue);
    void logEvent(const QString& name, const QString& parameterName, int parameterValue);
    void logEvent(const QString& name, const QVariantMap& parameters);

private:
    char *m_UserId;
};

#endif // QTANALYTICS_H

#endif // #if defined(QTFIREBASE_ANALYTICS_ENABLED)
