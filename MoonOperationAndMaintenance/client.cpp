#include "client.h"
#include <iostream>
#include <fstream>
#include <sys/io.h>
#include <dirent.h>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.1.13"),8001);
boost::asio::ip::udp::socket udpsock(service,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),7788));

Client::Client(QObject *p) :
    QObject(p)
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

void Client::splictString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

QString Client::showVideoCategory()
{
    json categorys;
    categorys["system"] = "MANAGE";
    categorys["request"] = "VIDEOCATEGORYS";
    std::string message = categorys.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    std::string result = replay["categorys"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

QString Client::showDetailCategory(QString category)
{
    json detailcategorys;
    detailcategorys["system"] = "MANAGE";
    detailcategorys["request"] = "VIDEODETAILCATEGORYS";
    detailcategorys["category"] = category.toStdString();
    std::string message = detailcategorys.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();
    json replay = json::parse(res);
    replay["detailcategorys"].erase(replay["detailcategorys"].begin());
    std::string result = replay["detailcategorys"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

QString Client::showVideos(QString category, QString detailtype)
{
    json videos;
    videos["system"] = "MANAGE";
    videos["request"] = "VIDEODETAILS";
    videos["category"] = category.toStdString();
    videos["detailtype"] = detailtype.toStdString();
    std::string message = videos.dump();
    //    std::cout << category.toStdString() << detailtype.toStdString() << std::endl;

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    std::string result = replay["movieAndTelevision"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

void Client::addAdvertToVideos(QString advert, QString company, QString duetime,
                                QString videomessage, QString videotype)
{
//    std::vector<std::string> videos;
//    splictString(videomessage.toStdString(),videos,"/");
//    std::cout << advert.toStdString() << company.toStdString() << duetime.toStdString()
//              << std::endl;
//    for(auto i=videos.begin();i!=videos.end();i++){
//        std::cout << *i << std::endl;
//    }

        json advertLinkvideo;
        advertLinkvideo["system"] = "MANAGE";
        advertLinkvideo["request"] = "ADDADVERT";
        advertLinkvideo["advert"] = advert.toStdString();
        advertLinkvideo["company"] = company.toStdString();
        advertLinkvideo["duetime"] = duetime.toStdString();
        advertLinkvideo["videos"] = videomessage.toStdString();
        advertLinkvideo["videotype"] = videotype.toStdString();
        std::string message = advertLinkvideo.dump();

        socket_ptr udpsockptr;
        udpsockptr = sendMessage(message);
        NetWork sock(udpsockptr);
        std::string res = sock.receive();

        json replay = json::parse(res);
        if(replay["replay"] == "SUCCEED"){
            emit addAdvertSucceed();
        }else if(replay["replay"] == "FAILED"){
            emit addAdvertFailed();
        }
}

QString Client::searchVideos(QString name)
{
    json search;
    search["system"] = "MANAGE";
    search["request"] = "SEARCHVIDEO";
    search["name"] = name.toStdString();
    std::string message = search.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    std::string result = replay["searchmessage"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

QString Client::showVideoAdverts(QString name, QString videotype)
{
    json advert;
    advert["system"] = "MANAGE";
    advert["request"] = "SHOWADVERTS";
    advert["videoname"] = name.toStdString();
    advert["videotype"] = videotype.toStdString();
    std::string message = advert.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    std::string result = replay["adverts"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

QString Client::showCompanyClicksRank(QString companyname)
{
    json company;
    company["system"] = "MANAGE";
    company["request"] = "SHOWCLICKSRANK";
    company["companyname"] = companyname.toStdString();
    std::string message = company.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    std::string result = replay["adverts"].dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

void Client::deleteVideoAdverts(QString videoname, QString advertname)
{
    json value;
    value["system"] = "MANAGE";
    value["request"] = "DELETEVIDEOADVERTS";
    value["videoname"] = videoname.toStdString();
    value["advertname"] = advertname.toStdString();
    std::string message = value.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    if(replay["replay"] == "SUCCEED"){
        emit deleteAdvertSucceed();
    }else if(replay["replay"] == "FAILED"){
        emit deleteAdvertFailed();
    }
}

void Client::getMovieInfo(QString name,QString message,QString pAdress,QString sAdress)
{
    makeFile();
    std::cout << "name" << message.toStdString() << std::endl;
    writeFile(name.toStdString(),message.toStdString());

    std::string adress = sAdress.toStdString();
    adress = adress.erase(0,7);
    std::string command = "cp -r "+pAdress.toStdString()+" "+adress;
    std::cout << command << std::endl;
    system(command.c_str());
}

QString Client::getLocalMessages()
{
    std::string path = "./上架/";
    if(opendir(path.data()) == NULL){
        emit filmEmpty();
    }else{
        std::vector<std::string> files;
        files = getFiles(path);
        if(files.empty()){
             emit filmEmpty();
        }else{

            json up;
        //    up["system"] = "MANAGE";
        //    up["request"] = "UP";
            json resources;

            for(int i = 0; i != files.size();i++)
            {

                //读消息
                std::cout << "读消息： " << std::endl;
                std::string fileName = path + "/" + files[i];
                std::cout << fileName << std::endl;
                std::ifstream infile(fileName.data());
                std::string mes;
                std::vector<std::string> messages; //存聊天记录的消息
                while(infile >> mes)
                {
                    std::string tmp = mes;
                    std::cout << mes << std::endl;
                    messages.push_back(tmp);
                }

                std::cout << "the star" << std::endl;
                for(int i = 0; i != messages.size();i+=11)
                {
                    json value;
                    value["bigType"] = messages[i];
                    value["name"] = messages[i+1];
                    value["type"] = messages[i+2];
                    value["region"] = messages[i+3];
                    value["episode"] = messages[i+4];
                    value["director"] = messages[i+5];
                    value["actor"] = messages[i+6];
                    value["introduction"] = messages[i+7];
                    value["recommmd"] = messages[i+8];
        //            std::string m = messages[i+9];
        //            std::string s = messages[i+10];
        //            m = m.erase(0,17);
        //            s = s.erase(0,45);
        //            std::string v = "."+s+m;
                    value["image"] = messages[i+9];
                    resources.push_back(value);
                    std:: cout << messages[i+9] << std::endl;

                }
                std::cout << "the end" << std::endl;
            }
            up["resources"] = resources;
            std::string message = up.dump();
            QString qmlValues = QString::fromStdString(message);
        //    qDebug() << qmlValue;
            return qmlValues;
        }
    }
}

void Client::upServer()
{
    json up;
    std::string path = "./上架";
    if(opendir(path.data()) == NULL){
        emit filmEmpty();
    }else{
        std::vector<std::string> files;
        files = getFiles(path);
        if(files.empty()){
            emit filmEmpty();
        }else{
             readFile(files);
        }
    }
//        return;

//    std::string path = "./上架/";
//    std::vector<std::string> files;
//    files = getFiles(path);
//    if(files.empty())
//        return;
}

void Client::deleteMovie(QString name,QString type)
{
//    std::vector<std::string> videos;
//    splictString(name.toStdString(),videos,"/");
//    std::string e = type.toStdString();
//    std::string s = recommendInterfaceBuffer[e];
//    json k = json::parse(s);
//    json value = k["resource"]["films"];
//    int index;
//    for(int v = 0;v < videos.size();v++){
//        for(int i = 0;i < value.size();i++){
//            if(value[i]["name"] == videos[v]){
//                std::cout<< i <<" "<< value.size() << std::endl;
//                index  = i;
//                break;
//            }
//        }
//        auto num = value.size();
//        std::cout << num << std::endl;
//        for(int i = index;i < num;i++){
//            value[i] = value[i+1];
//        }
//    }

//    k["resource"]["films"] = value;
//    recommendInterfaceBuffer[e] = k.dump();

    json delect;
    delect["system"] = "MANAGE";
    delect["request"] = "DELECT";
    delect["name"] = name.toStdString();
    delect["type"] = type.toStdString();
    std::string message = delect.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    json qmlValue;

    std::string result = replay["delect"];

    if(result == "DELECTSUCCEED")
    {

        emit delectSucceed();
    }
    else if(result == "DELECTFAILED")
    {
        emit delectFailed();
    }
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
            root["system"] = "CLIENT";
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

void Client::receiveFilename(boost::system::error_code &e, boost::asio::ip::udp::endpoint sender_ep, socket_ptr udpsock)
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

void Client::receive_file_content()
{
    std::cout << "=====Receive File Context=====" << std::endl;
    socket_ptr udpsock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    NetWork sock(udpsock);

    sock.receiveFile(fp);
}

void Client::sendFile(std::string filename, endpoint ep)
{

    socket_ptr sock(new boost::asio::ip::udp::socket(service,boost::asio::ip::udp::endpoint()));
    boost::asio::ip::udp::endpoint sender_ep;

    std::string path = "./";
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

void Client::writeFile(std::string name, std::string message)
{
    std::string command = "./上架/";

    std::string fileName;
    fileName = command+name;

    std::cout << fileName << std::endl;

    std::ifstream file;
    file.open(fileName.data(),std::ios::in);
    if(file)
    {
        std::cout << "文件存在" << std::endl;
        file.close();
        std::ofstream write(fileName,std::ios::app);
        std::string s;
        s += message + "\n";
        write << s << std::endl;
        std::cout << s << std::endl;
        write.close();
    }
    else {
        std::cout<< "文件bu存在" << std::endl;
        std::ofstream write(fileName.data(),std::ios::app);
        std::string s;
        s += message;
        write << s << std::endl;
        std::cout << s << std::endl;
        write.close();

    }
}

std::vector<std::string> Client::getFiles(std::string path)
{
    std::vector<std::string> files;

    //检查path是否是有效的目录
    struct stat s;
    lstat(path.data() , &s );
    if( ! S_ISDIR( s.st_mode ) )
    {
        std::cout <<"dir_name is not a valid directory !"<< std::endl;
        //        return;
    }

    struct dirent * filename;    // return value for readdir()
    DIR * dir;                   // return value for opendir()
    dir = opendir(path.data());
    if( NULL == dir )
    {
        std::cout<<"Can not open dir "<< path << std::endl;
        //        return;
    }else{
         std::cout <<"Successfully opened the dir !" << std::endl;
    }

    /* read all the files in the dir ~ */ //读取该目录下所有的文件名
    while( ( filename = readdir(dir) ) != NULL )
    {
        if( strcmp( filename->d_name , "." ) == 0 ||
                strcmp( filename->d_name , "..") == 0    ) //跳过. 和..文件夹
            continue;
        std::string name(filename ->d_name);
        std::cout << name << std::endl;
        files.push_back(name); //存入所有文件名
    }
    return files;
}

void Client::readFile(std::vector<std::string> files)
{
    std::string path = "./上架/";
//    std::vector<std::string> files;
//    files = getFiles(path);
//    if(files.empty())
//        return;


    json up;
    up["system"] = "MANAGE";
    up["request"] = "UP";
    json resources;

    for(int i = 0; i != files.size();i++)
    {

        //读消息
        std::cout << "读消息： " << std::endl;
        std::string fileName = path + "/" + files[i];
        std::cout << fileName << std::endl;
        std::ifstream infile(fileName.data());
        std::string mes;
        std::vector<std::string> messages; //存聊天记录的消息
        while(infile >> mes)
        {
            std::string tmp = mes;
            std::cout << mes << std::endl;
            messages.push_back(tmp);
        }

        std::cout << "the star" << std::endl;
        for(int i = 0; i != messages.size();i+=11)
        {
            json value;
            value["bigType"] = messages[i];
            value["name"] = messages[i+1];
            value["type"] = messages[i+2];
            value["region"] = messages[i+3];
            value["episode"] = messages[i+4];
            value["director"] = messages[i+5];
            value["actor"] = messages[i+6];
            value["introduction"] = messages[i+7];
            value["recommmd"] = messages[i+8];
            std::string m = messages[i+9];
            std::string s = messages[i+10];
            m = m.erase(0,17);
            s = s.erase(0,45);
            std::string v = "."+s+m;
            value["image"] = v;
            resources.push_back(value);
            std:: cout << messages[i] << v << std::endl;

        }
        std::cout << "the end" << std::endl;
    }
    up["resource"] = resources;
    std::string message = up.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    boost::asio::ip::udp::endpoint sender_ep;
    std::string res = sock.receive(sender_ep);

    json replay = json::parse(res);
    json qmlValue;

    std::string result = replay["update"];


    if(result == "UPSUCCEED")
    {
                std::string commend1 ="cp -r ../MoonOperationAndMaintenance/image ./";
                system(commend1.c_str());
        std::string commend = " tar zcvf image.tar.gz image";
        system(commend.c_str());
//        tar zcvf FileName.tar.gz DirName
        std::string fileName = "image.tar.gz";
        sendFile(fileName,sender_ep);
        emit upSucceed();
    }
    else if(result == "UPFAILED")
    {
        emit upFailed();
    }

}

void Client::makeFile()
{
    std::string path = "./上架";
    if(opendir(path.data()) != NULL)
        return;
    std::string name = "上架";
    std::string command = "mkdir " + name;
    system(command.c_str());
    std::cout << "创建文件夹成功" << std::endl;
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
        request["system"] = "MANAGE";
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
//    if(recommendInterfaceBuffer.find(interface.toStdString()) !=
//            recommendInterfaceBuffer.end())
//    {
//        result = recommendInterfaceBuffer[interface.toStdString()];
//    }
//    else
//    {
        json request;
        request["system"] = "MANAGE";
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
//        qmlValue["firstRecommends"] = replay["firstRecommends"];
//        qmlValue["secondRecommends"] = replay["secondRecommends"];

        result = qmlValue.dump();

//        recommendInterfaceBuffer[interface.toStdString()] = result;
//    }

    QString qmlValues = QString::fromStdString(result);
//    qDebug() << qmlValue;
    return qmlValues;
}
