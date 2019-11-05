/* Author:王梦娟
 * Date:2019-11-1
 * Note:
*/
#ifndef SERVER_H
#define SERVER_H

#include "threadpool.h"
#include "network.h"
#include "json.hpp"

using json = nlohmann::json;

class Server
{
public:
    Server();

    void acceptMreeage();
    void processMessage(std::string message, endpoint ep);  //处理消息
    void sendMessage(std::string message, endpoint ep); //发送消息

private:
    ThreadPool threadpool;
};

#endif // SERVER_H
