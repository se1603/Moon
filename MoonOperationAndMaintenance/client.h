#ifndef CLIET_H
#define CLIET_H

#include <QObject>
#include "network.h"
#include "json.hpp"
#include "manager.h"
#include "mysql/mysql.h"

using json = nlohmann::json;

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
signals:
    void loginSucceed(QString identity);
    void loginFailed();
    void hasLogined();
    void addAdvertSucceed();
    void addAdvertFailed();
    void deleteAdvertSucceed();
    void deleteAdvertFailed();
private:
    Manager *m_manager;
};

#endif // CLIET_H
