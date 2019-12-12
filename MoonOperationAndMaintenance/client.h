#ifndef CLIET_H
#define CLIET_H

#include <QObject>
#include "network.h"
#include "json.hpp"
#include "manager.h"

using json = nlohmann::json;

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *p = nullptr);

    socket_ptr sendMessage(std::string message);

    Q_INVOKABLE void sendLoginInfo(QString n,QString p);

signals:
    void loginSucceed(QString identity);
    void loginFailed();
    void hasLogined();

private:
    Manager *m_manager;
};

#endif // CLIET_H
