#ifndef ADVERT_H
#define ADVERT_H
#include <QString>

class Advert
{
    friend class Client;
public:
    Advert();
private:
    QString m_name;
    QString m_company;
    QString m_clicks;
    QString m_duetime;
};

#endif // ADVERT_H
