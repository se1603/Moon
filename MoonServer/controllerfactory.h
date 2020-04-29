#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"
#include "audiencecontroller.h"
#include "commentcontroller.h"
#include "managercontroller.h"
#include "searchcontroller.h"
#include "manageusercontroller.h"

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
    ManageUserController *createManageUserController();//管理用户
private:
    ControllerFactory();
    static ControllerFactory* m_instance;
};

#endif // CONTROLLERFACTORY_H
