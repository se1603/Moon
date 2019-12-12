#include "client.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.1.13"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7789));

Client::Client(QObject *p) :
    QObject(p)
{

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

void Client::sendLoginInfo(QString n, QString p)
{
    json login;
    login["system"] = "MANAGE";
    login["request"] = "LOGIN";
    login["number"] = n.toStdString();
    login["password"] = p.toStdString();

    std::string message = login.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    json qmlValue;

    std::string result = replay["login"];

    if(result == "LOGINSUCCEED")
    {
        std::string identity = replay["identity"];
        QString ident = QString::fromStdString(identity);
        emit loginSucceed(ident);
    }
    else if(result == "LOGINFAILED")
    {
        emit loginFailed();
    }

}
