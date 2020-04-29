#include "searchcontroller.h"
#include "film.h"
#include "variety.h"
#include "drama.h"
#include "comic.h"
#include "json.hpp"

using json = nlohmann::json;

SearchController* SearchController::m_instance = new SearchController();

SearchController::SearchController(){
    m_actorbroker = ActorBroker::getInstance();
    m_directorbroker = DirectorBroker::getInstance();
    m_movieAndTelevisionBroker = MovieAndTelevisionBroker::getInstance();
    m_browseAndWatchController = BrowseAndWatchController::getInstance();
}

SearchController::~SearchController()
{
    delete m_instance;
}

std::string SearchController::searchKeywords(std::string name)
{
    json root;
    json searchs;
    root["request"] = "SEARCH";

    std::vector<Film *> film = m_movieAndTelevisionBroker->searchFilm(name);
    std::vector<Drama *> drama = m_movieAndTelevisionBroker->searchDrama(name);
    std::vector<Comic *> comic = m_movieAndTelevisionBroker->searchComic(name);

    std::vector<Actor *> actor = m_actorbroker->searchActor(name);
    std::vector<Director *> director = m_directorbroker->searchDirector(name);

    if(film.size() != 0)
    {
        json search;
        std::vector<std::string> searchInfo;
        film[0]->searchInfo(searchInfo);
        search["type"] = "Film";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
//        search["episode"] = searchInfo[3];
        searchs.push_back(search);
    }
    else if(drama.size() != 0){
        json search;
        std::vector<std::string> searchInfo;
        drama[0]->searchInfo(searchInfo);
        search["type"] = "Drama";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
        search["episode"] = searchInfo[3];
        searchs.push_back(search);
    }
    else if (comic.size() != 0) {
        json search;
        std::vector<std::string> searchInfo;
        comic[0]->searchInfo(searchInfo);
        search["type"] = "Comic";
        search["name"] = searchInfo[0];
        search["post"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["rtspURL"] = m_browseAndWatchController->getUrl(searchInfo[0]);
        search["episode"] = searchInfo[3];
        searchs.push_back(search);
    }
    else if(actor.size() != 0)
    {
        json search;
        std::vector<std::string> searchInfo;
        actor[0]->searchInfo(searchInfo);
        search["type"] = "Actor";
        search["name"] = searchInfo[0];
        search["birthday"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["photo"] = searchInfo[3];
        search["region"] = searchInfo[4];
        searchs.push_back(search);
    }
    else if(director.size() != 0){
        json search;
        std::vector<std::string> searchInfo;
        director[0]->searchInfo(searchInfo);
        search["type"] = "Director";
        search["name"] = searchInfo[0];
        search["birthday"] = searchInfo[1];
        search["introduction"] = searchInfo[2];
        search["photo"] = searchInfo[3];
        search["region"] = searchInfo[4];
        searchs.push_back(search);
    }
    else{
        json search;
        search["type"] = "None";
        searchs.push_back(search);
    }
    root["searchResult"] = searchs;
    std::string out = root.dump();
    std::cout << "aaa" << out << std::endl;
    return out;
}

