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
            json drame;
            resource = drama1[a].show(false);
            drame["name"] = resource[0];
            drame["post"] = resource[1];
            std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;

            drame["rtspURL"] = url;
            arryd.push_back(drame);
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
        result = value.dump();
    }

    return result;
}



