//
//  database.cpp
//  QtFirebase
//
//  Created by Yevgeniy Logachev on 6/6/19.
//

#include "database.h"
#include "firebase.h"
#include "firebase/database.h"
#include <QDebug>

using namespace qfb;

Database::Database(QObject *parent) : QObject(parent)
{
    auto app = Firebase::instance()->app();
    m_Database = ::firebase::database::Database::GetInstance(app);
}

Database::~Database()
{
    
}

void Database::GetValue(const QString& path, std::function<void(QVariant)> callback)
{
    auto ref = m_Database->GetReference();
    auto child = ref.Child(path.toUtf8().data());
    
    auto future = child.GetValue();
    future.OnCompletion([callback](const ::firebase::Future<::firebase::database::DataSnapshot>& f) {
        if (f.status() != ::firebase::kFutureStatusComplete) {
            callback(QVariant());
            return;
        }
        
        auto data = f.result();
        if (!data) {
            callback(QVariant());
        }
        
        auto variant = data->value();
        switch (variant.type()) {
            case ::firebase::Variant::kTypeInt64:
                callback(QVariant(static_cast<qlonglong>(variant.int64_value())));
                break;
            
            case ::firebase::Variant::kTypeDouble:
                callback(QVariant(static_cast<double>(variant.double_value())));
                break;
            
            case ::firebase::Variant::kTypeStaticString:
            case ::firebase::Variant::kTypeMutableString:
                callback(QVariant(QString(variant.string_value())));
                break;
                
            default:
                callback(QVariant());
                break;
        }
    });
}

void Database::SetValue(const QString& path, const QVariant& value, std::function<void(bool)> callback)
{
    auto ref = m_Database->GetReference();
    auto child = ref.Child(path.toUtf8().data());
    
    ::firebase::Future<void> future;
    switch (value.type()) {
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
            future = child.SetValue(::firebase::Variant(static_cast<int64_t>(value.toLongLong())));
            break;
        
        case QVariant::Double:
            future = child.SetValue(::firebase::Variant(static_cast<double>(value.toDouble())));
            break;
        
        case QVariant::String:
            future = child.SetValue(::firebase::Variant(static_cast<const char*>(value.toString().toUtf8().data())));
            break;
            
        default:
            // TODO: Handle error
            return;
            break;
    }
    
    if (callback) {
        future.OnCompletion([callback](const ::firebase::Future<void>& f) {
            callback(f.status() == ::firebase::kFutureStatusComplete);
        });
    }
}

void Database::PurgeOutstandingWrites()
{
    m_Database->PurgeOutstandingWrites();
}
