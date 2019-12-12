#include "managercontroller.h"
#include "json.hpp"

using json = nlohmann::json;
ManagerController* ManagerController::m_instance = new ManagerController();

ManagerController::ManagerController()
{
    m_broker = ManagerBroker::getInstance();
    initManagers();
}

void ManagerController::initManagers()
{
    m_broker->initManagers();
}

std::string ManagerController::login(std::string number, std::string password)
{
    json result;
    result["request"] = "LOGIN";
    if(m_broker->login(number,password))
    {
        result["login"] = "LOGINSUCCEED";
        result["identity"] = std::to_string(m_broker->managerIdentity(number));
    }
    else
    {
        result["login"] = "LOGINFAILED";
    }

    std::string replay = result.dump();
    return replay;
}

