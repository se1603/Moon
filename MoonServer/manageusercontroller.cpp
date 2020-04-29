/*
 * Author:guchangrong 2016051604218
 * date:2020-03-12
 * 用户管理的控制器实现，连接数据代管者与服务器，将数据传给数据代管者或者从数据代管者取得数据
 */
#include "manageusercontroller.h"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

ManageUserController* ManageUserController::m_instance = new ManageUserController();

ManageUserController::~ManageUserController()
{
    delete m_instance;
}

std::string ManageUserController::getManageUserInfo(std::string informmark)
{
    std::vector<std::string> vec;
    json values;
    json root;
    std::string out;
    root["request"] = "GETMANAGEUSERINFO";
    if(m_manageuserbroker->ManageUserInfoSize() == 0){
        std::vector<std::string> v;
        m_manageuserbroker->getInfoFromDataBase(v);
        for(int i = 0; i != v.size(); i += 7){
            m_manageuserbroker->initManageUser(v[i], v[i+1], v[i+2], v[i+3], v[i+4],v[i+5],v[i+6]);
            json value;
            if(v[i+6] == informmark){
                value["id"] = v[i];
                value["informer"] = v[i+1];
                value["bereported"] = v[i+2];
                value["comment"] = v[i+3];
                value["date"] = v[i+4];
                value["informcount"] = v[i+5];
                value["informmark"] = v[i+6];
                values.push_back(value);
            }
        }
    } else {
        m_manageuserbroker->getManageUserInfo(informmark, vec);
        if(vec.size() != 0){
            for(auto i = 0; i != vec.size(); i += 7){
                json value;
                value["id"] = vec[i];
                value["informer"] = vec[i+1];
                value["bereported"] = vec[i+2];
                value["comment"] = vec[i+3];
                value["date"] = vec[i+4];
                value["informcount"] = vec[i+5];
                value["informmark"] = vec[i+6];
                values.push_back(value);
            }
        }
    }
    root["manageuserinfo"] = values;
    out = root.dump();
    std::cout << out << std::endl;
    return out;
}

std::string ManageUserController::getManageUserInfoByID(std::string id)
{
    std::vector<std::string> vec;
    json values;
    json root;
    std::string out;
    root["request"] = "GETMANAGEUSERINFOBYID";
    m_manageuserbroker->getManageUserInfoByID(id,vec);
    if(vec.size() != 0){
        for(auto i = 0; i != vec.size(); i += 7){
            json value;
            value["id"] = vec[i];
            value["informer"] = vec[i+1];
            value["bereported"] = vec[i+2];
            value["comment"] = vec[i+3];
            value["date"] = vec[i+4];
            value["informcount"] = vec[i+5];
            value["informmark"] = vec[i+6];
            values.push_back(value);
        }
    }
    root["manageuserinfobyid"] = values;
    out = root.dump();
    std::cout << out << std::endl;
    return out;
}

bool ManageUserController::deleteInformComment(std::string bereported, std::string comment)
{
    if(m_commentbroker->deleteComment(bereported, comment) == true){
        return true;
    } else {
        return false;
    }
}

bool ManageUserController::updateInformmark(std::string id)
{
    if(m_manageuserbroker->updateInfoemmark(id) == true){
        return true;
    } else {
        return false;
    }
}

ManageUserController::ManageUserController()
{
    m_manageuserbroker = ManageUserBroker::getInstance();
}
