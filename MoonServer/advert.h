/* Author:董梦丹
* Date:2020-02-01
* 最后修改:03-04
* Note:广告
*/
#ifndef ADVERT_H
#define ADVERT_H
#include <iostream>
#include <vector>
#include "movieandtelevision.h"

class MovieAndTelevision;
class Advert
{
public:
    Advert(std::string name, std::string company, std::string clicks, std::string duetime);

    //查看信息
    void showDetails(std::vector<std::string> &vec);
    //判断
    bool theSame(Advert* a);
    bool theSameName(std::string name);
    //公司
    bool sameCompany(std::string companyname);
    //点击量
    int showClicks();
    //添加影视链接
    void addVideoLink(MovieAndTelevision *mv);
    //删除影视链接
    bool deleteVideoLink(std::string videoname);
    //判断影视为空
    bool isVideoEmpty();
    //修改广告到期时间
    void changetime(std::string newdate);

    //void print();
private:
    std::string m_name;
    std::string m_company;
    std::string m_clicks;
    std::string m_duetime;

    std::vector<MovieAndTelevision *> m_videos;
};

#endif // ADVERT_H
