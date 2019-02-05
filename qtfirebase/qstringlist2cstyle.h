#ifndef QFBQSTRINGLIST2CSTYLE_H
#define QFBQSTRINGLIST2CSTYLE_H

#include <QStringList>
#include <QVector>

namespace qfb {

class QStringList2CStyle : public QStringList
{
public:
    QStringList2CStyle();
    virtual ~QStringList2CStyle();
    
    /*
     * Convert to C-styled array of strings
     */
    const char** operator() ();

private:
    void cleanup();
    QVector<const char *> m_CStrings;
};
    
} // namespace qfb

#endif // QFBQSTRINGLIST2CSTYLE_H
