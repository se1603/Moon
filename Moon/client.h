#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include "json.hpp"
#include "audience.h"
#include <QObject>
#include <string>
#include <QString>
#include <fstream>
#include <ostream>

using json = nlohmann::json;

struct File_info{
    typedef unsigned long long Size_type;
    size_t filename_size;  //文件名的长度
    Size_type filesize;    //文件的大小
    File_info() : filename_size(0), filesize(0){}
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *p = nullptr);

    void connectServer();
    void splictString(std::string &s, std::vector<std::string> &v, const std::string &c);
    socket_ptr sendMessage(std::string);

    //界面显示
    Q_INVOKABLE QString showCategory(QString interface);  //显示分类
    Q_INVOKABLE QString showRecommend(QString interface);  //显示各个页面的推荐影视
    Q_INVOKABLE QString showType(QString interface,QString type);  //显示各个类型的影视


    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

    //用户操作
    //登录
    Q_INVOKABLE void sendLoginInfo(QString n,QString p);
    //注册
    Q_INVOKABLE void sendRegisterInfo(QString n,QString p);
    //退出
    Q_INVOKABLE void loginOut(QString n);
    //修改头像
    Q_INVOKABLE void updateAvatar(QString n, QString a);
    //获取用户信息
    void getAudienceInfo(std::string name);
    //获取用户收藏
    Q_INVOKABLE QString audienceCollection(QString name);
    //获取用户记录
    Q_INVOKABLE QString audienceRecord(QString name);
    //添加用户收藏
    Q_INVOKABLE void addCollection(QString name, QString collecttime, QString videoname, QString type);
    //添加用户记录
    Q_INVOKABLE void addRecord(QString name, QString recordname, QString startPlaytime,
                               QString duration, QString type);
    //本地历史记录
    //初始化
    void initBrowseRecord();
    //保存在本地文件
    void addRecordToFile(std::string recordName, std::string startTime, std::string duration, std::string post);
    //添加
    Q_INVOKABLE void addBrowseRecord(QString recordName, QString startTime, QString duration,
                                     QString post);
    //读取
    Q_INVOKABLE QString browseRecord();

    Q_INVOKABLE QString showInfomation(QString name);//显示影视信息
    Q_INVOKABLE QString getActorInfo(QString name);//显示演员信息
    //获取评论信息
    Q_INVOKABLE QString showCommentInfo(QString name);
    //获取精华评论
    Q_INVOKABLE QString showGoodComment(QString name);
    //添加评论
    Q_INVOKABLE void addComment(QString aName, QString videoname, QString t, QString c);

signals:
    //用户信号
    void loginsucceed(QString name,QString avatar);
    void loginfailed();
    void registesucceed();
    void registefailed();
    void loginout();
    void haslogined();
    void updateAvatarFailed();
    void updateAvatarSucceed(QString newsource);
    void collectsucceed();
    void collectfailed();
    void recordupdatesucceed();
    void recordupdatefailed();
    //评论信号
    void insertSuccessed();
    void insertFailed();
private:
    //文件
    FILE *fp;
    File_info file_info;
    std::map<std::string,std::string> categoryBuffer;
    std::map<std::string,std::string> recommendInterfaceBuffer;
    std::map<std::string,std::map<std::string,std::string>> typeInterfaceBuffer;

    //用户标识
    Audience* _audience;
    //本地历史记录缓存
    std::string browseRecordBuffer;
};

#endif // Client_H
