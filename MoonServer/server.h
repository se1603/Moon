/* Author:王梦娟
 * Date:2019-11-1
 * Note:
*/
#ifndef SERVER_H
#define SERVER_H

#include "threadpool.h"
#include "network.h"
#include "json.hpp"
#include "controllerfactory.h"

using json = nlohmann::json;

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Server
{
public:
    Server();

    void acceptMreeage();
    void processMessage(std::string message, endpoint ep);  //处理消息
    void sendMessage(std::string message, endpoint ep); //发送消息

    void sendFile(std::string filename,endpoint ep);  //发送文件

private:
    ThreadPool threadpool;
    ControllerFactory *m_controllerFactory;
    BrowseAndWatchController *m_BrowseAndWatchController;
    AudienceController* m_AudienceController;//用户
};

#endif // SERVER_H
