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
                                       QString videotype, QString detailtype);
    //插播整个目录
    Q_INVOKABLE void addAdvertToCategory(QString advert, QString company,
                                         QString duetime, QString category);
    //搜索视频
    Q_INVOKABLE QString searchVideos(QString name);
    //读取视频广告信息
    Q_INVOKABLE QString showVideoAdverts(QString name, QString videotype);
    //获取公司广告排名
    Q_INVOKABLE QString showCompanyClicksRank(QString companyname);
    //删除广告
    Q_INVOKABLE void deleteVideoAdverts(QString deletemessage);
    //分割时间
    Q_INVOKABLE QString cliptime(QString duetime);
    //获取所有已编辑的广告
    Q_INVOKABLE QString showAllVideoAdverts();
    //判断日期
    Q_INVOKABLE QString judgedate(QString year, QString month, QString day,
                                  QString dueyear, QString duemonth, QString dueday);
    //获取所有已投放的映前广告
    Q_INVOKABLE QString showAdvertising();
    //修改广告到期时间
    Q_INVOKABLE void changeAdvertTime(QString advertname, QString newdate);
    //修改广告投放位置
    Q_INVOKABLE void changeAdvertLocation(QString advertname, QString videoname,
                                             QString newlocation);


     Q_INVOKABLE void getMovieInfo(QString name, QString fileName, QString message, QString pAdress, QString sAdress);//获取影视信息写入本地文件
    Q_INVOKABLE QString getLocalMessages();//获取本地影视信息文件，传输到qml端

    Q_INVOKABLE void upServer();//把文件传到服务端
    Q_INVOKABLE void noticeUp();//通知服务器处理影视信息
    Q_INVOKABLE void modifiedImage(QString imagePath,QString name);//修改影视内容

    //下架界面显示
    Q_INVOKABLE QString showCategory(QString interface);  //显示下架影视的分类
    Q_INVOKABLE QString showRecommend(QString interface);  //显示各个页面的影视
    Q_INVOKABLE void deleteMovie(QString name,QString type);//下架影视
    Q_INVOKABLE void updateVideos(QString str);

    //搜索视频
    Q_INVOKABLE QString search(QString name);


    //通过标签从服务器上获取管理用户相关信息
    Q_INVOKABLE QString getManageUserInfoByMark(QString informmark);
    //通过ID获取对应记录
    Q_INVOKABLE QString getManageUserInfoByID(QString id);
    //删除被举报的评论
    Q_INVOKABLE void deleteInformedComment(QString bereported, QString comment);
    Q_INVOKABLE void updateInformmark(QString id); //更新记录标记为已处理

   void writeFile(std::string filename, std::string message, std::string name);//影视编辑编辑影视信息，写入本地文件
    std::vector<std::string> getFiles(std::string path);//获取上架文件
    void readFile(std::vector<std::string> files);//读取上架文件的信息

    void makeFile();//创建文件

    void tarFiles();



    //获取文件
    void getFile();
    void receiveFile(std::string message);
    void receiveFilename(boost::system::error_code &e,boost::asio::ip::udp::endpoint sender_ep,socket_ptr udpsock);
    void receive_file_content();

    void sendFile(std::string filename,endpoint ep,bool flag);  //发送文件
    void sendFile1(std::string filename,endpoint ep);  //发送文件


signals:
    void loginSucceed(QString identity);
    void loginFailed();
    void hasLogined();
    void addAdvertSucceed();
    void addAdvertFailed();
    void deleteAdvertSucceed();
    void deleteAdvertFailed();
    void changeAdvertTimeSucceed();
    void changeAdvertTimeFailed();
    void changeAdvertLocationSucceed();
    void changeAdvertLocationFailed();
    void changeAdvertLocationNotFound();

    void upSucceed();
    void upFailed();
    void delectSucceed();
    void delectFailed();
    void filmEmpty();

    void updateSucceed();
    void updateFalied();
    void seachEmpty();
    //用户管理信号
    void deleteInformeCommentSucceed();
    void deleteInformeCommentFailed();
    void updateInformmarkSucceed();
    void updateInformmarkFailed();
private:
    //文件
    FILE *fp;
    File_info file_info;

    Manager *m_manager;
    std::map<std::string,std::string> categoryBuffer;
    std::map<std::string,std::string> recommendInterfaceBuffer;
};

#endif // CLIET_H
