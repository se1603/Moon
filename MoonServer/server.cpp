#include "server.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint udpep(boost::asio::ip::udp::v4(),8001);

Server::Server()
{
    m_controllerFactory = ControllerFactory::getInstance();
    m_BrowseAndWatchController = m_controllerFactory->createBrowseAndWatchController();
    m_AudienceController = m_controllerFactory->createAudienceController();
    m_commentController = m_controllerFactory->createCommentController();
    m_managerController = m_controllerFactory->createManagerController();
    m_searchController = m_controllerFactory->createSearchController();
    m_manageusercontroller = m_controllerFactory->createManageUserController();
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
    std::string system = j["system"];
    if(system == "MANAGE")
    {
        processOMRequest(j,ep);
    }
    else
    {
        processClientRequest(j,ep);
    }
}

void Server::processClientRequest(json j,endpoint ep)
{
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
    else if(request == "INFOMATION")
    {
        replay = m_BrowseAndWatchController->getMovieInfomation(j["name"]);
        sendMessage(replay,ep);
    }
    else if(request == "ACTORINFOMATION")
    {
        replay = m_BrowseAndWatchController->getActorInfomation(j["name"]);
        sendMessage(replay,ep);
    } else if(request == "SHOWCOMMENT"){
        replay = m_commentController->getCommentInfo(j["name"]);
        sendMessage(replay,ep);
    }
    else if(request == "SHOWGOODCOMMENT"){
        replay = m_commentController->goodCommentInfo(j["name"]);
        sendMessage(replay,ep);
        //        return reply;
    }
    else if(request == "INSERTCOMMENT"){
        if((m_commentController->insertComment(j["audiencename"],j["name"],j["time"],
                                               j["comment"]))==true){
            replay = "SUCESSED!";
            sendMessage(replay,ep);
        }else{
            replay = "FAILED";
            sendMessage(replay,ep);
        }

    }
    else if(request == "ADVERTADDRESS")
    {
        replay = m_BrowseAndWatchController->getAdvertInformation(j["name"]);
        std::cout << replay << std::endl;
        sendMessage(replay,ep);
    }
    else if(request == "SEARCH")
    {
        replay = m_searchController->searchKeywords(j["name"]);
        sendMessage(replay,ep);
    }
    else if(request == "ADVERTCLICKS")
    {
        replay = m_managerController->addAdvertClicks(j["advertname"]);
        sendMessage(replay,ep);
    }
}

void Server::processOMRequest(json j, endpoint ep)
{
    std::string request = j["request"];
    std::string replay;

    if(request == "LOGIN")
    {
        replay = m_managerController->login(j["number"],j["password"]);
        sendMessage(replay,ep);
    }
    if(request == "VIDEOCATEGORYS")
    {
        replay = m_managerController->showCategory();
        sendMessage(replay,ep);
    }
    if(request == "VIDEODETAILCATEGORYS")
    {
        replay = m_managerController->showCategoryType(j["category"]);
        sendMessage(replay,ep);
    }
    if(request == "VIDEODETAILS")
    {
        replay = m_BrowseAndWatchController->showTypeInterface(j["category"],
                j["detailtype"]);
        sendMessage(replay,ep);
    }
    if(request == "ADDADVERT")
    {
        replay = m_managerController->addAdvert(j["advert"],j["company"],
                j["duetime"], j["videos"],j["videotype"],j["detailtype"]);
//        receiveFile(replay,ep);
        sendMessage(replay,ep);
    }
    if(request == "ADDADVERTTOCATEGORY")
    {
        replay = m_managerController->addAdvertToCategory(j["advert"], j["company"],
                j["duetime"], j["category"]);
//        receiveFile(replay,ep);
        sendMessage(replay,ep);
    }
    if(request == "SEARCHVIDEO")
    {
        replay = m_managerController->searchVideo(j["name"]);
        sendMessage(replay,ep);
    }
    if(request == "SHOWADVERTS")
    {
        replay = m_managerController->showAdverts(j["videoname"], j["videotype"]);
        sendMessage(replay,ep);
    }
    if(request == "SHOWCLICKSRANK")
    {
        replay = m_managerController->showCompanyClicksRank(j["companyname"]);
        sendMessage(replay,ep);
    }
    if(request == "DELETEVIDEOADVERTS"){
        replay = m_managerController->deleteVideoAdverts(j["deletemessage"]);
        sendMessage(replay,ep);
    }else if(request == "UP"){
        std::string s = j.dump();
//        replay = m_BrowseAndWatchController->initMovies(s);
        receiveFile(s,ep);
        std::string commend = "tar xzvf ./images.tar.gz";
        system(commend.c_str());
        tarFiles();
    }else if(request =="NOTICEUP"){

        replay = m_BrowseAndWatchController->initMovies();
        receiveFile(replay,ep);
//        sendMessage(replay,ep);
    }
    else if(request == "CATEGORY"){
        replay = m_BrowseAndWatchController->InterfaceCategory1(j["interface"]);
        sendMessage(replay,ep);

    }else if(request =="RECOMMENDINTERFACE"){
        replay = m_BrowseAndWatchController->delayTV(j["interface"]);
        sendMessage(replay,ep);
    }else if(request == "DELECT")
    {
        replay = m_BrowseAndWatchController->deleteTv(j["name"],j["type"]);
        sendMessage(replay,ep);
    }else if(request == "SEACH"){
        replay = m_managerController->seach(j["name"]);
        sendMessage(replay,ep);
    }else if(request == "UPDATE"){
        std::string s = j["resource"].dump();
        replay = m_managerController->update(s);
        sendMessage(replay,ep);
    }else if(request == "SHOWALLVIDEOADVERTS"){
        replay = m_managerController->showAllVideoAdverts();
        sendMessage(replay,ep);
    }else if(request == "SHOWADVERTISING"){
        replay = m_managerController->showAdvertising();
        sendMessage(replay,ep);
    }else if(request == "CHANGEADVERTTIME"){
        replay = m_managerController->changeAdvertTime(j["advertname"],j["newdate"]);
        sendMessage(replay,ep);
    }else if(request == "CHANGEADVERTLOCATION"){
        replay = m_managerController->changeAdvertLocation(j["advertname"], j["videoname"],
                                                            j["newlocation"]);
        sendMessage(replay,ep);
    }
    //获取传来的用户管理信息
    if(request == "GETMANAGEUSERINFO"){
        replay = m_manageusercontroller->getManageUserInfo(j["informmark"]);
        sendMessage(replay, ep);
    }
    //通过ID获取用户管理信息
    if(request == "GETMANAGEUSERINFOBYID"){
        replay = m_manageusercontroller->getManageUserInfoByID(j["id"]);
        sendMessage(replay, ep);
    }
    //删除被举报的信息
    if(request == "DELETEINFORMEDCOMMENT"){
        replay = m_manageusercontroller->deleteInformComment(j["bereported"], j["comment"]);
        sendMessage(replay, ep);
    }
    //修改已删除平路记录的标记为processed
    if(request == "UPDATEINFORMMARK"){
        replay = m_manageusercontroller->updateInformmark(j["id"]);
        sendMessage(replay, ep);
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
void Server::receiveFile(std::string message,endpoint clientep)
{
    std::cout << "Send message:"  << message << std::endl;
    //创建一个新的套接字。
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    NetWork sock(udpsock);

    sock.sendto(message,clientep);

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

void Server::receiveFilename(boost::system::error_code &e, boost::asio::ip::udp::endpoint sender_ep, socket_ptr udpsock)
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
}
void Server::tarFiles()
{
    std::vector<std::string> files{"films","comics","drama","varietyshow"};
//    for(auto i:files){
//        std::cout << i << std::endl;
//        std::string commend2 ="tar xzvf ../MoonServer/images/"+i+".tar.gz";
//        system(commend2.c_str());
//    }
    for(auto i:files){
//        std::string commend3 ="cp -rf ./images/"+i+" ./";
//        system(commend3.c_str());
//        std::string commend = "tar zcvf "+i+".tar.gz "+i;
//        std::cout << commend << std::endl;
//        system(commend.c_str());
        std::string commend1 ="cp -r ./images/"+i+".tar.gz ../MoonServer/images";
        system(commend1.c_str());
    }
}
