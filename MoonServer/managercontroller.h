#ifndef MANAGERCONTROLLER_H
#define MANAGERCONTROLLER_H

#include "controller.h"
#include "managerbroker.h"
#include "movieandtelevisionbroker.h"
#include "advertbroker.h"

class ManagerController : public Controller
{
public:
    static ManagerController* getInstance()
    {
        return m_instance;
    }

    void initManagers();
    void initAdverts();
    void initAdvertLinkVideo();
    std::string login(std::string number,std::string password);

    //字符串分割工具
    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);

    //广告运营
    //目录
    std::string showCategory();
    //详细目录
    std::string showCategoryType(std::string category);
    //添加广告
    std::string addAdvert(std::string advertname, std::string company,
                          std::string duetime, std::string videosmessage,
                          std::string videotype, std::string detailtype);
    //整个目录添加广告
    std::string addAdvertToCategory(std::string advert, std::string company,
                                    std::string duetime, std::string category);
    //搜索影视
    std::string searchVideo(std::string name);
    //初始化所有广告
    void initAllAdverts();
    //获取广告信息
    std::string showAdverts(std::string videoname, std::string videotype);
    //公司广告排名
    std::string showCompanyClicksRank(std::string companyname);
    //删除影视广告
    std::string deleteVideoAdverts(std::string deletemessage);
    //添加广告点击量
    std::string addAdvertClicks(std::string advertname);
    //获取所有已编辑的广告
    std::string showAllVideoAdverts();
    //获取所有已投放的映前广告
    std::string showAdvertising();
    //修改广告到期时间
    std::string changeAdvertTime(std::string advertname, std::string newdate);
    //
    std::string changeAdvertLocation(std::string advertname, std::string videoname,
                                     std::string newlocation);

    //搜索影视信息
    std::string seach(std::string name);

    //更新影视信息
    std::string update(std::string s);
private:
    ManagerController();
    static ManagerController* m_instance;
    ManagerBroker *m_broker;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;
    AdvertBroker* m_advertBroker;
};

#endif // MANAGERCONTROLLER_H
