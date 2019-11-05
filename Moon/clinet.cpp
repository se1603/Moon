#include "clinet.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.1.13"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));



Clinet::Clinet(QObject *p) :
    QObject(p)
{
    connectServer();
}

void Clinet::connectServer()
{
    sendMessage();
}

socket_ptr Clinet::sendMessage(/*json jmessage*/)
{
    json jmessage;
    jmessage["request"] = "connect";
    std::cout << "Send message to server:"  << jmessage << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    std::string s = jmessage.dump();
    sock.sendto(s,serverep);
    return  udpsock;
}
