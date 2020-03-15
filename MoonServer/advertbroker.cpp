/* Author:董梦丹
* Date:2020-02-17
* Note:广告
*/
#include "advertbroker.h"

AdvertBroker* AdvertBroker::m_instance = new AdvertBroker();

AdvertBroker::AdvertBroker()
{

}

AdvertBroker::~AdvertBroker()
{
    delete m_instance;
}

bool AdvertBroker::addAdvert(std::string advertname, std::string company, std::string duetime)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);

    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "addAdvert:connect MYSQL failed" << std::endl;
    }else{
        std::cout << "addAdvert:connect MYSQL succeed" << std::endl;
    }

    std::string click = "0";

    std::string sql = "insert into Advert(name,company,clicks,duetime) value('"+advertname+"','"+company+"','"+click+"','"+duetime+"');";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Insert Advert Failed" << std::endl;
        return false;
    }else{
        std::cout << "Insert Advert Succeed" << std::endl;
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

Advert *AdvertBroker::createAdvertEntity(std::string name, std::string company, std::string duetime)
{
    Advert* newadvert = new Advert(name,company,"0",duetime);
//    for(auto item = currentAdverts.begin(); item != currentAdverts.end(); item++){
//        std::cout << item->first << std::endl;
//    }
    currentAdverts.insert(std::pair<std::string, Advert*>(name, newadvert));
    return newadvert;
}

bool AdvertBroker::addAdvertLinkVideo(std::string advertname, std::string videoname)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);

    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "addAdvertLink:connect MYSQL failed" << std::endl;
    }else{
        std::cout << "addAdvertLink:connect MYSQL succeed" << std::endl;
    }

    std::string sql = "insert into AdvertLinkVideo(advertName,videoName) value('"+advertname+"','"+videoname+"');";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Insert AdvertLink Failed" << std::endl;
        return false;
    }else{
        std::cout << "Insert AdvertLink Succeed" << std::endl;
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

bool AdvertBroker::initAdverts()
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "(Adverts)Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "(Adverts)Connect MYSQL succeed." << std::endl;
    }


    std::string sql = "select * from Advert;";

    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(advert)" << std::endl;
    }
    else
    {
        std::vector<std::string> advertinfo;
        result = mysql_use_result(mysql);
        while(1)
        {
            row = mysql_fetch_row(result);
            if(row == nullptr){
                return false;
            }else{
                for(unsigned int i=0;i<mysql_num_fields(result);++i){
                    advertinfo.push_back(std::string(row[i]));
                }
                Advert* a = new Advert(advertinfo[0], advertinfo[1],
                        advertinfo[2], advertinfo[3]);

                currentAdverts.insert(std::make_pair(advertinfo[0],a));
                advertinfo.clear();
            }
        }
    }
    if(mysql != nullptr)
        mysql_close(mysql);

    return true;
}

void AdvertBroker::deleteAdvert(std::string advertname)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);

    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "deleteAdvert:connect MYSQL failed" << std::endl;
    }else{
        std::cout << "deleteAdvert:connect MYSQL succeed" << std::endl;
    }

    std::string sql = "delete from Advert where name = '"+advertname+"';";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Delete Advert Failed" << std::endl;
    }else{
        std::cout << "Delete Advert Succeed" << std::endl;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

Advert *AdvertBroker::findAdvert(std::string advertname)
{
    for(auto item = currentAdverts.begin(); item != currentAdverts.end(); item++){
        if(item->first == advertname){
            return item->second;
        }
    }
}

bool AdvertBroker::initAdvertLinks()
{
    MYSQL* mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "(AdvertLinks)Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "(AdvertLinks)Connect MYSQL succeed." << std::endl;
    }

    std::string sql = "select * from AdvertLinkVideo;";
    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(advertlink)" << std::endl;
    }else{
        std::vector<std::string> links;
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr){
                return false;
            }else{
                std::cout << "----" << std::endl;
                for(unsigned i = 0; i < mysql_num_fields(result); ++i){
                    links.push_back(std::string(row[i]));
                }
                for(auto &l:links) {
                    std::cout << "this is: " << l << std::endl;
                }
                currentAdvertLinks.insert(std::make_pair(links[0],links[1]));
                links.clear();
            }
        }
    }
    if(mysql != nullptr)
        mysql_close(mysql);

    return true;
}

std::multimap<std::string, std::string> AdvertBroker::readAdvertLinks()
{
    std::cout << "zheshisha" << currentAdvertLinks.size() << std::endl;
    return currentAdvertLinks;
}

bool AdvertBroker::updateAdvertClicks(std::string advertname, std::string newclicks)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "(UpdateClicks)Connect MYSQL failed" << std::endl;
    }else{
        std::cout << "(UpdateClicks)Connect MYSQL succeed" << std::endl;
    }

    std::string sql = "update Advert set clicks ='"+newclicks+"' where name = '"+advertname+"';";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Update clicks failed" << std::endl;
        return false;
    }else{
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

std::vector<Advert *> AdvertBroker::rankCompanyAdvert(std::string companyname)
{
    std::multimap<int,Advert*> list;
    for(auto &a:currentAdverts){
        if(a.second->sameCompany(companyname) == true)
            list.insert(std::make_pair(a.second->showClicks(),a.second));
    }

    std::vector<Advert*> ranklist;
    for(auto item = list.rbegin(); item != list.rend(); item++){
        ranklist.push_back(item->second);
    }

    return ranklist;
}

bool AdvertBroker::deleteVideoAdvertLink(std::string video, std::string advert)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "(DeleteLinks)Connect MYSQL failed" << std::endl;
    }else{
        std::cout << "(DeleteLinks)Connect MYSQL succeed" << std::endl;
    }

    std::string sql = "delete from AdvertLinkVideo where advertName ='"+advert+"' and videoName = '"+video+"';";

    if(mysql_query(mysql,sql.data())){
        std::cout << "Delete link failed" << std::endl;
        return false;
    }else{
        return true;
    }

    if(mysql != nullptr)
        mysql_close(mysql);
}

bool AdvertBroker::deleteVideoLink(std::string advertname, std::string videoname)
{
    bool res1;

    for(auto item = currentAdverts.begin(); item != currentAdverts.end(); ++item){
        if(item->first == advertname){
            res1 = item->second->deleteVideoLink(videoname);
//            std::cout << res1 << "boolvalue" << std::endl;
        }
    }

    for(auto item = currentAdvertLinks.begin(); item != currentAdvertLinks.end(); ++item){
        if(item->first == advertname && item->second == videoname){
            currentAdvertLinks.erase(item);
            break;
        }
    }

    if(res1 == true){
        return true;
    }else{
        return false;
    }
}

void AdvertBroker::judgeAdvertRemove(std::string advertname)
{
    for(auto item = currentAdverts.begin(); item != currentAdverts.end(); ++item){
        if(item->first == advertname){
            if(item->second->isVideoEmpty() == true)
                deleteAdvert(advertname);
        }
    }
}

void AdvertBroker::initVideoLink(std::string advertname, MovieAndTelevision *mv)
{
    for(auto &a:currentAdverts){
        if(a.first == advertname)
            a.second->addVideoLink(mv);
    }
}
