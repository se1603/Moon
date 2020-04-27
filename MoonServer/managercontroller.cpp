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
//        std::cout << "lalala" << std::endl;
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
                                         std::string videotype, std::string detailtype)
{
    json value;
    std::vector<std::string> videos;
    if(videosmessage != "")
        splictString(videosmessage,videos,"/");

    std::vector<std::string> types;
    if(detailtype != "")
        splictString(detailtype,types,"/");

    //    bool res1 = m_advertBroker->addAdvert(advertname, company, duetime);

    //    if(res1 == true){
    //        a = m_advertBroker->createAdvertEntity(advertname,company,duetime);
    //    }else{
    //        a = m_advertBroker->findAdvert(advertname);
    //    }

    Advert* a;
    a = m_advertBroker->findAdvert(advertname);

    if(a != nullptr){

        for(auto &v:videos){
            int flag = 0;
            auto mv = m_movieAndTelevisionBroker->addAdvert(v,a,videotype,flag);
            if(flag == 0){
                m_advertBroker->initVideoLink(advertname, mv);
                m_advertBroker->addAdvertLinkVideo(advertname, v);
                m_advertBroker->addCurrentLink(advertname,v);
            }
        }

        for(auto &t:types){
            auto vec = m_movieAndTelevisionBroker->findTypeVideo(t,videotype);
            for(auto &v:vec){
                int flag = 0;
                auto mv = m_movieAndTelevisionBroker->addAdvert(v,a,videotype,flag);
                if(flag == 0){
                    m_advertBroker->initVideoLink(advertname, mv);
                    m_advertBroker->addAdvertLinkVideo(advertname, v);
                    m_advertBroker->addCurrentLink(advertname,v);
                }
            }
        }

        value["replay"] = "SUCCEED";
    }
    else{
        value["replay"] = "FAILED";
    }
    std::string replay = value.dump();
    return replay;
}

std::string ManagerController::addAdvertToCategory(std::string advert, std::string company, std::string duetime, std::string category)
{
    json value;

    //    bool res1 = m_advertBroker->addAdvert(advert, company, duetime);


    //    if(res1 == true){
    //        a = m_advertBroker->createAdvertEntity(advert,company,duetime);
    //    }else{
    //        a = m_advertBroker->findAdvert(advert);
    //    }

    Advert* a;
    a = m_advertBroker->findAdvert(advert);

    if(a != nullptr){

        auto videos = m_movieAndTelevisionBroker->findCategory(category);
        for(auto &v:videos){
            int flag = 0;
            auto mv = m_movieAndTelevisionBroker->addAdvert(v,a,category,flag);
            if(flag == 0){
                m_advertBroker->initVideoLink(advert, mv);
                m_advertBroker->addAdvertLinkVideo(advert, v);
                m_advertBroker->addCurrentLink(advert,v);
            }
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

std::string ManagerController::deleteVideoAdverts(std::string deletemessage)
{
    json replay;

    std::vector<std::string> links;
    splictString(deletemessage,links,"#");
    bool res = true;

    for(auto &l:links){
        std::vector<std::string> tmp;
        splictString(l,tmp,"/");

        bool res1 = m_movieAndTelevisionBroker->deleteVideoAdverts(tmp[1],tmp[0]);
        bool res2 = m_advertBroker->deleteVideoLink(tmp[0],tmp[1]);
        bool res3 = m_advertBroker->deleteVideoAdvertLink(tmp[1],tmp[0]);

//        m_advertBroker->judgeAdvertRemove(tmp[1]);

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

std::string ManagerController::addAdvertClicks(std::string advertname)
{
    json replay;

    bool res = m_advertBroker->updateAdvertClicks(advertname);
    if(res == true){
        replay["replay"] = "SUCCEED";
    }else{
        replay["replay"] = "FAILED";
    }

    std::string message = replay.dump();
    return message;
}

std::string ManagerController::showAllVideoAdverts()
{
    json replay;
    json arry;

    auto adverts = m_advertBroker->showAllVideoAdverts();

    if(adverts.size() != 0){
        for(auto &a:adverts){
            json value;
            value["name"] = a[0];
            value["company"] = a[1];
            value["duetime"] = a[3];
            arry.push_back(value);
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

std::string ManagerController::showAdvertising()
{
    json replay;
    json arry;

//    std::cout <<"oneday" << std::endl;
    auto adverts = m_advertBroker->showAdvertising();
//    std::cout <<"luyao" << std::endl;

    if(adverts.size() != 0){
        for(auto &a:adverts){
            json value;
            value["name"] = a[0];
            value["company"] = a[1];
            value["duetime"] = a[3];
            value["videoname"] = a[4];
            arry.push_back(value);
        }
    }else{
        json value;
        value["name"] = "NULL";
        arry.push_back(value);
    }

    replay["adverts"] = arry;
    std::cout << "@@@\n" << replay.dump() << std::endl;
    std::string res = replay.dump();
    return res;
}

std::string ManagerController::changeAdvertTime(std::string advertname, std::string newdate)
{
    json replay;

    bool res1 = m_advertBroker->changeAdvertTime(advertname, newdate);
    bool res2 = m_advertBroker->changeAdvertTimeDB(advertname, newdate);

    if(res1 == true && res2 == true){
        replay["replay"] = "SUCCEED";
    }else{
        replay["replay"] = "FAILED";
    }

    std::string message = replay.dump();
    return message;
}

std::string ManagerController::changeAdvertLocation(std::string advertname, std::string videoname, std::string newlocation)
{
    json replay;
    auto res = m_movieAndTelevisionBroker->searchVideos(newlocation);
    if(res.size() == 0){
        replay["replay"] = "NOVIDEO";
    }else{
        std::cout << "wojinlaile" << std::endl;
        auto advert = m_advertBroker->findAdvert(advertname);
        int flag = 0;
        m_movieAndTelevisionBroker->addAdvert(newlocation, advert, "未知", flag);
        m_movieAndTelevisionBroker->deleteVideoAdverts(videoname, advertname);
        bool res1 = m_advertBroker->deleteVideoLink(advertname, videoname);
        bool res2 = m_advertBroker->deleteVideoAdvertLink(videoname, advertname);
        bool res3 = m_advertBroker->addAdvertLinkVideo(advertname, newlocation);
        m_advertBroker->addCurrentLink(advertname, newlocation);

        if(res1 == true && res2 == true && res3 == true){
            replay["replay"] = "SUCCEED";
        }else{
            replay["replay"] = "FAILED";
        }
    }

    std::string message = replay.dump();
    return message;
}

std::string ManagerController::seach(std::string name)
{
    //   auto m = m_movieAndTelevisionBroker->getVideoInfo(name);
    json root;
    std::string out;
    root["request"] = "SEACH";
    root["name"] = name;
    auto f = m_movieAndTelevisionBroker->getVideoInfo(name);
    json value;
    json types;
    root["videotype"] = 1;
    if(f.size() == 0){
        root["empty"]="EMPTY";
    }else{
        root["empty"] = "NULL";
    }

    for(int i = 0;i != f.size();i++){
        json type;
        if(i == 0){
            value["esipode"] = f[0];
        }else if(i == 1){
            value["introduction"] = f[1];
        }else if(i == 2){
            value["category"] = f[2];
        }else if(i==3){
            value["region"] = f[3];
        }else if(i == 4){
            value["post"] = f[4];
        }
        else{
            type["type"] = f[i];
            types.push_back(type);
            //            types.append(type);w
        }
    }
    value["name"] = name;
    value["videotype"] = types;
    root["resource"] = value;
    out = root.dump();

    return out;
}

std::string ManagerController::update(std::string s)
{
    json update;
    update["UPDATE"] ="update";
    if(m_movieAndTelevisionBroker->updateVideos(s)){
        update["MES"]= "sucessed";
    }else{
        update["MES"] = "failed";
    }
    std::string out = update.dump();
    return out;
}
