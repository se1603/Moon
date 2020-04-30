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
    void processClientRequest(json j, endpoint ep);
    void processOMRequest(json j,endpoint ep);
    void sendMessage(std::string message, endpoint ep); //发送消息

    void sendFile(std::string filename,endpoint ep);  //发送文件

    void receiveFile(std::string message,endpoint clientep);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

     void  tarFiles();//压缩文件
private:
    FILE *fp;
    File_info file_info;

    ThreadPool threadpool;
    ControllerFactory *m_controllerFactory;
    BrowseAndWatchController *m_BrowseAndWatchController;
    AudienceController* m_AudienceController;//用户
    CommentController *m_commentController;
    ManagerController *m_managerController;
    SearchController *m_searchController;
    ManageUserController *m_manageuserController; //用户管理
};

#endif // SERVER_H
