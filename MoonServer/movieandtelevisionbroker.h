#ifndef MOVIEANDTELEVISIONBROKER_H
#define MOVIEANDTELEVISIONBROKER_H

#include "relationalbroker.h"
#include "film.h"
#include "variety.h"
#include "comic.h"
#include "drama.h"
#include "actorbroker.h"
#include "directorbroker.h"

class MovieAndTelevisionBroker : public RelationalBroker
{
public:
    static MovieAndTelevisionBroker* getInstance()
    {
        return m_instance;
    }
    ~MovieAndTelevisionBroker();

    std::vector<std::string> InterfaceCategory(std::string interface);  //分类目录
    std::vector<std::string> interfaceRecommendCategory(std::string interface);//分类推荐目录
    void splictString(const std::string& s, std::vector<std::string>& v, const std::string& c);

    //目录
    std::vector<std::string> mainCategory();

    //电影
    void initFilms();    //获取所有电影
    Film handleFilm(std::vector<std::string> row);   //处理数据库数据
    std::vector<Film> getFilms(FilmType type);
    std::vector<Film> getRecommendFilms(int type);
    //剧集
    void initDrama();
    Drama handleDrama(std::vector<std::string> row);

    std::vector<Drama> getDramas(DramaType type);
    std::vector<Drama> getRecommendDramas(int type);

    //综艺
    void initVarieties();
    Variety handleVariety(std::vector<std::string> row);

    std::vector<Variety> getVarieties(VarietyType type);
    std::vector<Variety> getRecommendVarieties(int type);

    //动漫
    void initComics();//获取所有动漫
    Comic handleComic(std::vector<std::string> row); //处理数据库数据

    std::vector<Comic> getComics(ComicType type);
    std::vector<Comic> getRecommendComics(int type);

    //用户操作
    //处理用户信息
    void processAudienceCollection(std::vector<std::string> tmp,MovieAndTelevision *m);
    void processAudienceRecord(std::vector<std::string> tmp,MovieAndTelevision *m);
    //获取用户具体信息
    void showCollection(MovieAndTelevision* m, std::vector<std::string> &collections);
    void showRecord(MovieAndTelevision* m, std::vector<std::string> &records);

    std::vector<std::string> getVideoInfo(std::string name);//获取影视内容
    std::vector<std::string> getActorInfo(std::string name);//获去演员内容
    void findMovieandTelevision(std::string name, MovieAndTelevision *m);//获取影视指针

    //广告管理员
    //目录
    std::map<std::string,std::string> getVideos(std::string category, std::string type);
    //搜索
    std::map<std::string, std::string> searchVideos(std::string name);
    //插入广告
    MovieAndTelevision *addAdvert(std::string video, Advert *a, std::string videotype);
    //获取广告信息
    std::vector<Advert*> showAdverts(std::string name, std::string type);
    //插入广告链接
    MovieAndTelevision *initAdvertLinks(std::string videoname, Advert* a);
    //删除广告链接
    bool deleteVideoAdverts(std::string videoname, std::string advertname);

    bool initMovieandTelevision(std::string s);//添加影视信息到数据库
    bool delect(std::string name,std::string type);//下架影视
    std::vector<std::string> dealType(std::string type);//处理影视类型
    Region dealRegion(std::string& region);//处理影视地域
    std::vector<Actor *> dealActor(std::string actor);//处理演员
    std::vector<Director *> dealDirector(std::string director);//处理导演
    std::vector<std::string> dealPost(std::string image);//处理海报
    std::vector<int> dealRecommends(std::string recommend);
//    template<typename T> std::string dealTypes(std::string type, std::vector<T>& y);



private:
    MovieAndTelevisionBroker();
    static MovieAndTelevisionBroker *m_instance;

    ActorBroker *m_actorBroker;
    DirectorBroker *m_directorBroker;

    std::map<std::string,std::vector<std::string>> m_categorys; //分类目录
    std::map<std::string,std::vector<std::string>> m_recommendCatergory; //推荐目录

    std::map<std::string,Film> m_films;   //电影
    std::map<std::string,Drama> m_dramas;  //剧集
    std::map<std::string,Variety> m_varieties; //综艺
    std::map<std::string,Comic> m_comics;  //动漫
};
//template<typename T>
//std::string MovieAndTelevisionBroker::dealTypes(std::string type, std::vector<T> &y)
//{
//    if(type == "机战"||type =="古装"||type =="武侠"||type =="真人秀"){
//        if(type == "机战"){
//            y.push_back(ComicType::RobotWars);
//        }else if(type == "古装"){
//            y.push_back(DramaType::AncientCostume);
//        }else if(type =="武侠"){
//          y.push_back(FilmType::MartialArts);
//        }else if(type =="真人秀"){
//          y.push_back(VarietyType::RealityShow);
//        }
//        return "1";
//    }else if(type == "青春"||type =="悬疑"||type =="悬疑"||type =="选秀"){
//        if(type == "青春"){
//            y.push_back(ComicType::Youth);
//        }else if(type == "悬疑"){
//            y.push_back(DramaType::Suspense);
//        }else if(type =="悬疑"){
//          y.push_back(FilmType::Suspense);
//        }else if(type =="选秀"){
//          y.push_back(VarietyType::TalentShow);
//        }
//        return "2";
//    }else if(type == "格斗"||type =="武侠"||type =="喜剧"||type =="美食"){

//        return "3";
//    }else if(type == "恋爱"||type =="都市"||type =="动作"||type =="旅游"){
//        return "4";
//    }else if(type == "美少女"||type =="历史"||type =="爱情"||type =="纪实"){
//        return "5";
//    }else if(type == "热血"||type =="偶像"||type =="动画"||type =="搞笑"){
//        return "6";
//    }else if(type == "校园"||type =="家庭"||type =="惊悚"||type =="访谈"){
//        return "7";
//    }else if (type == "科幻"||type =="科幻") {
//        return "8";
//    }
//}

#endif // MOVIEANDTELEVISIONBROKER_H
