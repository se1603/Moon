#ifndef CLIET_H
#define CLIET_H

#include <QObject>
#include "network.h"
#include "json.hpp"
#include "manager.h"
#include "mysql/mysql.h"
#include <vector>

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

    socket_ptr sendMessage(std::string message);

    Q_INVOKABLE void sendLoginInfo(QString n,QString p);

    //字符串分割工具
    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);

    //广告运营
    //读取视频目录
    Q_INVOKABLE QString showVideoCategory();
    //读取详细目录
    Q_INVOKABLE QString showDetailCategory(QString category);
    //读取视频信息
    Q_INVOKABLE QString showVideos(QString category, QString detailtype);
    //插播广告
    Q_INVOKABLE void addAdvertToVideos(QString advert, QString company,
                                       QString duetime, QString videomessage,
                                       QString videotype);
    //搜索视频
    Q_INVOKABLE QString searchVideos(QString name);
    //读取视频广告信息
    Q_INVOKABLE QString showVideoAdverts(QString name, QString videotype);
    //获取公司广告排名
    Q_INVOKABLE QString showCompanyClicksRank(QString companyname);
    //删除广告
    Q_INVOKABLE void deleteVideoAdverts(QString videoname, QString advertname);


    Q_INVOKABLE void getMovieInfo(QString name, QString fileName, QString message, QString pAdress, QString sAdress);//获取影视信息写入本地文件
    Q_INVOKABLE QString getLocalMessages();//获取本地影视信息文件，传输到qml端

    Q_INVOKABLE void upServer();//把信息传到服务端
    Q_INVOKABLE void modifiedImage(QString imagePath,QString name);

    //下架界面显示
    Q_INVOKABLE QString showCategory(QString interface);  //显示下架影视的分类
    Q_INVOKABLE QString showRecommend(QString interface);  //显示各个页面的推荐影视
    Q_INVOKABLE void deleteMovie(QString name,QString type);//下架影视



    void writeFile(std::string filename, std::string message, std::string name);//影视编辑编辑影视信息，写入本地文件
    std::vector<std::string> getFiles(std::string path);//获取上架文件
    void readFile(std::vector<std::string> files);//读取上架文件的信息

    void makeFile();//创建文件




    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

    void sendFile(std::string filename,endpoint ep);  //发送文件


signals:
    void loginSucceed(QString identity);
    void loginFailed();
    void hasLogined();
    void addAdvertSucceed();
    void addAdvertFailed();
    void deleteAdvertSucceed();
    void deleteAdvertFailed();

    void upSucceed();
    void upFailed();
    void delectSucceed();
    void delectFailed();
    void filmEmpty();
private:
    //文件
    FILE *fp;
    File_info file_info;

    Manager *m_manager;
    std::map<std::string,std::string> categoryBuffer;
    std::map<std::string,std::string> recommendInterfaceBuffer;
};

#endif // CLIET_H
