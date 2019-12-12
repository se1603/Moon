#ifndef MANAGERCONTROLLER_H
#define MANAGERCONTROLLER_H

#include "controller.h"
#include "managerbroker.h"

class ManagerController : public Controller
{
public:
    static ManagerController* getInstance()
    {
        return m_instance;
    }

    void initManagers();
    std::string login(std::string number,std::string password);

private:
    ManagerController();
    static ManagerController* m_instance;
    ManagerBroker *m_broker;
};

#endif // MANAGERCONTROLLER_H
