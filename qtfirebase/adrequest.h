#ifndef QFBADREQUEST_H
#define QFBADREQUEST_H

#include <QObject>
#include "types.h"
#include "qstringlist2cstyle.h"

namespace firebase {
    namespace admob {
        struct AdRequest;
    }
}

namespace qfb {

class AdRequest : public QObject
{
    Q_OBJECT
public:
    explicit AdRequest(QObject *parent = nullptr);
    virtual ~AdRequest();

    /*
     * Convert to firebase::admob::AdRequest
     */
    const firebase::admob::AdRequest& toAdRequest();

signals:
    void changed();

public slots:
    /*
     * Set gender
     */
    Q_INVOKABLE void setGender(Gender gender);

    /*
     * Set birthday
     */
    Q_INVOKABLE void setBirthday(int day, int month, int year);

    /*
     * Add test device ID
     */
    Q_INVOKABLE void addTestDevice(const QString& deviceID);

    /*
     * Add keyword
     */
    Q_INVOKABLE void addKeyword(const QString& keyword);

private:
    void cleanup();

    firebase::admob::AdRequest* m_AdRequest;

    QStringList2CStyle m_TestDevices;
    QStringList2CStyle m_KeyWords;
};

} // namespace qfb

#endif // QFBADREQUEST_H
