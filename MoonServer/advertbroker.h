/* Author:董梦丹
* Date:2020-02-01
* 最后修改:04-27
* Note:广告
*/
#ifndef ADVERTBROKER_H
#define ADVERTBROKER_H
#include "relationalbroker.h"
#include "advert.h"

class AdvertBroker : public RelationalBroker
{
public:
    static AdvertBroker* getInstance()
    {
        return m_instance;
    }
    ~AdvertBroker();

    //添加新的一条广告
    bool addAdvert(std::string advertname, std::string company, std::string duetime);
    //生成新的广告
    Advert* createAdvertEntity(std::string name, std::string company,
                               std::string duetime);
    //添加链接
    bool addAdvertLinkVideo(std::string advertname, std::string videoname);
    //生成广告
    bool initAdverts();
    //删除广告
    void deleteAdvert(std::string advertname);
    //寻找广告
    Advert* findAdvert(std::string advertname);
    //生成广告链接
    bool initAdvertLinks();
    //读取广告链接
    std::multimap<std::string, std::string> readAdvertLinks();
    //更新点击量
    bool updateAdvertClicks(std::string advertname);
    //公司广告排名
    std::vector<Advert*> rankCompanyAdvert(std::string companyname);
    //删除广告链接
    bool deleteVideoAdvertLink(std::string video, std::string advert);
    //删除视频链接
    bool deleteVideoLink(std::string advertname, std::string videoname);
    //判断是否删除数据库的广告
//    void judgeAdvertRemove(std::string advertname);
    //生成视频链接
    void initVideoLink(std::string advertname, MovieAndTelevision* mv);
    //获取所有已编辑的广告
    std::vector<std::vector<std::string> > showAllVideoAdverts();
    //获取所有已投放的映前广告
    std::vector<std::vector<std::string> > showAdvertising();
    //添加广告链接
    void addCurrentLink(std::string advertname, std::string videoname);
    //修改广告到期时间
    bool changeAdvertTime(std::string advertname, std::string newdate);
    //修改数据库广告到期时间
    bool changeAdvertTimeDB(std::string advertname, std::string newdate);
private:
    AdvertBroker();
    static AdvertBroker* m_instance;

    std::map<std::string,Advert*> currentAdverts;
    std::multimap<std::string,std::string> currentAdvertLinks;
};

#endif // ADVERTBROKER_H
