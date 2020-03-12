/*
 * 1 用户管理
 * 2 影视管理
 * 3 广告管理
 *
 * */
#ifndef MANAGER_H
#define MANAGER_H

#include <string>

class Manager
{
public:
    Manager();
    Manager(std::string number,int identity);

//    bool login(std::string password);
    int identity();

private:
    std::string m_number;
    std::string m_name;
    std::string m_passWord;
    int m_identity;
};

#endif // MANAGER_H
