#if defined(QTFIREBASE_ANALYTICS_ENABLED)

#ifndef QFBANALYTICS_H
#define QFBANALYTICS_H

#include <QObject>

namespace qfb {

class Analytics : public QObject
{
    Q_OBJECT
public:
    /*
     * Constructor
     */
    explicit Analytics(QObject *parent = nullptr);

    /*
     * Set user ID
     */
    void setUserId(const QString& userId);

    /*
     * Get user ID
     */
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

} // namespace qfb

#endif // QFBANALYTICS_H

#endif // #if defined(QTFIREBASE_ANALYTICS_ENABLED)
