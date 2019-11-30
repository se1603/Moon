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
