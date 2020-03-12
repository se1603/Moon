#ifndef DRAMA_H
#define DRAMA_H

#include "movieandtelevision.h"

enum class DramaType
{
    Recommend = 0,
    AncientCostume = 1,   //古装
    Suspense = 2,     //悬疑
    MartialArts = 3,     //武侠
    Metropolis = 4,     //都市
    History = 5,     //历史
    Idol = 6,       //偶像
    Family = 7,       //家庭
    ScienceFiction = 8      //科幻
};

class Drama : public MovieAndTelevision
{
public:
    Drama(std::string name,std::string introduction,
          Region region,std::vector<std::string> posts,
          std::vector<Actor *> actors,
          std::vector<Director *> directors,
          std::vector<DramaType> types,int episode,std::vector<int> recommends);
    Drama(){}
    std::vector<std::string> show(bool recommend);
    void findDramaByType(DramaType type, std::vector<Drama> &Dramas);
    void findDramaByRecommend(int recommend, std::vector<Drama> &Dramas);
    bool findByName(std::string name);

    void recodeInfo(std::string name,std::vector<std::string> &v);

    void getActorInfo(std::string name,std::vector<std::string> &v);
    void save(std::map<std::string,Drama> &Dramas);

    void showPost(std::string &post);
private:
    std::vector<DramaType> m_type;
};

#endif // DRAMA_H
