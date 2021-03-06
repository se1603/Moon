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
    MovieAndTelevision *addAdvert(std::string video, Advert *a, std::string videotype, int &flag);
    //获取广告信息
    std::vector<Advert*> showAdverts(std::string name, std::string type);
    //插入广告链接
    MovieAndTelevision *initAdvertLinks(std::string videoname, Advert* a);
    //删除广告链接
    bool deleteVideoAdverts(std::string videoname, std::string advertname);
    //获取目录影视
    std::vector<std::string> findCategory(std::string category);
    //获取细类影视
    std::vector<std::string> findTypeVideo(std::string type, std::string category);
    //获取影视指针
    MovieAndTelevision *findVideo(std::string videoname);

    bool getMTVMessage();
    std::vector<std::string> getFiles(std::string path);//获取上架文件
    bool readFile(std::vector<std::string> files);//从文件中读取影视信息
    bool initMovieandTelevision(std::string s);//添加影视信息到数据库
    bool delect(std::string name,std::string type);//下架影视
    std::vector<std::string> dealType(std::string type);//处理影视类型
    Region dealRegion(std::string& region);//处理影视地域
    std::vector<Actor *> dealActor(std::string actor);//处理演员
    std::vector<Director *> dealDirector(std::string director);//处理导演
    std::vector<std::string> dealPost(std::string image);//处理海报
    std::vector<int> dealRecommends(std::string recommend);

    std::string subString(std::string type,std::string s);
//    template<typename T> std::string dealTypes(std::string type, std::vector<T>& y);


    bool updateVideos(std::string s);//更新影视


    //搜索
    std::vector<Film *> searchFilm(std::string name); //从map中读取数据，返回给controller
    std::vector<Drama *> searchDrama(std::string name);
    std::vector<Comic *> searchComic(std::string name);

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

#endif // MOVIEANDTELEVISIONBROKER_H
