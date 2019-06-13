#include "adrequest.h"
#include "firebase/admob/types.h"

using namespace qfb;



AdRequest::AdRequest(QObject *parent) : QObject(parent)
{
    m_AdRequest = new firebase::admob::AdRequest();
    memset(m_AdRequest, 0, sizeof(firebase::admob::AdRequest));
}

AdRequest::~AdRequest()
{
    m_AdRequest->test_device_ids = nullptr;
    m_AdRequest->test_device_id_count = 0;

    m_AdRequest->keywords = nullptr;
    m_AdRequest->keyword_count = 0;

    delete m_AdRequest;
}

void AdRequest::setGender(Gender gender)
{
    m_AdRequest->gender = static_cast<firebase::admob::Gender>(gender);
    emit changed();
}

void AdRequest::setBirthday(int day, int month, int year)
{
    m_AdRequest->birthday_day = day;
    m_AdRequest->birthday_month = month;
    m_AdRequest->birthday_year = year;
    emit changed();
}

void AdRequest::addTestDevice(const QString& deviceID)
{
    m_TestDevices.append(deviceID);
    emit changed();
}

void AdRequest::addKeyword(const QString& keyword)
{
    m_KeyWords.append(keyword);
    emit changed();
}

const firebase::admob::AdRequest& AdRequest::toAdRequest()
{
    m_AdRequest->test_device_ids = m_TestDevices();
    m_AdRequest->test_device_id_count = m_TestDevices.size();

    m_AdRequest->keywords = m_KeyWords();
    m_AdRequest->keyword_count = m_KeyWords.size();

    return *m_AdRequest;
}
