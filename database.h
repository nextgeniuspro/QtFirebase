//
//  database.h
//  QtFirebase
//
//  Created by Yevgeniy Logachev on 6/6/19.
//

#ifndef QFBDATABASE_H
#define QFBDATABASE_H

#include <QObject>
#include <QVariant>

namespace firebase {
    namespace database {
        class Database;
        class DatabaseReference;
    }
}

namespace qfb {

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    virtual ~Database();
    
    /*
     * Get value from DB
     */
    Q_INVOKABLE void GetValue(const QString& path, std::function<void(QVariant)> callback);
    
    /*
     * Set value to DB
     */
    Q_INVOKABLE void SetValue(const QString& path, const QVariant& value, std::function<void(bool)> callback);
    
    /*
     * Purge all pending writes to the Firebase Realtime Database server.
     */
    Q_INVOKABLE void PurgeOutstandingWrites();
    
signals:
    
public slots:
    
private:
    firebase::database::Database* getDatabase();
};
    
} // namespace qfb

#endif /* QFBDATABASE_H */
