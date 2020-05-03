/*
 * Author:guchangrong 2016051604218
 * date:2020-03-12
 * 用户管理的控制器，连接数据代管者与服务器，将数据传给数据代管者或者从数据代管者取得数据
 */
#ifndef MANAGEUSERCONTROLLER_H
#define MANAGEUSERCONTROLLER_H

//#include "controllerfactory.h"
#include "manageuserbroker.h"
#include "controller.h"
#include "commentbroker.h"

class ManageUserController:public Controller
{
public:
    static ManageUserController* getInstance(){
        return m_instance;
    }
    ~ManageUserController();

    std::string getManageUserInfo(std::string informmark);//获取用户管理信息
    std::string getManageUserInfoByID(std::string id);//通过id获取用户管理信息
    bool deleteInformComment(std::string bereported, std::string comment); //删除被举报的评论
    bool updateInformmark(std::string id); //更改已删除的评论的记录标记为processed
    //添加举报记录
    bool addInformInfo(std::string informer, std::string bereported, std::string comment, std::string date);

private:
    ManageUserController();
    static ManageUserController* m_instance;
    ManageUserBroker* m_manageuserbroker;
    CommentBroker* m_commentbroker;
};

#endif // MANAGEUSERCONTROLLER_H
