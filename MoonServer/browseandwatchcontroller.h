#ifndef BROWSEANDWATCHCONTROLLER_H
#define BROWSEANDWATCHCONTROLLER_H

#include "controller.h"
#include "movieandtelevisionbroker.h"

class BrowseAndWatchController : public Controller
{
public:
    static BrowseAndWatchController* getInstance()
    {
        return m_instance;
    }

    ~BrowseAndWatchController();

    std::string InterfaceCategory(std::string interface); //每个界面下的目录
    std::string recommendInterface(std::string interface); //每个分类下的推荐页面

    std::string showTypeInterface(std::string interface, std::string type);
    std::string filmInterface(std::string type); //电影界面显示信息
    std::string dramaInterface(std::string type);//剧集页面显示
    std::string varietyInterface(std::string type);//综艺界面显示信息
    std::string comicInterface(std::string type);//动漫界面显示信息


    std::string getMovieInfomation(std::string name);//获取视频的基本信息
    std::string getActorInfomation(std::string name);//获取演员的基本信息

private:
    BrowseAndWatchController();
    static BrowseAndWatchController* m_instance;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;

    std::string m_rtspAddress;
};

#endif // BROWSEANDWATCHCONTROLLER_H
