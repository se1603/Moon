#ifndef MOVIEANDTELEVISION_H
#define MOVIEANDTELEVISION_H

#include "actor.h"
#include "director.h"
#include "advert.h"
#include <map>

class Advert;
class MovieAndTelevision
{
public:
    MovieAndTelevision();

    void searchInfo(std::vector<std::string> &vec);

    //用户操作
    //判断
    bool isSame(std::string n);
    //收藏与记录
    void showInfo(std::vector<std::string> &a_collections);
    //广告
    //添加广告
    void addAdvertLink(Advert* a);
    //获取广告链接
    std::vector<Advert*> showAdvertLink();
    //删除广告链接
    bool deleteAdvertLink(std::string advertname);
protected:
    std::string m_name;             //名称
    std::string m_introduction;       //简介
    Region m_region;                   //地区
    std::vector<std::string> m_post;  //海报
    std::vector<Actor *> m_actors;      //演员
    std::vector<Director *> m_director; //导演
    int m_episode; //集数

    std::vector<int> m_recommend;     //推荐标记
    std::vector<Advert*> m_adverts;  //广告
};

#endif // MOVIEANDTELEVISION_H
