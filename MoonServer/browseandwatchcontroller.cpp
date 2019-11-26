#include "browseandwatchcontroller.h"
#include "json.hpp"

using json = nlohmann::json;

BrowseAndWatchController* BrowseAndWatchController::m_instance = new BrowseAndWatchController;

BrowseAndWatchController::BrowseAndWatchController()
{
    m_rtspAddress = "10.253.25.97";
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
}

BrowseAndWatchController::~BrowseAndWatchController()
{
    delete m_instance;
}

std::string BrowseAndWatchController::InterfaceCategory(std::string interface)
{
    std::vector<std::string> categorys;

    categorys = m_movieAndTelevisionBroker->InterfaceCategory(interface);

    json result;
    result["request"] = "CATEGORY";
    result["interface"] = interface;
    json arry;

    for(int i = 0; i < categorys.size(); i++)
    {
        json item;
        item["category"] = categorys[i];
        arry.push_back(item);
    }
    result["categorys"] = arry;

    std::string s = result.dump();
    return s;
}

std::string BrowseAndWatchController::recommendInterface(std::string interface)
{
    std::string result;

    json value;
    value["request"] = "RECOMMENDINTERFACE";
    value["interface"] = interface;

    if(interface == "精选")
    {
        std::vector<std::string> title =
                m_movieAndTelevisionBroker->interfaceRecommendCategory(interface);
        json array;
        json common;
        std::vector<Film> films = m_movieAndTelevisionBroker->getRecommendFilms(7);
        for(int i = 0;i != films.size();i++){
            std::vector<std::string> resource;
            json film;
            resource = films[i].show(true);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            array.push_back(film);
        }

        std::vector<Drama> dramas = m_movieAndTelevisionBroker->getRecommendDramas(7);
        for(int i = 0;i != dramas.size();i++){
            std::vector<std::string> resource;
            json drama;
            resource = dramas[i].show(true);
            drama["name"] = resource[0];
            drama["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            drama["rtspURL"] = url;
            array.push_back(drama);
        }

        std::vector<Comic> comics = m_movieAndTelevisionBroker->getRecommendComics(7);
        for(int i = 0;i != comics.size();i++){
            std::vector<std::string> resource;
            json comic;
            resource = comics[i].show(true);
            comic["name"] = resource[0];
            comic["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            comic["rtspURL"] = url;
            array.push_back(comic);
        }

        std::vector<Variety> varieties = m_movieAndTelevisionBroker->getRecommendVarieties(7);
        for(int i = 0;i != varieties.size();i++){
            std::vector<std::string> resource;
            json varietie;
            resource = varieties[i].show(true);
            varietie["name"] = resource[0];
            varietie["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            varietie["rtspURL"] = url;
            array.push_back(varietie);
        }

        value["firstRecommends"] = array;  //大图`

        std::vector<Film> film1s = m_movieAndTelevisionBroker->getRecommendFilms(99);
        json arryf;
        json item;
        for(int a = 0;a != 5;a++)
        {
            std::vector<std::string> resource;
            json film;
            resource = film1s[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];

            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arryf.push_back(film); //存小图电影
            //            a++;
        }
        item["title"] = title[0];
        item["films"] = arryf;
        common["resource"].push_back(item);

        std::vector<Drama> drama1 = m_movieAndTelevisionBroker->getRecommendDramas(5);
        json arryd;
        for(int a = 0;a != 5;a++){
            std::vector<std::string> resource;
            json drama;
            resource = drama1[a].show(false);
            drama["name"] = resource[0];
            drama["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            drama["rtspURL"] = url;
            arryd.push_back(drama);
        }
        item["title"] = title[1];
        item["films"] = arryd;
        common["resource"].push_back(item);

        std::vector<Comic> comic2s = m_movieAndTelevisionBroker->getRecommendComics(99);
        json arryc;
        for(int a = 0; a != 5;a++)
        {
            std::vector<std::string> resource;
            json film;
            resource = comic2s[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arryc.push_back(film); //存小图电影
        }
        item["title"] = title[2];
        item["films"] = arryc;
        common["resource"].push_back(item);

        std::vector<Variety> vas = m_movieAndTelevisionBroker->getRecommendVarieties(99);
        json arryv;
        for(int a = 0; a != 5;a++)
        {
            std::vector<std::string> resource;
            json film;
            resource = vas[a].show(false);
            film["name"] = resource[0];
            film["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            film["rtspURL"] = url;
            arryv.push_back(film); //存小图电影
        }
        item["title"] = title[3];
        item["films"] = arryv;
        common["resource"].push_back(item);

        value["secondRecommends"] = common;

    }
    else if(interface == "电影")
    {
        std::vector<std::string> title =
                m_movieAndTelevisionBroker->interfaceRecommendCategory(interface);
        json bigPostFilms;
        json commonFilm;

        for(int i = 0; i != 6;i++)
        {
            std::vector<Film> films = m_movieAndTelevisionBroker->getRecommendFilms(i);
            json arry;
            json item;
            for(int a = 0; a != films.size();a++)
            {
                std::vector<std::string> resource;
                json film;
                if(i == 0){
                    resource = films[a].show(true);
                    film["name"] = resource[0];
                    film["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    film["rtspURL"] = url;
                    bigPostFilms.push_back(film);   //存大图电影
                }
                else{
                    resource = films[a].show(false);
                    film["name"] = resource[0];
                    film["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    film["rtspURL"] = url;
                    arry.push_back(film); //存小图电影
                }
                if(i != 0)
                {
                    item["title"] = title[i - 1];
                    item["films"] = arry;
                }
            }
            if(i != 0)
                commonFilm["resource"].push_back(item);
        }
        value["secondRecommends"] = commonFilm;   //普通
        value["firstRecommends"] = bigPostFilms;  //大图
    }
    else if (interface == "剧集") {
        std::vector<std::string> title =
                m_movieAndTelevisionBroker->interfaceRecommendCategory(interface);

        json dramaArry;
        json commonDrama;
        for(int i = 0; i != 6;i++)
        {
            std::vector<Drama> dramas = m_movieAndTelevisionBroker->getRecommendDramas(i);
            json arry;
            json item;
            for(int a = 0; a != dramas.size();a++)
            {
                std::vector<std::string> resource;
                json drama;
                if(i == 0){
                    resource = dramas[a].show(true);
                    drama["name"] = resource[0];
                    drama["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    drama["rtspURL"] = url;
                    dramaArry.push_back(drama);   //存大图
                }
                else{
                    resource = dramas[a].show(false);
                    drama["name"] = resource[0];
                    drama["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    drama["rtspURL"] = url;
                    arry.push_back(drama); //存小图
                }
                if(i != 0)
                {
                    item["title"] = title[i - 1];
                    item["dramas"] = arry;
                }
            }
            if(i != 0)
                commonDrama["resource"].push_back(item);
        }
        value["secondRecommends"] = commonDrama;   //普通
        value["firstRecommends"] = dramaArry;  //大图
    }
    else if (interface == "动漫") {
        std::vector<std::string> title =
                m_movieAndTelevisionBroker->interfaceRecommendCategory(interface);

        json comicArry;
        json commonComic;
        for(int i = 0;i != 6;i++){
            std::vector<Comic> comics = m_movieAndTelevisionBroker->getRecommendComics(i);
            json array;
            json item;
            for(int a = 0;a != comics.size();a++){
                std::vector<std::string> resource;
                json comic;
                if(i == 0){
                    resource = comics[a].show(true);
                    comic["name"] = resource[0];
                    comic["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    comic["rtspURL"] = url;
                    comicArry.push_back(comic);  //存大图电影
                }
                else{
                    resource = comics[a].show(false);
                    comic["name"] = resource[0];
                    comic["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
                    comic["rtspURL"] = url;
                    array.push_back(comic); //存小图电影
                }
                if(i != 0)
                {
                    item["title"] = title[i - 1];
                    item["films"] = array;
                }
            }
            if(i != 0)
                commonComic["resource"].push_back(item);
        }
        value["secondRecommends"] = commonComic;   //普通
        value["firstRecommends"] = comicArry;  //大图
    }
    else if(interface == "综艺")
    {
        std::vector<std::string> title =
                m_movieAndTelevisionBroker->interfaceRecommendCategory(interface);

        json varietyarry;
        json commonVariety;
        for(int i=0;i!=5;i++){
            std::vector<Variety> varieties = m_movieAndTelevisionBroker->getRecommendVarieties(i);
            json arry;
            json item;
            for(int a=0;a!=varieties.size();a++)
            {
                std::vector<std::string> resource;
                json variety;
                if(i == 0){
                    resource = varieties[a].show(true);
                    variety["name"] = resource[0];
                    variety["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    variety["rtspURL"] = url;
                    varietyarry.push_back(variety);
                }else{
                    resource = varieties[a].show(false);
                    variety["name"] = resource[0];
                    variety["post"] = resource[1];
                    std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

                    variety["rtspURL"] = url;
                    arry.push_back(variety);
                }

                if(i!=0){
                    item["title"] = title[i-1];
                    item["varieties"] = arry;
                }
            }
            if(i!=0)
                commonVariety["resource"].push_back(item);
        }
        value["secondRecommends"] = commonVariety;
        value["firstRecommends"] = varietyarry;
    }

    result = value.dump();
    return result;
}



