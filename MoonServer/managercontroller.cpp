#include "managercontroller.h"
#include "json.hpp"

using json = nlohmann::json;
ManagerController* ManagerController::m_instance = new ManagerController();

ManagerController::ManagerController()
{
    m_broker = ManagerBroker::getInstance();
    m_advertBroker = AdvertBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
    initManagers();
    initAdverts();
    initAdvertLinkVideo();
}

void ManagerController::initManagers()
{
    m_broker->initManagers();
}

void ManagerController::initAdverts()
{
    m_advertBroker->initAdverts();
}

void ManagerController::initAdvertLinkVideo()
{
    m_advertBroker->initAdvertLinks();
    auto links = m_advertBroker->readAdvertLinks();

    for(auto item = links.begin(); item != links.end(); ++item){
        std::cout << "lalala" << std::endl;
        auto advert = m_advertBroker->findAdvert(item->first);
        auto video = m_movieAndTelevisionBroker->initAdvertLinks(item->second, advert);
        m_advertBroker->initVideoLink(item->first, video);
    }
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

void ManagerController::splictString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

std::string ManagerController::showCategory()
{
    json result;
    json arry;

    std::vector<std::string> categorys = m_movieAndTelevisionBroker->mainCategory();
    for(auto iter = categorys.begin(); iter != categorys.end(); iter++){
        json value;
        value["name"] = *iter;
        arry.push_back(value);
    }
    result["categorys"] = arry;

    std::string replay = result.dump();
    return replay;
}

std::string ManagerController::showCategoryType(std::string category)
{
    json result;
    json arry;

    std::vector<std::string> types = m_movieAndTelevisionBroker->InterfaceCategory(category);
    for(auto iter = types.begin(); iter != types.end(); iter++){
        json value;
        value["name"] = *iter;
        arry.push_back(value);
    }
    result["detailcategorys"] = arry;

    std::string replay = result.dump();
    return replay;
}

std::string ManagerController::addAdvert(std::string advertname, std::string company,
                                         std::string duetime, std::string videosmessage,
                                         std::string videotype)
{
    json value;
    std::vector<std::string> videos;
    splictString(videosmessage,videos,"/");

    bool res1 = m_advertBroker->addAdvert(advertname, company, duetime);

    Advert* a;

    if(res1 == true){
        a = m_advertBroker->createAdvertEntity(advertname,company,duetime);
    }else{
        a = m_advertBroker->findAdvert(advertname);
    }

    if(a != nullptr){

        for(auto &v:videos){
            auto mv = m_movieAndTelevisionBroker->addAdvert(v,a,videotype);
            m_advertBroker->initVideoLink(advertname, mv);
            m_advertBroker->addAdvertLinkVideo(advertname, v);
        }

        value["replay"] = "SUCCEED";
    }
    else{
        value["replay"] = "FAILED";
    }
    std::string replay = value.dump();
    return replay;
}

std::string ManagerController::searchVideo(std::string name)
{
    json result;
    json arry;

    std::map<std::string, std::string> message =
            m_movieAndTelevisionBroker->searchVideos(name);

    for(auto iter = message.begin(); iter != message.end(); iter++){
        json value;
        value["name"] = iter->first;
        value["post"] = iter->second;
        arry.push_back(value);
    }

    if(arry.size() == 0){
        json value;
        value["name"] = "暂无搜索结果";
        value["post"] = "none";
        arry.push_back(value);
    }

    result["searchmessage"] = arry;
    std::string replay = result.dump();
    return replay;
}

void ManagerController::initAllAdverts()
{
    m_advertBroker->initAdverts();
}

std::string ManagerController::showAdverts(std::string videoname, std::string videotype)
{
    std::cout << "this is 1" << videoname << videotype << std::endl;
    std::vector<Advert*> vec = m_movieAndTelevisionBroker->showAdverts(videoname, videotype);

    json replay;
    json arry;
    std::vector<std::string> detail;

    if(vec.size() != 0){
        for(auto &v:vec){
            v->showDetails(detail);
            json value;
            value["name"] = detail[0];
            value["company"] = detail[1];
            value["clicks"] = detail[2];
            value["duetime"] = detail[3];
            arry.push_back(value);
            detail.clear();
        }
    }
    else
    {
        json value;
        value["name"] = "NULL";
        value["company"] = "NULL";
        value["clicks"] = "NULL";
        value["duetime"] = "NULL";
        arry.push_back(value);
    }

    replay["adverts"] = arry;
    std::string res = replay.dump();
    return res;
}

std::string ManagerController::showCompanyClicksRank(std::string companyname)
{
    json replay;
    json arry;

    auto ranklist = m_advertBroker->rankCompanyAdvert(companyname);

    if(ranklist.size() != 0){
        std::vector<std::string> tmp;
        for(auto &r:ranklist){
            r->showDetails(tmp);
            json value;
            value["name"] = tmp[0];
            value["clicks"] = tmp[2];
            value["duetime"] = tmp[3];
            arry.push_back(value);
            tmp.clear();
        }
    }else{
        json value;
        value["name"] = "NULL";
        value["clicks"] = "NULL";
        value["duetime"] = "NULL";
        arry.push_back(value);
    }

    replay["adverts"] = arry;
    std::string res = replay.dump();
    return res;
}

std::string ManagerController::deleteVideoAdverts(std::string videoname, std::string advertname)
{
    json replay;

    std::vector<std::string> adverts;
    splictString(advertname,adverts,"/");
    bool res = true;

    for(auto &a:adverts){
        bool res1 = m_movieAndTelevisionBroker->deleteVideoAdverts(videoname,a);
        bool res2 = m_advertBroker->deleteVideoLink(a,videoname);
        bool res3 = m_advertBroker->deleteVideoAdvertLink(videoname,a);

        m_advertBroker->judgeAdvertRemove(a);

//        std::cout << "a:" << res1 << res2 << res3 << std::endl;

        if(res1 == false || res2 == false || res3 == false)
            res = false;
    }

    if(res == true){
        replay["replay"] = "SUCCEED";
    }else{
        replay["replay"] = "FAILED";
    }

    std::string message = replay.dump();
    return message;
}
