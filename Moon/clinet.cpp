#include "clinet.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.43.111"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));



Clinet::Clinet(QObject *p) :
    QObject(p)
{
    connectServer();
}

void Clinet::connectServer()
{
//    std::thread t(std::bind(&Client::getFile,this));
//    t.detach();
//    showCategory(0);

}

socket_ptr Clinet::sendMessage(json jmessage)
{
//    json jmessage;
//    jmessage["request"] = "connect";
//    std::cout << "Send message to server:"  << jmessage << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
//    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    std::string s = jmessage.dump();
    sock.sendto(s,serverep);
    return  udpsock;
}

QString Clinet::showCategory(int type)
{
    boost::asio::ip::udp::endpoint sender_ep;
    json jmesagge;
    jmesagge["request"] = "category";
    
    std::cout << "请求侧边栏" << jmesagge << std::endl;
       
    socket_ptr udpsockptr;
    udpsockptr = sendMessage(jmesagge);

    NetWork sock(udpsockptr);

    std::string receive;
    receive = sock.receive(sender_ep);

    std::cout << receive << std::endl;

    json j = json::parse(receive);
//    std::string request = j["menu"];
    std::cout << j << std::endl;

//    Json::Value value;
//    Json::Value qmlvalue;
//    Json::Reader reader;
//    if(!reader.parse(receive,value))
//    {
//        std::cerr << "Receive message failed." << std::endl;
//    }
//    else {
//        qmlvalue["resource"] = value["resource"];
//    }
//    std::cout << qmlvalue.toStyledString() << std::endl;
    QString t = QString::fromStdString(j.dump());
    return t;
}
