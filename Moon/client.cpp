#include "client.h"
#include <iostream>
#include <qdebug.h>
#include <dirent.h>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.43.76"),8001);
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

void Client::splictString(std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1,pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2){
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
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
    qDebug() << qmlValue;
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

        categoryBuffer[interface.toStdString()] = result;
    }

    QString qmlValue = QString::fromStdString(result);
    qDebug() << qmlValue;
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

//登录
void Client::sendLoginInfo(QString n, QString p)
{
    json login;
    login["request"] = "VERIFYINFO";
    login["name"] = n.toStdString();
    login["password"] = p.toStdString();

    std::string message = login.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    if(res == "LOGINSUCCEED"){
        getAudienceInfo(n.toStdString());
    }else if(res == "VERIFYFAILED"){
        emit loginfailed();
    }else if(res == "HASLOGINED"){
        emit haslogined();
    }
}

//注册
void Client::sendRegisterInfo(QString n, QString p)
{
    json registor;
    registor["request"] = "REGISTEACCOUNT";
    registor["name"] = n.toStdString();
    registor["password"] = p.toStdString();

    std::string message = registor.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    if(res == "REGISTESUCCEED"){
        emit registesucceed();
    }else{
        emit registefailed();
    }
}

//退出登录
void Client::loginOut(QString n)
{
    json logOUT;
    logOUT["request"] = "LOGOUT";
    logOUT["name"] = n.toStdString();

    std::string message = logOUT.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    if(res == "LOGOUTSUCCEED"){
        _audience = nullptr;
        emit loginout();
    }
}

//修改头像
void Client::updateAvatar(QString n,QString a)
{
    json avatar;
    avatar["request"] = "UPDATEAVATAR";
    avatar["audience"] = a.toStdString();
    avatar["avatar"] = n.toStdString();

    std::string message = avatar.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    if(res == "HASCHANGED"){
        emit updateAvatarSucceed(QString::fromStdString(n.toStdString()));
    }else if(res == "FAILED"){
        emit updateAvatarFailed();
    }
}

//获取用户信息
void Client::getAudienceInfo(std::string name)
{
    json AudienceInfo;
    AudienceInfo["request"] = "GETAUDIENCEINFO";
    AudienceInfo["name"] = name;

    std::string message = AudienceInfo.dump();

    socket_ptr udpsockptr;
    udpsockptr = sendMessage(message);
    NetWork sock(udpsockptr);
    std::string res = sock.receive();

    json replay = json::parse(res);
    QString n = QString::fromStdString(replay["name"]);
    QString a = QString::fromStdString(replay["avatar"]);
    emit loginsucceed(n,a);
}

//读取用户收藏
QString Client::audienceCollection(QString name)
{
    json collection;
    collection["request"] = "GETCOLLECTION";
    collection["name"] = name.toStdString();

    std::string message = collection.dump();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    json replay = json::parse(res);
    json collectionValue = replay["collections"];
    std::string result = collectionValue.dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

//读取用户历史
QString Client::audienceRecord(QString name)
{
    json record;
    record["request"] = "GETRECORD";
    record["name"] = name.toStdString();

    std::string message = record.dump();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    json replay = json::parse(res);
    json recordValue = replay["records"];
    std::string result = recordValue.dump();
    QString qmlvalue = QString::fromStdString(result);
    return qmlvalue;
}

//添加用户收藏
void Client::addCollection(QString name, QString collecttime, QString videoname, QString type)
{
    json collection;
    collection["request"] = "ADDCOLLECTION";
    collection["audiencename"] = name.toStdString();
    collection["collecttime"] = collecttime.toStdString();
    collection["collectname"] = videoname.toStdString();
    collection["collecttype"] = type.toStdString();

    std::string message = collection.dump();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    if(res == "COLLECTSUCCEED"){
        emit collectsucceed();
    }else if(res == "COLLECTFAILED"){
        emit collectfailed();
    }
}

//添加用户历史
void Client::addRecord(QString name, QString recordname, QString startPlaytime, QString duration, QString type)
{
    json record;
    record["request"] = "UPDATERECORD";
    record["audiencename"] = name.toStdString();
    record["recordname"] = recordname.toStdString();
    record["startPlayTime"] = startPlaytime.toStdString();
    record["duration"] = duration.toStdString();
    record["type"] = type.toStdString();

    std::string message = record.dump();

    socket_ptr udpsock;
    udpsock = sendMessage(message);
    NetWork sock(udpsock);
    std::string res = sock.receive();

    if(res == "SUCCEED"){
        recordupdatesucceed();
    }else{
        recordupdatefailed();
    }
}

//创建本地历史记录文件
void Client::initBrowseRecord()
{
    std::string str = "";
    json qmlvalue;
    std::ifstream inf("browseRecord.txt",std::ifstream::app);

    if (inf.is_open())
        std::cout << "browseRecord.txt is open" << std::endl;

    getline(inf,str);
    inf.close();

    if(str.size() != 0) {
        std::vector<std::string> records;
        splictString(str,records,"#");
        for(auto &r:records) {
            std::vector<std::string> tmp;
            splictString(r,tmp," ");
            json value;
            value["name"] = tmp[0];
            value["startPlayTime"] = tmp[1];
            value["duration"] = tmp[2];
            value["post"] = tmp[3];
            qmlvalue.push_back(value);
        }
        browseRecordBuffer = qmlvalue.dump();
    }else{
        browseRecordBuffer = "";
    }
}

//添加本地历史记录
void Client::addRecordToFile(std::string recordName, std::string startTime, std::string duration, std::string post)
{
    std::ofstream OpenFile("browseRecord.txt",std::ofstream::app);

    if (OpenFile.fail())
    {
        std::cout << "打开文件错误!" << std::endl;
        exit(0);
    }

    OpenFile << recordName + " " + startTime + " " + duration + " " + post + "#";
    OpenFile.close();
}

void Client::addBrowseRecord(QString recordName, QString startTime, QString duration, QString post)
{
    std::string rN = recordName.toStdString();
    std::string sT = startTime.toStdString();
    std::string d = duration.toStdString();
    std::string p = post.toStdString();

    json root;
    root["name"] = rN;
    root["startPlayTime"] = sT;
    root["duration"] = d;
    root["post"] = p;

    std::ifstream inf("browseRecord.txt",std::ifstream::app);
    std::string str;
    getline(inf,str);
    inf.close();

    json value;
    json qmlvalue;

    int flag = 0;

    if(browseRecordBuffer.size() == 0){
        qmlvalue.push_back(root);
        browseRecordBuffer = qmlvalue.dump();
        addRecordToFile(rN,sT,d,p);
    }else{
        if(!json::parse(browseRecordBuffer)){
            std::cout << "failed" << std::endl;
        }
        else
        {
            value = json::parse(browseRecordBuffer);
            std::vector<std::string> vec;
            splictString(str,vec,"#");
            for(auto item = vec.begin();item != vec.end(); item++) {
                std::vector<std::string> tmp;
                splictString(*item,tmp," ");
                if(tmp[0] == rN){
                    vec.erase(item);
                    flag = 1;
                }
                if(vec.size() == 0)
                    break;
            }
            std::string newstr = rN+" "+sT+" "+d+" "+p+"#";
            vec.push_back(newstr);

            if(flag = 0){
                    value.push_back(root);
                    browseRecordBuffer = value.dump();
                    addRecordToFile(rN,sT,d,p);
            }else{
                std::string newRecord;
                for(auto &v:vec){
                    std::cout << "??????" << v << std::endl;
                    newRecord += v;
                }
                std::ofstream OpenFile("browseRecord.txt",std::ofstream::trunc);
                OpenFile << newRecord;
                OpenFile.close();
                initBrowseRecord();
            }
        }
    }
}

QString Client::browseRecord()
{
    QString message;
    if(browseRecordBuffer.size() == 0){
        json root;
        root["name"] = " ";
        root["startPlayTime"] = " ";
        root["duration"] = " ";
        root["post"] = " ";
        std::string s = root.dump();
        message = QString::fromStdString(s);
    }else{
        message = QString::fromStdString(browseRecordBuffer);
    }
    return message;
}
