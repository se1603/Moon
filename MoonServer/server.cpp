#include "server.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint udpep(boost::asio::ip::udp::v4(),8001);

Server::Server()
{

}

void Server::acceptMreeage()
{
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,udpep));
    NetWork sock(udpsock);
    std::string message;

    boost::asio::ip::udp::endpoint sender_ep;
    //接收客户消息，接收到消息以后将处理任务添加到线程池任务队列
    while (1) {

        message = sock.receive(sender_ep);
        std::cout << "Client:" << message << std::endl;

        threadpool.append(std::bind(&Server::processMessage, this,message,sender_ep));
    }
}

void Server::processMessage(std::string message, endpoint ep)
{
//    std::cout << std::this_thread::get_id() << std::endl;
    std::cout << ep.address().to_string() + " send: " << message << std::endl;

    json j = json::parse(message);
    std::string request = j["request"];
    std::string replay;

    if(request == "category")
    {
        json js;
        js["menu"] = {"精选","电影","剧集","动漫","综艺"};
        std::string s = js.dump();
        replay = s;
        sendMessage(replay,ep);
    }

}

void Server::sendMessage(std::string message, endpoint ep)
{
    //    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字指向客户端。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,ep);
}
