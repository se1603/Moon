#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class Client;

class Manager
{
    friend class Client;
public:
    Manager();

    QString m_password;
    QString m_number;
};

#endif // MANAGER_H
