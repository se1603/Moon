/*
 * Author:guchangrong 2016051604218
 * date:2020-03-12
 * 用户管理的数据库代管者，对数据库进行查找和修改操作，并将查询的数据存入容器
 */
#ifndef MANAGEUSERBROKER_H
#define MANAGEUSERBROKER_H

#include <map>
#include <iostream>
#include "manageuser.h"
#include "relationalbroker.h"

class ManageUserBroker : public RelationalBroker
{
public:
    ~ManageUserBroker();
    static ManageUserBroker* getInstance()
    {
        return m_instance;
    }

    //从数据库中读取举报信息
    void getInfoFromDataBase(std::vector<std::string> &v);

    void initManageUser(std::string id, std::string informer, std::string bereported, std::string comment, std::string date,std::string informcount, std::string informmark);
    //通过标识获取用户管理信息
    void getManageUserInfo(std::string informmark, std::vector<std::string> &v);
    //通过id获取用户管理信息
    void getManageUserInfoByID(std::string id, std::vector<std::string> &v);
    bool ManageUserInfoSize();

    //修改已删除平路记录的标记为processed
    bool updateInformmark(std::string id);
    //插入举报评论
    bool addInformInfo(std::string id, std::string informer, std::string bereported, std::string comment, std::string date, std::string count);
    //获取用户被举报次数
    int getbereportedcount(std::string bereported, std::vector<std::string> &v);
private:
    ManageUserBroker();
    static ManageUserBroker* m_instance;
    std::multimap<std::string, ManageUser> m_manageusers;
};

#endif // MANAGEUSERBROKER_H
