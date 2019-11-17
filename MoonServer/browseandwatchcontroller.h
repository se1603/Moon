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

private:
    BrowseAndWatchController();
    static BrowseAndWatchController* m_instance;
    MovieAndTelevisionBroker* m_movieAndTelevisionBroker;

    std::string m_rtspAddress;
};

#endif // BROWSEANDWATCHCONTROLLER_H
