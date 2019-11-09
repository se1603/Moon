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

    socket_ptr sendMessage(json jmessage);

    //界面显示
    Q_INVOKABLE QString showCategory(int type);  //显示分类
};

#endif // CLINET_H
