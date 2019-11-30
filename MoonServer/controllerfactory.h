#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include "browseandwatchcontroller.h"

class ControllerFactory
{
public:
    static ControllerFactory* getInstance(){
        return m_instance;
    }

    ~ControllerFactory();

    BrowseAndWatchController *createBrowseAndWatchController();

private:
    ControllerFactory();
    static ControllerFactory* m_instance;
};

#endif // CONTROLLERFACTORY_H
