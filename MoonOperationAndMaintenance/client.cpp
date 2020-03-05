#include "client.h"
#include <iostream>

boost::asio::io_service service;
boost::asio::ip::udp::endpoint serverep(boost::asio::ip::address::from_string("192.168.43.76"),8001);
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
