#ifndef CLINET_H
#define CLINET_H

#include "network.h"
#include "json.hpp"
#include <QObject>

using json = nlohmann::json;

class Clinet : public QObject
{
    Q_OBJECT
public:
    Clinet(QObject *p = nullptr);

    void connectServer();

    socket_ptr sendMessage();

    //界面显示
};

#endif // CLINET_H
