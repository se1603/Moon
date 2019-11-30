#include "server.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint udpep(boost::asio::ip::udp::v4(),8001);

Server::Server()
{
    m_controllerFactory = ControllerFactory::getInstance();
    m_BrowseAndWatchController = m_controllerFactory->createBrowseAndWatchController();
    m_AudienceController = m_controllerFactory->createAudienceController();
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
    else if(request == "VERIFYINFO")
    {
        if(m_AudienceController->checkoutAudience(j["name"]) == true){
            std::cout << "!!!!----" << std::endl;
            if(m_AudienceController->verifyAudience(j["name"],j["password"]) == true)
            {
                std::cout << "wojinlaile----" << std::endl;
                replay = "LOGINSUCCEED";
                sendMessage(replay,ep);
            }
            else
            {
                replay = "VERIFYFAILED";
                sendMessage(replay,ep);
            }
        }
        else
        {
            replay = "HASLOGINED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "REGISTEACCOUNT")
    {
        if(m_AudienceController->registeAudience(j["name"],j["password"]) == true)
        {
            replay = "REGISTESUCCEED";
            sendMessage(replay,ep);
        }
        else
        {
            replay = "REGISTEFAILED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "LOGOUT")
    {
        if(m_AudienceController->logoutAudience(j["name"]) == true)
        {
            replay = "LOGOUTSUCCEED";
            sendMessage(replay,ep);
        }
        else
        {
            replay = "LOGOUTFAILED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "UPDATEAVATAR")
    {
        if(m_AudienceController->updateAudienceAvatar(j["audience"],j["avatar"]) == true){
            replay = "HASCHANGED";
            sendMessage(replay,ep);
        }
        else
        {
            replay = "FAILED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "GETAUDIENCEINFO")
    {
        replay = m_AudienceController->audienceInfo(j["name"]);
        sendMessage(replay,ep);
    }
    else if(request == "GETCOLLECTION")
    {
        std::vector<std::string> collectlist;
        m_AudienceController->audienceCollection(j["name"],collectlist);
        replay = m_AudienceController->pakageCollection(collectlist);
        sendMessage(replay,ep);
    }
    else if(request == "GETRECORD")
    {
        std::vector<std::string> recordlist;
        m_AudienceController->audienceRecord(j["name"],recordlist);
        replay = m_AudienceController->pakageRecord(recordlist);
        sendMessage(replay,ep);
    }
    else if(request == "ADDCOLLECTION")
    {
        if(m_AudienceController->addAudienceCollection(j["audiencename"],j["collectname"],
                                                       j["collecttime"],j["collecttype"]) == true)
        {
            replay = "COLLECTSUCCEED";
            sendMessage(replay,ep);
        }else{
            replay = "COLLECTFAILED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "UPDATERECORD")
    {
        if(m_AudienceController->updateAudienceRecord(j["audiencename"],j["recordname"],
                                                      j["startPlayTime"],j["duration"],
                                                      j["type"]) == true)
        {
            replay = "SUCCEED";
            sendMessage(replay,ep);
        }else{
            replay = "FAILED";
            sendMessage(replay,ep);
        }
    }
    else if(request == "TYPEINTERFACE")
    {
        replay = m_BrowseAndWatchController->showTypeInterface(j["interface"],j["type"]);
        sendMessage(replay,ep);
    }

}

void Server::sendMessage(std::string message, endpoint ep)
{
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
