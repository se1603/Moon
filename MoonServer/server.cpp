#include "server.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint udpep(boost::asio::ip::udp::v4(),8001);

Server::Server()
{
    m_controllerFactory = ControllerFactory::getInstance();
    m_BrowseAndWatchController = m_controllerFactory->createBrowseAndWatchController();
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
//        std::cout << "Client:" << message << std::endl;

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

    if(request == "FILETRANSFER")
    {
        sendFile(j["fileName"],ep);
        replay = "FILETRANSFERSUCCEED";
        sendMessage(replay,ep);
    }
    else if(request == "CATEGORY")
    {
        replay = m_BrowseAndWatchController->InterfaceCategory(j["interface"]);
        sendMessage(replay,ep);
    }
    else if(request == "RECOMMENDINTERFACE")
    {
        replay = m_BrowseAndWatchController->recommendInterface(j["interface"]);
        sendMessage(replay,ep);
    }

}

void Server::sendMessage(std::string message, endpoint ep)
{
//        std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字指向客户端。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,ep);
}

void Server::sendFile(std::string filename, endpoint ep)
{
    std::cout << "Send file:" << filename << std::endl;

    socket_ptr sock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    std::string path = "../MoonServer/images/";
    path += filename;
    std::cout << path << std::endl;
    auto fileName = path.data();
    FILE *fp = fopen(fileName,"rb");

    boost::shared_ptr<FILE> file_ptr(fp,fclose); //退出后自动关闭文件

    //打开文件失败发送一个空的file_info到客户端
    if(fp == NULL){
        std::cout << "Cannot open file." << std::endl;
        File_info file_info;
        char buffer[16];
        memcpy(buffer, &file_info,sizeof (file_info));
        sock->send_to(boost::asio::buffer(buffer,sizeof(buffer)),ep);
        return;
    }

    clock_t costTime = clock();  //记录传送文件时长

    const size_t buffer_size = 512;
    char buffer[buffer_size];
    memset(buffer,0,sizeof (char) * buffer_size);
    File_info file_info;

    int filename_size = strlen(filename.data()) + 1;     //文件名
    size_t file_info_size = sizeof (file_info);
    size_t total_size = file_info_size + filename_size;
    if(total_size > buffer_size){
        std::cerr << "File name is too long";
        return;
    }

    file_info.filename_size = filename_size;

    fseek(fp,0,SEEK_END);     //设置文件指针到文件末尾
    file_info.filesize = ftell(fp);  //得到文件的大小
    rewind(fp);    //重新指向文件头

    std::cout << "filenamesize: " << filename_size << std::endl;
    std::cout << "filesize: " << file_info.filesize << std::endl;
    std::cout << "totalsize: " << total_size << std::endl;

    memcpy(buffer, &file_info, file_info_size);
    sock->send_to(boost::asio::buffer(buffer,file_info_size),ep);  //发送大小

    memcpy(buffer, filename.data(), filename_size);
    sock->send_to(boost::asio::buffer(buffer,filename_size),ep);  //发送文件名

    std::cout << "Send file: " << buffer << "\n";

    //发送文件内容
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    NetWork filesock(udpsock);

    long int total_bytes_read = 0;
    total_bytes_read = filesock.sendFile(fp,ep);

    //发送文件内容结束

    std::cout << "send totalsize: " << total_bytes_read << std::endl;
    costTime = clock() - costTime;
    if(costTime == 0) costTime = 1;

    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / costTime;
    std::cout << "cost time: " << costTime / (double) CLOCKS_PER_SEC  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";
    return;
}
