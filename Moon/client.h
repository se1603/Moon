#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include "json.hpp"
#include <QObject>
#include <string>
#include <QString>

using json = nlohmann::json;

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *p = nullptr);

    void connectServer();

    socket_ptr sendMessage(std::string);

    //界面显示
    Q_INVOKABLE QString showCategory(QString interface);  //显示分类
    Q_INVOKABLE QString showRecommend(QString interface);  //显示各个页面的推荐影视
    Q_INVOKABLE QString showType(QString interface,QString type);  //显示各个类型的影视

    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

private:
    //文件
    FILE *fp;
    File_info file_info;
    std::map<std::string,std::string> categoryBuffer;
    std::map<std::string,std::string> recommendInterfaceBuffer;
    std::map<std::string,std::map<std::string,std::string>> typeInterfaceBuffer;
};

#endif // Client_H
