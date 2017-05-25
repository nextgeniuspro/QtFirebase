#if defined(QTFIREBASE_ANALYTICS_ENABLED)

#include "qtanalytics.h"
#include "firebase/analytics.h"
#include <QMapIterator>
#include <QVariant>
#include <QVector>

QtAnalytics::QtAnalytics(QObject *parent) : QObject(parent)
{

}

void QtAnalytics::logEvent(const QString& name)
{
    ::firebase::analytics::LogEvent(name.toUtf8().constData());
}

void QtAnalytics::logEvent(const QString& name, const QString& parameterName, const QString& parameterValue)
{
    ::firebase::analytics::LogEvent(name.toUtf8().constData(), parameterName.toUtf8().constData(), parameterValue.toUtf8().constData());
}

void QtAnalytics::logEvent(const QString& name, const QString& parameterName, double parameterValue)
{
    ::firebase::analytics::LogEvent(name.toUtf8().constData(), parameterName.toUtf8().constData(), parameterValue);
}

void QtAnalytics::logEvent(const QString& name, const QString& parameterName, int parameterValue)
{
    ::firebase::analytics::LogEvent(name.toUtf8().constData(), parameterName.toUtf8().constData(), parameterValue);
}

void QtAnalytics::logEvent(const QString& name, const QVariantMap& parameters)
{
    QVector<::firebase::analytics::Parameter> data;

    QMapIterator<QString, QVariant> it(parameters);
    for (const QString& key : parameters.keys()) {
        const QVariant& value = parameters[key];

        if (value.type() == QVariant::Int) {
            ::firebase::analytics::Parameter param(key.toUtf8().constData(), value.toInt());
            data.push_back(param);
        }
        else if (value.type() == QVariant::Double) {
            ::firebase::analytics::Parameter param(key.toUtf8().constData(), value.toDouble());
            data.push_back(param);
        }
        else if (value.type() == QVariant::String) {
            ::firebase::analytics::Parameter param(key.toUtf8().constData(), value.toString().toUtf8().constData());
            data.push_back(param);
        }
    }

    ::firebase::analytics::LogEvent(name.toUtf8().constData(), data.data(), data.size());
}

#endif // #if defined(QTFIREBASE_ANALYTICS_ENABLED)
