#ifndef MANAGERBROKER_H
#define MANAGERBROKER_H

#include "relationalbroker.h"
#include "manager.h"

class ManagerBroker : public RelationalBroker
{
public:
    static ManagerBroker* getInstance()
    {
        return m_instance;
    }
    ~ManagerBroker();

    void initManagers();
    bool login(std::string number,std::string password);
    int managerIdentity(std::string number);

private:
    ManagerBroker();
    static ManagerBroker* m_instance;
    std::vector<Manager*> m_logined;
    std::map<std::string,Manager*> m_managers;
};

#endif // MANAGERBROKER_H
