#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"
#include "audiencecontroller.h"
#include "commentcontroller.h"
#include "managercontroller.h"
#include "searchcontroller.h"

class ControllerFactory
{
public:
    static ControllerFactory* getInstance(){
        return m_instance;
    }

    ~ControllerFactory();

    BrowseAndWatchController *createBrowseAndWatchController();
    AudienceController *createAudienceController();//用户
    CommentController *createCommentController();
    ManagerController *createManagerController();
    SearchController *createSearchController();
private:
    ControllerFactory();
    static ControllerFactory* m_instance;
};

#endif // CONTROLLERFACTORY_H
