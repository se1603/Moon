/*
 * Author:guchangrong   2016051604218
 * data:2020-3-12
 * 管理用户初始化
 */
#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <iostream>
#include <vector>

class ManageUser
{
public:
    ManageUser(std::string id, std::string informer, std::string bereported, std::string comment, std::string date, std::string  informcount, std::string informmark);
    void manageUserInfo(std::vector<std::string> &v);//获得举报相关内容
    bool findByInformmark(std::string informmark); //通过举报标识查找
    bool findByBereported(std::string bereported);

private:
    std::string m_id;
    std::string m_informer;
    std::string m_bereported;
    std::string m_comment;
    std::string m_date;
    std::string m_informcount;
    std::string m_informmark;
};

#endif // MANAGEUSER_H
