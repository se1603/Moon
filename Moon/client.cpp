#include "client.h"
#include <iostream>
#include <qdebug.h>
#include <dirent.h>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.1.11"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));

Client::Client(QObject *p) :
    QObject(p)
{
    connectServer();
}

void Client::connectServer()
{
    std::thread t(std::bind(&Client::getFile,this));
    t.detach();
}

socket_ptr Client::sendMessage(std::string message)
{
    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,serverep);
    return  udpsock;
}

QString Client::showCategory(QString interface)
{
    std::string result;

    //查找缓存
    if(categoryBuffer.find(interface.toStdString()) != categoryBuffer.end())
    {
        result = categoryBuffer[interface.toStdString()];
    }
    else
    {
        json request;
        request["request"] = "CATEGORY";
        request["interface"] = interface.toStdString();

        std::string message = request.dump();

        socket_ptr udpsock;
        udpsock = sendMessage(message);
        NetWork sock(udpsock);
        std::string res = sock.receive();

        json replay = json::parse(res);
        json categorys = replay["categorys"];
        result = categorys.dump();

        categoryBuffer[interface.toStdString()] = result;
    }

    QString qmlValue = QString::fromStdString(result);
//    qDebug() << qmlValue;
    return qmlValue;
}

QString Client::showRecommend(QString interface)
{
    std::string result;

    //查找缓存
    if(recommendInterfaceBuffer.find(interface.toStdString()) !=
            recommendInterfaceBuffer.end())
    {
        result = recommendInterfaceBuffer[interface.toStdString()];
    }
    else
    {
        json request;
        request["request"] = "RECOMMENDINTERFACE";
        request["interface"] = interface.toStdString();

        std::string message = request.dump();

        socket_ptr udpsock;
        udpsock = sendMessage(message);
        NetWork sock(udpsock);
        std::string res = sock.receive();

        json replay = json::parse(res);
        json qmlValue;
        qmlValue["resource"] = replay["resource"];
        qmlValue["firstRecommends"] = replay["firstRecommends"];
        qmlValue["secondRecommends"] = replay["secondRecommends"];

        result = qmlValue.dump();

        recommendInterfaceBuffer[interface.toStdString()] = result;
    }

    QString qmlValue = QString::fromStdString(result);
//    qDebug() << qmlValue;
    return qmlValue;
}

QString Client::showType(QString interface, QString type)
{
    std::string result;

    bool sendRequest = true;
    if(typeInterfaceBuffer.find(interface.toStdString()) !=
            typeInterfaceBuffer.end())
    {
        std::map<std::string,std::string> tmp =
                typeInterfaceBuffer[interface.toStdString()];
        if(tmp.find(type.toStdString()) != tmp.end())
        {
            result = tmp[type.toStdString()];
            sendRequest = false;
        }
    }

    if(sendRequest)
    {
        json request;
        request["request"] = "TYPEINTERFACE";
        request["interface"] = interface.toStdString();
        request["type"] = type.toStdString();

        std::string message = request.dump();

        socket_ptr udpsock;
        udpsock = sendMessage(message);
        NetWork sock(udpsock);
        std::string res = sock.receive();

        json replay = json::parse(res);
        json qmlValue;

        qmlValue = replay["movieAndTelevision"];

        result = qmlValue.dump();

        if(typeInterfaceBuffer.find(interface.toStdString()) ==
                typeInterfaceBuffer.end())
        {
            std::map<std::string,std::string> showresouce;
            showresouce[type.toStdString()] = result;
            typeInterfaceBuffer[interface.toStdString()] = showresouce;
        }
        else
        {
            std::map<std::string,std::string> showresouce;
            showresouce = typeInterfaceBuffer[interface.toStdString()];
            if(showresouce.find(type.toStdString()) == showresouce.end())
            {
                showresouce[type.toStdString()] = result;
            }
        }
    }

    QString qmlValue = QString::fromStdString(result);
//    qDebug() << qmlValue;
    return qmlValue;
}

void Client::getFile()
{
    std::string pathStart = "./";

    std::vector<std::string> pathNames{"recommend","films","comics","drama","varietyshow","actors","directors"};

    std::string pathEnd = ".tar.gz";

    for(int i = 0; i != pathNames.size();i++)
    {
        std::string path = pathStart + pathNames[i];
        DIR * dir;
        dir = opendir(path.data());
        if(dir == nullptr )
        {
            json root;
            root["request"] = "FILETRANSFER";
            root["fileName"] =
                    pathNames[i] + pathEnd;

            std::string message = root.dump();

            receiveFile(message);

            std::string commend = "tar xzvf " + pathNames[i] + pathEnd;
            system(commend.c_str());
        }
    }
}

void Client::receiveFile(std::string message)
{
    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,serverep);

    std::cout << "======Receive file size======" << std::endl;

    udpsock->receive_from(boost::asio::buffer(reinterpret_cast<char*>(&file_info), sizeof(file_info)),sender_ep);  //接收文件大小

    std::cout << "filename: " << file_info.filename_size << std::endl;
    if(file_info.filename_size == 0){
        std::cout << "The file doesn't exit." << std::endl;
        return;
    }
    boost::system::error_code error;
    receiveFilename(error,sender_ep,udpsock);
}

void Client::receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock)
{
    std::cout << "======Receive fileName======" << std::endl;
    if(e)
    {
        std::cout << boost::system::system_error(e).what() << std::endl;
    }

    int len = file_info.filename_size;
    char filename[len];
    memset(filename,0,sizeof (char) * len);

    //    boost::asio::ip::udp::endpoint sender_ep;

    udpsock->receive_from(boost::asio::buffer(filename,len),sender_ep); //接收文件名

    std::cout << filename << std::endl;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        std::cerr << "Failed to open file to write\n";
        return;
    }

    NetWork sock(udpsock);

    sock.receiveFile(fp);

    //    receive_file_content();
}

void Client::receive_file_content()
{
    std::cout << "=====Receive File Context=====" << std::endl;
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    NetWork sock(udpsock);

    sock.receiveFile(fp);
}
