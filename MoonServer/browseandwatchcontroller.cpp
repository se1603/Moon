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
                    item["films"] = arry;
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
                    item["films"] = arry;
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

std::string BrowseAndWatchController::showTypeInterface(std::string interface, std::string type)
{
    std::string reply;
    
    if(interface == "电影")
    {
        reply = filmInterface(type);
    }
    else if(interface == "剧集")
    {
        reply = dramaInterface(type);
    }
    else if(interface == "动漫")
    {
        reply = comicInterface(type);
    }
    else if(interface == "综艺")
    {
        reply = varietyInterface(type);
    }
    
    return reply;
}

std::string BrowseAndWatchController::filmInterface(std::string type)
{
    FilmType filmtype;
    if(type == "推荐")
    {
        filmtype = FilmType::Recommend;
    }
    else if(type == "喜剧")
    {
        filmtype = FilmType::Comedy;
    }
    else if(type == "动作")
    {
        filmtype = FilmType::Action;
    }
    else if(type == "动画")
    {
        filmtype = FilmType::Cartoon;
    }
    else if(type == "武侠")
    {
        filmtype = FilmType::MartialArts;
    }
    else if(type == "爱情")
    {
        filmtype = FilmType::Love;
    }
    else if(type == "科幻")
    {
        filmtype = FilmType::ScienceFiction;
    }
    else if(type == "悬疑")
    {
        filmtype = FilmType::Suspense;
    }
    else if(type == "惊悚")
    {
        filmtype = FilmType::Terror;
    }
    std::vector<Film> films;
    films = m_movieAndTelevisionBroker->getFilms(filmtype);
    
    json root;
    json arryObj;
    root["request"] = "TYPEINTERFACE";
    root["interface"] = "电影";
    root["type"] = type;
    for(int i = 0; i != films.size();i++)
    {
        std::vector<std::string> resource;
        resource = films[i].show(false);
        json item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        
        item["rtspURL"] = url;
        arryObj.push_back(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.dump();
    
    return out;
}

std::string BrowseAndWatchController::dramaInterface(std::string type)
{
    
    DramaType Dramatype;
    
    if(type == "推荐")
    {
        Dramatype = DramaType::Recommend;
    }
    else if(type == "古装")
    {
        Dramatype = DramaType::AncientCostume;
    }
    else if(type == "悬疑")
    {
        Dramatype = DramaType::Suspense;
    }
    else if(type == "武侠")
    {
        Dramatype = DramaType::MartialArts;
    }
    else if(type == "都市")
    {
        Dramatype = DramaType::Metropolis;
    }
    else if (type == "历史") {
        Dramatype = DramaType::History;
    }
    else if(type == "偶像")
    {
        Dramatype = DramaType::Idol;
    }
    else if(type == "家庭")
    {
        Dramatype = DramaType::Family;
    }
    else if(type == "科幻")
    {
        Dramatype = DramaType::ScienceFiction;
    }
    
    std::vector<Drama> Dramas; color: "lightblue";
    Dramas = m_movieAndTelevisionBroker->getDramas(Dramatype);
    
    json root;
    json arryObj;
    root["request"] = "TYPEINTERFACE";
    root["interface"] = "剧集";
    root["type"] = type;
    for(int i=0;i != Dramas.size();i++){
        std::vector<std::string> resource;
        resource = Dramas[i].show(false);
        json item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        item["rtspURL"] = url;
        arryObj.push_back(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.dump();
    
    return out;
}

std::string BrowseAndWatchController::varietyInterface(std::string type)
{
    VarietyType varietytype;
    
    if(type == "推荐")
    {
        varietytype = VarietyType::Recommend;
    }
    else if(type == "真人秀")
    {
        varietytype = VarietyType::RealityShow;
    }
    else if(type == "选秀")
    {

        varietytype = VarietyType::TalentShow;
    }
    else if(type == "美食")
    {
        varietytype = VarietyType::Food;
    }
    else if(type == "旅游")
    {
        varietytype = VarietyType::Travel;
    }
    else if(type == "纪实")
    {

        varietytype = VarietyType::ActualRecord;
    }
    else if(type == "搞笑")
    {
        varietytype = VarietyType::Funny;
    }
    else if(type == "访谈")
    {

        varietytype = VarietyType::Interview;
    }
    
    std::vector<Variety> varieties;
    varieties = m_movieAndTelevisionBroker->getVarieties(varietytype);
    
    json root;
    json arryObj;
    root["request"] = "TYPEINTERFACE";
    root["interface"] = "综艺";
    root["type"] = type;
    for(int i=0;i != varieties.size();i++){
        std::vector<std::string> resource;
        resource = varieties[i].show(false);
        json item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        item["rtspURL"] = url;
        arryObj.push_back(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.dump();
    
    return out;
}

std::string BrowseAndWatchController::comicInterface(std::string type)
{
    ComicType comictype;
    
    if(type == "推荐")
    {
        comictype = ComicType::Recommend;
    }
    else if(type == "机战")
    {
        comictype =ComicType::RobotWars;
    }
    else if(type == "青春")
    {

        comictype = ComicType::Youth;
    }
    else if(type == "格斗")
    {
        comictype = ComicType::Combat;
    }
    else if(type == "恋爱")
    {
        comictype = ComicType::Love;
    }
    else if(type == "美少女")
    {

        comictype = ComicType::Kayoing;
    }
    else if(type == "热血")
    {
        comictype = ComicType::WarmBlood;
    }
    else if(type == "校园")
    {

        comictype = ComicType::Campus;
    }

    std::vector<Comic> comics;
    comics = m_movieAndTelevisionBroker->getComics(comictype);
    
    json root;
    json arryObj;
    root["request"] = "INTERFACE";
    root["interface"] = 3;
    root["type"] = type;
    
    for(int i = 0; i != comics.size();i++)
    {
        std::vector<std::string> resource;
        resource = comics[i].show(false);
        json item;
        item["name"] = resource[0];
        item["post"] = resource[1];
        
        std::string url = "rtsp://" + m_rtspAddress + "/movies/" + resource[0] ;
        
        item["rtspURL"] = url;
        arryObj.push_back(item);
    }
    root["movieAndTelevision"] = arryObj;
    std::string out = root.dump();
    
    return out;
}


std::string BrowseAndWatchController::getMovieInfomation(std::string name)
{
    json root;
    std::string out;
    root["request"] = "Infomation";
    root["name"] = name;
    auto f = m_movieAndTelevisionBroker->getVideoInfo(name);
    json value;
    json types;
    root["videotype"] = 1;
    for(int i = 0;i != f.size();i++){
        json type;
        if(i == 0){
            value["esipode"] = f[0];
        }else if(i == 1){
            value["introduction"] = f[1];
        }else if(i == 2){
            value["category"] = f[2];
        }else if(i==3){
            value["region"] = f[3];
        }
        else{
            type["type"] = f[i];
            types.push_back(type);
//            types.append(type);w
        }
    }
    value["videotype"] = types;
    root["resource"] = value;
    out = root.dump();

    return out;
}

std::string BrowseAndWatchController::getActorInfomation(std::string name)
{
    json root;
    std::string out;

    root["request"] = "ACTORINFOMATION";
    root["name"] = name;

    auto info = m_movieAndTelevisionBroker->getActorInfo(name);
    json values;

    //    std::cout << "information"<<info.size() << std::endl;
    for(int i = 0;i != info.size();i+=3){
        json value;
        value["name"] = info[i];
        value["type"] = info[i+1];
        value["post"] = info[i+2];
        values.push_back(value);
    }
    root["resource"] = values;
    out = root.dump();

    return out;
}
