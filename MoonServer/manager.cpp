#include "manager.h"

Manager::Manager()
{

}

Manager::Manager(std::string number, int identity)
{
    m_number = number;
    m_identity = identity;
    m_name = "";
    m_passWord = "";
}

int Manager::identity()
{
    return m_identity;
}

//bool Manager::login(std::string password)
//{
//    if(password == m_passWord)
//        return true;
//    return false;
//}
