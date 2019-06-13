#include "qstringlist2cstyle.h"

using namespace qfb;



QStringList2CStyle::QStringList2CStyle()
{

}

QStringList2CStyle::~QStringList2CStyle()
{
    cleanup();
}

const char** QStringList2CStyle::operator() ()
{
    cleanup();
    m_CStrings.resize(this->size());
    for (int i = 0; i < this->size(); ++i) {
        m_CStrings[i] = strdup(this->at(i).toUtf8().constData());
    }
    return m_CStrings.data();
}

void QStringList2CStyle::cleanup()
{
    for (int i = 0; i < m_CStrings.size(); ++i) {
        free(static_cast<void*>(const_cast<char*>(m_CStrings[i])));
    }
}
