#include "movieandtelevisionbroker.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
using std::cout;    using std::string;
using std::endl;

MovieAndTelevisionBroker* MovieAndTelevisionBroker::m_instance = new MovieAndTelevisionBroker;

MovieAndTelevisionBroker::MovieAndTelevisionBroker()
{
    m_actorBroker = ActorBroker::getInstance();
    m_directorBroker = DirectorBroker::getInstance();
    m_categorys["HomePage"] = {"精选","电影","剧集","动漫","综艺"};
    m_categorys["电影"] = {"推荐","喜剧","武侠","动画","悬疑","爱情","科幻","惊悚","动作"};
    m_categorys["剧集"] = {"推荐","古装","悬疑","武侠","都市","历史","偶像", "家庭","科幻"};
    m_categorys["动漫"] = {"推荐","机战","青春","格斗","恋爱","美少女","热血","校园"};
    m_categorys["综艺"] = {"推荐","真人秀","选秀","美食","旅游","纪实","搞笑","访谈"};

    m_recommendCatergory["精选"] = {"电影精选","剧集精选","动漫精选","综艺精选"};
    m_recommendCatergory["电影"] = {"正在热播","热门华语大片","高人气好莱坞大片","经典高分港片","历年贺岁大片精选"};
    m_recommendCatergory["剧集"] = {"正在热播","猜你喜欢","排行榜","卫视同步","偶像剧场"};
    m_recommendCatergory["动漫"] = {"正在热播","日漫推荐","国漫推荐","独家播放","经典日漫"};
    m_recommendCatergory["综艺"] = {"热门在播综艺","今日份快乐源泉请查收","地表最强真人秀","细说人生百态"};

    initFilms();
    initVarieties();
    initComics();
    initDrama();
}

MovieAndTelevisionBroker::~MovieAndTelevisionBroker()
{
    delete m_instance;
}

std::vector<std::string> MovieAndTelevisionBroker::InterfaceCategory(std::string interface)
{
    std::vector<std::string> res = m_categorys[interface];
    return res;
}

std::vector<std::string> MovieAndTelevisionBroker::interfaceRecommendCategory(std::string interface)
{
    std::vector<std::string> res = m_recommendCatergory[interface];
    return res;
}

void MovieAndTelevisionBroker::splictString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

std::vector<std::string> MovieAndTelevisionBroker::mainCategory()
{
    std::vector<std::string> categorys = {"电影","综艺","动漫","剧集"};
    return categorys;
}

void MovieAndTelevisionBroker::initFilms()
{
    if(!m_films.empty())
        m_films.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0))
    {
        cout << "(Film)Connect MYSQL failed." << endl;
    }
    else{
        cout << "(Film)Connect MYSQL succed." << endl;
    }

    std::string sql = "select * from Film;";
    if(mysql_query(mysql,sql.data())){
        cout << "获取目录失败" << endl;
    }
    else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);  //获取下一行
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i = 0;i < mysql_num_fields(result);++i){
                //                std::cout << row[i] << std::endl;
                res.push_back(row[i]);
            }
            Film f = handleFilm(res);
            f.save(m_films);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Film MovieAndTelevisionBroker::handleFilm(std::vector<std::string> row)
{
    std::vector<std::string> filmDirector,filmActor,filmPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<FilmType> filmtype;     //电影类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            filmtype.push_back(FilmType::MartialArts);
            break;
        case 2:
            filmtype.push_back(FilmType::Suspense);
            break;
        case 3:
            filmtype.push_back(FilmType::Comedy);
            break;
        case 4:
            filmtype.push_back(FilmType::Action);
            break;
        case 5:
            filmtype.push_back(FilmType::Love);
            break;
        case 6:
            filmtype.push_back(FilmType::Cartoon);
            break;
        case 7:
            filmtype.push_back(FilmType::Terror);
            break;
        case 8:
            filmtype.push_back(FilmType::ScienceFiction);
            break;
        default:
            break;
        }
    }
    Region filmRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        filmRegion = Region::China;
        break;
    case 2:
        filmRegion = Region::American;
        break;
    case 3:
        filmRegion = Region::Korea;
        break;
    case 4:
        filmRegion = Region::India;
        break;
    case 5:
        filmRegion = Region::THailand;
        break;
    case 6:
        filmRegion = Region::Britain;
        break;
    default:
        break;
    }
    splictString(row[3],filmDirector,",");
    std::vector<Director *> directors;
    directors = m_directorBroker->findDirector(filmDirector);

    splictString(row[4],filmActor,",");
    std::vector<Actor *> actors;

    actors = m_actorBroker->findActor(filmActor);

    splictString(row[5],filmPost,",");
    splictString(row[7],recommend,",");
    std::vector<int> filmRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        filmRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Film film(row[0],row[6],filmRegion,filmPost,
            actors,directors,filmtype,filmRecommends);
    m_actorBroker->addMovieAndTelevision(filmActor,film);
    m_directorBroker->addMovieAndTelevision(filmDirector, film);

    return film;
}

std::vector<Film> MovieAndTelevisionBroker::getFilms(FilmType type)
{
    std::vector<Film> result;
    for(auto it = m_films.begin(); it != m_films.end();it++)
    {
        Film tmp = it->second;
        tmp.findFilmByType(type,result);
    }
    return result;
}

std::vector<Film> MovieAndTelevisionBroker::getRecommendFilms(int type)
{
    std::vector<Film> result;
    for(auto it = m_films.begin(); it != m_films.end();it++)
    {
        Film tmp = it->second;
        tmp.findFilmByRecommend(type,result);
    }
    return result;
}

void MovieAndTelevisionBroker::initDrama()
{
    if(!m_dramas.empty())
        m_dramas.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        cout << "(Drama)Connect MYSQL failed." << endl;
    }else{
        cout << "(Drama)Connect MYSQL succeed." << endl;
    }

    std::string sql = "select * from Drama;";
    if(mysql_query(mysql,sql.data())){
        cout << "(Drama)获取失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i=0;i<mysql_num_fields(result);++i){
                res.push_back(row[i]);
                //                    cout << i << "  " << row[i] << endl;
            }
            Drama drama= handleDrama(res);
            drama.save(m_dramas);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Drama MovieAndTelevisionBroker::handleDrama(std::vector<std::string> row)
{
    std::vector<std::string> dramaDirector,dramaActor,dramaPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<DramaType> dramatype;     //剧集类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            dramatype.push_back(DramaType::AncientCostume);
            break;
        case 2:
            dramatype.push_back(DramaType::Suspense);
            break;
        case 3:
            dramatype.push_back(DramaType::MartialArts);
            break;
        case 4:
            dramatype.push_back(DramaType::Metropolis);
            break;
        case 5:
            dramatype.push_back(DramaType::History);
            break;
        case 6:
            dramatype.push_back(DramaType::Idol);
            break;
        case 7:
            dramatype.push_back(DramaType::Family);
            break;
        case 8:
            dramatype.push_back(DramaType::ScienceFiction);
            break;
        default:
            break;
        }
    }
    Region dramaRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        dramaRegion = Region::China;
        break;
    case 2:
        dramaRegion = Region::American;
        break;
    case 3:
        dramaRegion = Region::Korea;
        break;
    case 4:
        dramaRegion = Region::India;
        break;
    case 5:
        dramaRegion = Region::THailand;
        break;
    case 6:
        dramaRegion = Region::Britain;
        break;
    case 7:
        dramaRegion = Region::Japan;
        break;
    default:
        break;
    }
    splictString(row[3],dramaDirector,",");
    std::vector<Director *> directors;
    directors = m_directorBroker->findDirector(dramaDirector);

    splictString(row[4],dramaActor,",");
    std::vector<Actor *> actors;
    actors = m_actorBroker->findActor(dramaActor);


    splictString(row[5],dramaPost,",");
    splictString(row[7],recommend,",");
    std::vector<int> dramaRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        dramaRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Drama drame(row[0],row[6],dramaRegion,dramaPost,actors,directors,dramatype,atoi(row[8].c_str()),dramaRecommends);

    m_actorBroker->addMovieAndTelevision(dramaActor,drame);


    m_directorBroker->addMovieAndTelevision(dramaDirector, drame);


    return drame;
}

std::vector<Drama> MovieAndTelevisionBroker::getDramas(DramaType type)
{
    std::vector<Drama> result;
    for(auto it = m_dramas.begin(); it != m_dramas.end();it++){
        Drama tmp = it->second;
        tmp.findDramaByType(type, result);
    }
    return result;
}

std::vector<Drama> MovieAndTelevisionBroker::getRecommendDramas(int type)
{
    std::vector<Drama> result;
    for(auto it = m_dramas.begin(); it != m_dramas.end();it++){
        Drama tmp = it->second;
        tmp.findDramaByRecommend(type,result);
    }
    return result;
}

void MovieAndTelevisionBroker::initVarieties()
{
    if(!m_varieties.empty())
        m_varieties.clear();

    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        cout << "(Variety)Connect MYSQL failed." << endl;
    }else{
        cout << "(Variety)Connect MYSQL succeed." << endl;
    }

    std::string sql = "select * from VarietyShow;";
    if(mysql_query(mysql,sql.data())){
        cout << "(Variety)获取失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned int i=0;i<mysql_num_fields(result);++i){
                res.push_back(row[i]);
            }
            Variety v = handleVariety(res);
            v.save(m_varieties);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Variety MovieAndTelevisionBroker::handleVariety(std::vector<std::string> row)
{
    std::vector<std::string> varietyDirector,varietyActor,varietyPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<VarietyType> varietytype;
    for(int i=0;i!=type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            varietytype.push_back(VarietyType::RealityShow);
            break;
        case 2:
            varietytype.push_back(VarietyType::TalentShow);
            break;
        case 3:
            varietytype.push_back(VarietyType::Food);
            break;
        case 4:
            varietytype.push_back(VarietyType::Travel);
            break;
        case 5:
            varietytype.push_back(VarietyType::ActualRecord);
            break;
        case 6:
            varietytype.push_back(VarietyType::Funny);
            break;
        case 7:
            varietytype.push_back(VarietyType::Interview);
            break;
        default:
            break;
        }
    }

    int varietyEpisodes = atoi(row[2].c_str());

    Region varietyRegion = Region::China;
    switch (atoi(row[3].c_str())) {
    case 1:
        varietyRegion = Region::China;
        break;
    case 2:
        varietyRegion = Region::American;
        break;
    case 3:
        varietyRegion = Region::Korea;
        break;
    case 4:
        varietyRegion = Region::India;
        break;
    case 5:
        varietyRegion = Region::THailand;
        break;
    case 6:
        varietyRegion = Region::Britain;
        break;
    default:
        break;
    }
    splictString(row[4],varietyDirector,",");
    std::vector<Director *> directors;
    directors = m_directorBroker->findDirector(varietyDirector);

    splictString(row[5],varietyActor,"/");
    std::vector<Actor *> actors;
    actors = m_actorBroker->findActor(varietyActor);


    splictString(row[6],varietyPost,",");

    splictString(row[8],recommend,",");
    std::vector<int> varietyRecommends;
    for(int i=0;i!=recommend.size();i++){
        varietyRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Variety variety(row[0],row[7],varietyRegion,varietyPost,actors,directors,
            varietytype,varietyRecommends,varietyEpisodes);

    m_actorBroker->addMovieAndTelevision(varietyActor,variety);

    m_directorBroker->addMovieAndTelevision(varietyDirector, variety);

    return variety;
}

std::vector<Variety> MovieAndTelevisionBroker::getVarieties(VarietyType type)
{
    std::vector<Variety> result;
    for(auto it = m_varieties.begin(); it != m_varieties.end();it++){
        Variety tmp = it->second;
        tmp.findVarietyByType(type,result);
    }
    return result;
}

std::vector<Variety> MovieAndTelevisionBroker::getRecommendVarieties(int type)
{
    std::vector<Variety> result;
    for(auto it = m_varieties.begin(); it != m_varieties.end();it++){
        Variety tmp = it->second;
        tmp.findVarietyByRecommend(type,result);
    }
    return result;
}

void MovieAndTelevisionBroker::initComics()
{
    if(!m_comics.empty())
        m_comics.clear();
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0))
    {
        cout << "(Comic)Connect MYSQL failed." << endl;
    }else{
        cout << "(Comic)Connect MYSQL succed." << endl;
    }

    std::string sql = "select * from Comic;";
    if(mysql_query(mysql,sql.data())){
        cout << "获取目录失败" << endl;
    }else{
        result = mysql_use_result(mysql);
        while(1){
            row = mysql_fetch_row(result);
            if(row == nullptr) break;
            std::vector<string> res;
            for(unsigned i = 0;i < mysql_num_fields(result);++i){
                //                cout << i << "  " << row[i] << endl;
                res.push_back(row[i]);
            }
            Comic c = handleComic(res);
            c.save(m_comics);
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
    mysql_library_end();
}

Comic MovieAndTelevisionBroker::handleComic(std::vector<std::string> row)
{
    std::vector<std::string> comicDirector,comicActor,comicPost,recommend,type;

    splictString(row[1],type,",");
    std::vector<ComicType> comictype;     //动漫类型
    for(int i = 0; i != type.size();i++)
    {
        switch (atoi(type[i].c_str())) {
        case 1:
            comictype.push_back(ComicType::RobotWars);
            break;
        case 2:
            comictype.push_back(ComicType::Youth);
            break;
        case 3:
            comictype.push_back(ComicType::Combat);
            break;
        case 4:
            comictype.push_back(ComicType::Love);
            break;
        case 5:
            comictype.push_back(ComicType::Kayoing);
            break;
        case 6:
            comictype.push_back(ComicType::WarmBlood);
            break;
        case 7:
            comictype.push_back(ComicType::Campus);
            break;
        default:
            break;
        }
    }
    Region comicRegion = Region::China;
    switch (atoi(row[2].c_str())) {
    case 1:
        comicRegion = Region::China;
        break;
    case 2:
        comicRegion = Region::American;
        break;
    case 3:
        comicRegion = Region::Korea;
        break;
    case 4:
        comicRegion = Region::India;
        break;
    case 5:
        comicRegion = Region::THailand;
        break;
    case 6:
        comicRegion = Region::Britain;
        break;
    case 7:
        comicRegion = Region::Japan;
        break;
    default:
        break;
    }
    splictString(row[4],comicDirector,",");
    std::vector<Director *> directors;
    directors = m_directorBroker->findDirector(comicDirector);
    //    for(int i = 0; i != comicDirector.size();i++)
    //    {
    //        auto it = m_directors.find(comicDirector[i]);
    //        if(it != m_directors.end())
    //        {
    //            directors.push_back(&it->second);
    //        }
    //        else {
    //            Director d = Director(comicDirector[i]);
    //            m_directors[comicDirector[i]] = d;
    //            directors.push_back(&m_directors[comicDirector[i]]);
    //        }
    //    }
    splictString(row[5],comicActor,",");

    std::vector<Actor *> actors = m_actorBroker->findActor(comicActor);
    //    for(int i = 0; i != comicActor.size();i++)
    //    {
    //        auto it = m_actors.find(comicActor[i]);
    //        if(it != m_actors.end())
    //        {
    //            actors.push_back(&it->second);
    //        }
    //        else {
    //            Actor tmpActor(comicActor[i]);
    //            m_actors[comicActor[i]] = tmpActor;
    //            actors.push_back(&m_actors[comicActor[i]]);
    //        }
    //    }

    splictString(row[6],comicPost,",");

    splictString(row[8],recommend,",");
    std::vector<int> comicRecommends;
    for(int i = 0; i != recommend.size();i++)
    {
        comicRecommends.push_back(atoi(recommend[i].c_str()));
    }

    Comic comic(row[0],row[7],comicRegion,comicPost,actors,directors,comictype,atoi(row[3].c_str()),comicRecommends);

    m_actorBroker->addMovieAndTelevision(comicActor,comic);
    //    for (int i = 0;i != comicActor.size();i ++)
    //    {
    //        auto it = m_actors.find(comicActor[i]);
    //        if(it != m_actors.end())
    //        {
    //            it->second.addMovieAndTelevision(&comic);
    //        }
    //    }

    m_directorBroker->addMovieAndTelevision(comicDirector, comic);
    //    for (int i = 0;i != comicDirector.size();i ++)
    //    {
    //        auto it = m_directors.find(comicDirector[i]);
    //        if(it != m_directors.end())
    //        {
    //            it->second.addMovieAndTelevision(&comic);
    //        }
    //    }

    return comic;
}

std::vector<Comic> MovieAndTelevisionBroker::getComics(ComicType type)
{
    std::vector<Comic> result;
    for(auto it = m_comics.begin(); it != m_comics.end();it++)
    {
        Comic tmp = it->second;
        tmp.findComicByType(type,result);
    }
    return result;
}

std::vector<Comic> MovieAndTelevisionBroker::getRecommendComics(int type)
{
    std::vector<Comic> result;
    for(auto it = m_comics.begin(); it != m_comics.end();it++){
        Comic tem = it->second;
        tem.findComicByRecommend(type,result);
    }
    return result;
}

//识别用户收藏
void MovieAndTelevisionBroker::processAudienceCollection(std::vector<std::string> tmp, MovieAndTelevision *m)
{
    std::cout << "~~~~~~~~" << std::endl;
    auto n = atoi(tmp[2].c_str());
    std::cout << n << std::endl;
    switch(n) {
    case 1:{
        for(auto item = m_films.begin();item != m_films.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 2:{
        for(auto item = m_dramas.begin();item != m_dramas.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 3:{
        for(auto item = m_comics.begin();item != m_comics.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 4:{
        for(auto item = m_varieties.begin();item != m_varieties.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    }
    std::cout << "shenmegui" << std::endl;
}

//识别用户记录
void MovieAndTelevisionBroker::processAudienceRecord(std::vector<std::string> tmp, MovieAndTelevision* m)
{
    std::cout << "shenmegui99999999" << std::endl;
    auto n = atoi(tmp[3].c_str());
    switch(n) {
    case 1:{
        for(auto item = m_films.begin();item != m_films.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 2:{
        for(auto item = m_dramas.begin();item != m_dramas.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 3:{
        for(auto item = m_comics.begin();item != m_comics.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    case 4:{
        for(auto item = m_varieties.begin();item != m_varieties.end();item++){
            if(item->first == tmp[0]){
                *m = item->second;
            }
        }
    }
        break;
    }
}

//展示收藏
void MovieAndTelevisionBroker::showCollection(MovieAndTelevision *m, std::vector<std::string> &collections)
{
    m->showInfo(collections);
}

//展示记录
void MovieAndTelevisionBroker::showRecord(MovieAndTelevision *m, std::vector<std::string> &records)
{
    m->showInfo(records);
}

std::vector<std::string> MovieAndTelevisionBroker::getVideoInfo(std::string name)
{
    std::vector<std::string> resource;
    auto tem = m_films.find(name);
    if(tem != m_films.end()){
        tem->second.recodeInfo(name,resource);
    }

    if(resource.size()==0){
        auto c = m_comics.find(name);
        if(c!=m_comics.end()){
            c->second.recodeInfo(name,resource);
        }
    }
    if(resource.size()==0){
        auto d = m_dramas.find(name);
        if(d != m_dramas.end()){
            d->second.recodeInfo(name,resource);
        }
    }

    if(resource.size()==0){
        auto v =m_varieties.find(name);
        if(v != m_varieties.end()){
            v->second.recodeInfo(name,resource);
        }
    }

    return resource;
}

std::vector<std::string> MovieAndTelevisionBroker::getActorInfo(std::string name)
{
    std::vector<std::string> resource;
    auto n = m_films.find(name);
    if(n != m_films.end()){
        auto tem = n->second;
        tem.getActorInfo(name,resource);
    }

    if(resource.size() != 0){
        return resource;
    }
    auto d = m_dramas.find(name);
    if(d != m_dramas.end()){
        auto tem = d->second;
        tem.getActorInfo(name,resource);
    }

    if(resource.size() != 0){
        return resource;
    }

    auto c = m_comics.find(name);
    if(c != m_comics.end()){
        auto tem = c->second;
        tem.getActorInfo(name,resource);
    }

    if(resource.size() != 0){
        return resource;
    }

    auto v = m_varieties.find(name);
    if(v != m_varieties.end()){
        auto tem = v->second;
        tem.getActorInfo(name,resource);
    }

    return resource;
}
void MovieAndTelevisionBroker::findMovieandTelevision(std::string name, MovieAndTelevision *m)
{
    cout << "jjj" << endl;
    auto f = m_films.find(name);
    cout << "ddd" << endl;
    if(f != m_films.end()){
        *m = f->second;
        return;
    }
    auto c = m_comics.find(name);
    if(c != m_comics.end()){
        *m = c->second;
        return;
    }
    auto d = m_dramas.find(name);
    if(d != m_dramas.end()){
        *m = d->second;
        return;
    }
    auto v = m_varieties.find(name);
    if(v != m_varieties.end()){
        *m = v->second;
        return;
    }
}

std::map<std::string, std::string> MovieAndTelevisionBroker::getVideos(std::string category, std::string type)
{
    std::map<std::string,std::string> videos;

    if(category == "电影"){

    }else if (category == "综艺") {

    }else if (category == "动漫") {

    }else if (category == "剧集") {

    }
}

std::map<std::string,std::string> MovieAndTelevisionBroker::searchVideos(std::string name)
{
    std::map<std::string,std::string> videoinfo;

    for(auto item = m_films.begin(); item != m_films.end(); item++){
        if(item->first == name){
            std::string n;
            item->second.showPost(n);
            videoinfo.insert(std::make_pair(name,n));
            break;
        }
    }
    for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
        if(item->first == name){
            std::string n;
            item->second.showPost(n);
            videoinfo.insert(std::make_pair(name,n));
            break;
        }
    }
    for(auto item = m_comics.begin(); item != m_comics.end(); item++){
        if(item->first == name){
            std::string n;
            item->second.showPost(n);
            videoinfo.insert(std::make_pair(name,n));
            break;
        }
    }
    for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
        if(item->first == name){
            std::string n;
            item->second.showPost(n);
            videoinfo.insert(std::make_pair(name,n));
            break;
        }
    }

    return videoinfo;
}

MovieAndTelevision* MovieAndTelevisionBroker::addAdvert(std::string video, Advert *a, std::string videotype)
{
    if(videotype == "电影"){
        for(auto item = m_films.begin(); item != m_films.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }
    }else if(videotype == "综艺"){
        for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }
    }else if(videotype == "动漫"){
        for(auto item = m_comics.begin(); item != m_comics.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }
    }else if(videotype == "剧集"){
        for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }
    }else if(videotype == "未知"){
        for(auto item = m_films.begin(); item != m_films.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }

        for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }

        for(auto item = m_comics.begin(); item != m_comics.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }

        for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
            if(item->first == video){
                item->second.addAdvertLink(a);
                MovieAndTelevision* mv = new MovieAndTelevision();
                mv = &item->second;
                return mv;
            }
        }
    }
}

std::vector<Advert *> MovieAndTelevisionBroker::showAdverts(std::string name, std::string type)
{
    std::vector<Advert*> vec;

    if(type == "电影"){
        std::cout << "this is f" << std::endl;
        for(auto item = m_films.begin(); item != m_films.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
    }else if(type == "综艺"){
        std::cout << "this is v" << std::endl;
        for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
    }else if(type == "动漫"){
        std::cout << "this is c" << std::endl;
        for(auto item = m_comics.begin(); item != m_comics.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }

    }else if(type == "剧集"){
        std::cout << "this is drama" << std::endl;
        for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
    }else if(type == "空"){
        for(auto item = m_films.begin(); item != m_films.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
        for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
        for(auto item = m_comics.begin(); item != m_comics.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
        for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
            if(item->first == name){
                vec = item->second.showAdvertLink();
                break;
            }
        }
    }

    return vec;
}

MovieAndTelevision* MovieAndTelevisionBroker::initAdvertLinks(std::string videoname, Advert *a)
{

    for(auto item = m_films.begin(); item != m_films.end(); item++){
        if(item->first == videoname){
            item->second.addAdvertLink(a);
            MovieAndTelevision* mv = new MovieAndTelevision();
            mv = &item->second;
            return mv;
        }
    }

    for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
        if(item->first == videoname){
            item->second.addAdvertLink(a);
            MovieAndTelevision* mv = new MovieAndTelevision();
            mv = &item->second;
            return mv;
        }
    }

    for(auto item = m_comics.begin(); item != m_comics.end(); item++){
        if(item->first == videoname){
            item->second.addAdvertLink(a);
            MovieAndTelevision* mv = new MovieAndTelevision();
            mv = &item->second;
            return mv;
        }
    }

    for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
        if(item->first == videoname){
            item->second.addAdvertLink(a);
            MovieAndTelevision* mv = new MovieAndTelevision();
            mv = &item->second;
            return mv;
        }
    }
}

bool MovieAndTelevisionBroker::deleteVideoAdverts(std::string videoname, std::string advertname)
{
    bool res;
    for(auto item = m_films.begin(); item != m_films.end(); item++){
        if(item->first == videoname){
            res = item->second.deleteAdvertLink(advertname);
            break;
        }
    }

    for(auto item = m_varieties.begin(); item != m_varieties.end(); item++){
        if(item->first == videoname){
            res = item->second.deleteAdvertLink(advertname);
            break;
        }
    }

    for(auto item = m_comics.begin(); item != m_comics.end(); item++){
        if(item->first == videoname){
            res = item->second.deleteAdvertLink(advertname);
            break;
        }
    }

    for(auto item = m_dramas.begin(); item != m_dramas.end(); item++){
        if(item->first == videoname){
            res = item->second.deleteAdvertLink(advertname);
            break;
        }
    }

    return res;
}
bool MovieAndTelevisionBroker::initMovieandTelevision(std::string s)
{
    json j = json::parse(s);
    //    for (json::iterator it = j.begin(); it != j.end(); ++it) {
    //      std::cout << *it << '\n';

    //    }
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "Database connect failed" << std::endl;
    }else{
        std::cout << "Database connect Successed" << std::endl;
    }

    auto k = j.size();
    for(int i = 0;i < j.size();i++){
        std::string name = j[i]["name"];
        std::string typ = j[i]["type"];

        std::vector<std::string> typeV = dealType(typ);
        std::string type="";
        for(auto i:typeV){
            type += i;
        }
        std::string region = j[i]["region"];
        Region re;
        re = dealRegion(region);

        std::string esd = j[i]["episode"];
        std::string director = j[i]["director"];
        std::string actor = j[i]["actor"];
        std::string introduction = j[i]["introduction"];
        std::string image = j[i]["image"];
        std::string rec;
        if("否" == j[i]["recommmd"]){
            rec ="99";
        }else{
            rec ="2";
        }
        std::string sql;

        //处理信息，构造影视初始化函数
        auto post = dealPost(image);
        auto actors = dealActor(actor);
        auto directors = dealDirector(director);
        auto recom = dealRecommends(rec);
        if("剧集" == j[i]["bigType"]){
            std::vector<DramaType> dramatype;     //剧集类型
            for(int i = 0; i != typeV.size();i++)
            {
                switch (atoi(typeV[i].c_str())) {
                case 1:
                    dramatype.push_back(DramaType::AncientCostume);
                    break;
                case 2:
                    dramatype.push_back(DramaType::Suspense);
                    break;
                case 3:
                    dramatype.push_back(DramaType::MartialArts);
                    break;
                case 4:
                    dramatype.push_back(DramaType::Metropolis);
                    break;
                case 5:
                    dramatype.push_back(DramaType::History);
                    break;
                case 6:
                    dramatype.push_back(DramaType::Idol);
                    break;
                case 7:
                    dramatype.push_back(DramaType::Family);
                    break;
                case 8:
                    dramatype.push_back(DramaType::ScienceFiction);
                    break;
                default:
                    break;
                }
            }
            Drama drama(name,introduction,re,post,actors,directors,dramatype,atoi(esd.c_str()),recom);
            if(m_dramas.find(name)!=m_dramas.end()){
                m_dramas.erase(name);
                drama.save(m_dramas);
                sql="update Drama set type = '"+type+"',region = '"+region+"',director = '"+director+"',actor = '"+actor+"',post ='"+image+"',introduction ='"+introduction+"',recommend = '"+rec+"',episode = '"+ esd+"' where name = '"+name+"';";
            }else{
                drama.save(m_dramas);
                 sql = "insert into Drama(name,type,region,director,actor,post,introduction,recommend, episode) values('"+name+"','"+type+"','"+region+"','"+director+"','"+actor+"','"+image+"','"+introduction+"','"+rec+"','"+esd+"');";

            }

        }else if("动漫" == j[i]["bigType"]){
//            std::vector<ComicType> comictype;
            std::vector<ComicType> comictype;     //动漫类型
            for(int i = 0; i != typeV.size();i++)
            {
                switch (atoi(typeV[i].c_str())) {
                case 1:
                    comictype.push_back(ComicType::RobotWars);
                    break;
                case 2:
                    comictype.push_back(ComicType::Youth);
                    break;
                case 3:
                    comictype.push_back(ComicType::Combat);
                    break;
                case 4:
                    comictype.push_back(ComicType::Love);
                    break;
                case 5:
                    comictype.push_back(ComicType::Kayoing);
                    break;
                case 6:
                    comictype.push_back(ComicType::WarmBlood);
                    break;
                case 7:
                    comictype.push_back(ComicType::Campus);
                    break;
                default:
                    break;
                }
            }
            Comic comic(name,introduction,re,post,actors,directors,comictype,atoi(esd.c_str()),recom);
            if(m_comics.find(name) != m_comics.end()){
                m_comics.erase(name);
                comic.save(m_comics);
                sql="update Comic set type = '"+type+"',region = '"+region+"',director = '"+director+"',actor = '"+actor+"',post ='"+image+"',introduction ='"+introduction+"',recommend = '"+rec+"',epilide = '"+ esd+"' where name = '"+name+"';";
            }else{
                 comic.save(m_comics);
                 sql = "insert into Comic(name,type,region,epilide,director,actor,post,introduction,recommend) values('"+name+"','"+type+"','"+region+"','"+esd+"','"+director+"','"+actor+"','"+image+"','"+introduction+"','"+rec+"');";
            }

        }else if("电影" == j[i]["bigType"]){
            std::vector<FilmType> filmtype;     //电影类型
            for(int i = 0; i != typeV.size();i++)
            {
                switch (atoi(typeV[i].c_str())) {
                case 1:
                    filmtype.push_back(FilmType::MartialArts);
                    break;
                case 2:
                    filmtype.push_back(FilmType::Suspense);
                    break;
                case 3:
                    filmtype.push_back(FilmType::Comedy);
                    break;
                case 4:
                    filmtype.push_back(FilmType::Action);
                    break;
                case 5:
                    filmtype.push_back(FilmType::Love);
                    break;
                case 6:
                    filmtype.push_back(FilmType::Cartoon);
                    break;
                case 7:
                    filmtype.push_back(FilmType::Terror);
                    break;
                case 8:
                    filmtype.push_back(FilmType::ScienceFiction);
                    break;
                default:
                    break;
                }
            }
            Film film(name,introduction,re,post,actors,directors,filmtype,recom);
            if(m_films.find(name) != m_films.end()){
                m_films.erase(name);
                film.save(m_films);
                 sql="update Film set type = '"+type+"',region = '"+region+"',director = '"+director+"',actor = '"+actor+"',post ='"+image+"',introduction ='"+introduction+"',recommend = '"+rec+"' where name = '"+name+"';";
            }else{
                 film.save(m_films);
                sql = "insert into Film(name,type,region,director,actor,post,introduction,recommend) values('"+name+"','"+type+"','"+region+"','"+director+"','"+actor+"','"+image+"','"+introduction+"','"+rec+"');";
            }

        }else if("综艺" == j[i]["bigType"]){
            //            Variety(std::string name,std::string introduction,
            //                    Region region,std::vector<std::string> posts,
            //                    std::vector<Actor *> actors,
            //                    std::vector<Director *> directors,std::vector<VarietyType> types,
            //                    std::vector<int> recommends,int episodes);
            std::vector<VarietyType> varietytype;
            for(int i=0;i!=typeV.size();i++)
            {
                switch (atoi(typeV[i].c_str())) {
                case 1:
                    varietytype.push_back(VarietyType::RealityShow);
                    break;
                case 2:
                    varietytype.push_back(VarietyType::TalentShow);
                    break;
                case 3:
                    varietytype.push_back(VarietyType::Food);
                    break;
                case 4:
                    varietytype.push_back(VarietyType::Travel);
                    break;
                case 5:
                    varietytype.push_back(VarietyType::ActualRecord);
                    break;
                case 6:
                    varietytype.push_back(VarietyType::Funny);
                    break;
                case 7:
                    varietytype.push_back(VarietyType::Interview);
                    break;
                default:
                    break;
                }
            }
            Variety var(name,introduction,re,post,actors,directors,varietytype,recom,atoi(esd.c_str()));
//            var.save(m_varieties);
            if(m_varieties.find(name) != m_varieties.end()){
                m_varieties.erase(name);
                var.save(m_varieties);
                 sql="update VarietyShow set type = '"+type+"',region = '"+region+"',director = '"+director+"',actor = '"+actor+"',post ='"+image+"',introduction ='"+introduction+"',recommend = '"+rec+"',episodes = '"+ esd+"' where name = '"+name+"';";
            }else{
                var.save(m_varieties);
                sql = "insert into VarietyShow(name,type,episodes,region,director,actor,post,introduction,recommend) values('"+name+"','"+type+"','"+esd+"','"+region+"','"+director+"','"+actor+"','"+image+"','"+introduction+"','"+rec+"');";
            }

        }

        if(mysql_query(mysql,sql.data())){
            std::cout <<"insert failed"<< std::endl;
            return false;
        }else{
            std::cout <<"insert successed"<< std::endl;

        }
    }
    return true;
}
bool MovieAndTelevisionBroker::delect(std::string name, std::string type)
{
    std::vector<std::string> videos;
    splictString(name,videos,"/");

    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "Database connect failed" << std::endl;
    }else{
        std::cout << "Database connect Successed" << std::endl;
    }
    std::string sql;

    if("电影" == type){
        for(int i =0;i < videos.size();i++){
            auto it = m_films.find(videos[i]);
            if(it != m_films.end()){
                m_films.erase(it);
            }
            sql = "DELETE FROM Film WHERE name = '"+videos[i]+"';" ;
            if(mysql_query(mysql,sql.data())){
                std::cout <<"insert failed"<< std::endl;
                return false;
            }else{
                cout <<"delect sucessed!"<< endl;
            }
        }

    }else if("动漫"== type){

        for(int i =0;i < videos.size();i++){
            auto it = m_comics.find(videos[i]);
            if(it != m_comics.end()){
                m_comics.erase(it);
            }
            sql = "DELETE FROM Comic WHERE name = '"+videos[i]+"';" ;
            if(mysql_query(mysql,sql.data())){
                std::cout <<"insert failed"<< std::endl;
                return false;
            }else{
                cout <<"delect sucessed!"<< endl;
            }
        }
//        sql = "DELETE FROM Comic WHERE name = '"+name +"';";
    }else if("剧集"== type){
        for(int i =0;i < videos.size();i++){
            auto it = m_dramas.find(videos[i]);
            if(it != m_dramas.end()){
                m_dramas.erase(it);
            }
            sql = "DELETE FROM Drama WHERE name = '"+videos[i]+"';" ;
            if(mysql_query(mysql,sql.data())){
                std::cout <<"insert failed"<< std::endl;
                return false;
            }else{
                cout <<"delect sucessed!"<< endl;
            }
        }
//        sql = "DELETE FROM Drama WHERE name = '"+name +"';";
    }else if("综艺"== type){
        for(int i =0;i < videos.size();i++){
            auto it = m_varieties.find(videos[i]);
            if(it != m_varieties.end()){
                m_varieties.erase(it);
            }
            sql = "DELETE FROM VarietyShow WHERE name = '"+videos[i]+"';" ;
            if(mysql_query(mysql,sql.data())){
                std::cout <<"insert failed"<< std::endl;
                return false;
            }else{
                cout <<"delect sucessed!"<< endl;
            }
        }
//        sql = "DELETE FROM VarietyShow WHERE name = '"+name +"';";
    }


    return true;
//    sql = "DELETE FROM " + table + " WHERE"
}

std::vector<std::string> MovieAndTelevisionBroker::dealType(std::string type)
{
    std::vector<std::string> s;
    std::vector<std::string> videos;
    splictString(type,videos,"，");
    for(int i = 0;i < videos.size();i++){
        if(videos[i] == "机战"||videos[i] =="古装"||videos[i] =="武侠"||videos[i] =="真人秀"){
            s.push_back("1");
        }else if(videos[i] == "青春"||videos[i] =="悬疑"||videos[i] =="悬疑"||videos[i] =="选秀"){
            s.push_back("2");
        }else if(videos[i] == "格斗"||videos[i] =="武侠"||videos[i] =="喜剧"||videos[i] =="美食"){
            s.push_back("3");
        }else if(videos[i] == "恋爱"||videos[i] =="都市"||videos[i] =="动作"||videos[i] =="旅游"){
            s.push_back("4");
        }else if(videos[i] == "美少女"||videos[i] =="历史"||videos[i] =="爱情"||videos[i] =="纪实"){
            s.push_back("5");
        }else if(videos[i] == "热血"||videos[i] =="偶像"||videos[i] =="动画"||videos[i] =="搞笑"){
            s.push_back("6");
        }else if(videos[i] == "校园"||videos[i] =="家庭"||videos[i] =="惊悚"||videos[i] =="访谈"){
            s.push_back("7");
        }else if (videos[i] == "科幻"||videos[i] =="科幻") {
            s.push_back("8");
        }
    }

    return s;
}

Region MovieAndTelevisionBroker::dealRegion(std::string &region)
{
    Region r = Region::China;
        if(region == "中国"){
            r = Region::China;
            region = "1";
            return r;
        }else if(region == "美国"){
            r = Region::American;
            region = "2";
            return r;
        }else if(region == "韩国"){
            r = Region::Korea;
            region = "3";
            return r;
        }else if(region == "印度"){
            r = Region::India;
            region = "4";
            return r;
        }else if(region == "泰国"){
            r = Region::THailand;
            region = "5";
            return r;
        }else if(region == "英国"){
            r = Region::Britain;
            region = "6";
            return r;
        }else if(region == "日本"){
            r = Region::Japan;
            region = "7";
            return r;
        }
        return r;
}

std::vector<Actor *> MovieAndTelevisionBroker::dealActor(std::string actor)
{
    std::vector<std::string> actorVector;
    splictString(actor,actorVector,"，");
    std::vector<Actor *> actors;
    actors = m_actorBroker->findActor(actorVector);
    return actors;
}

std::vector<Director *> MovieAndTelevisionBroker::dealDirector(std::string director)
{
    std::vector<std::string> directorVector;
    splictString(director,directorVector,"，");
    std::vector<Director *> directors;
    directors = m_directorBroker->findDirector(directorVector);
    return directors;
}

std::vector<std::string> MovieAndTelevisionBroker::dealPost(std::string image)
{
    std::vector<std::string> postVector;
    splictString(image,postVector,"，");
    return postVector;
}

std::vector<int> MovieAndTelevisionBroker::dealRecommends(std::string recommend)
{
    std::vector<std::string> recommendVector;
    splictString(recommend,recommendVector,"，");
    std::vector<int> rec;
    for(auto s:recommendVector){
        rec.push_back( atoi(s.c_str()));
    }
    return rec;
}

//std::string MovieAndTelevisionBroker::dealRegion(std::string region, Region &r)
//{
//    if(region == "中国"){
//        r = Region::China;
//        return "1";
//    }else if(region == "美国"){
//        r = Region::American;
//        return "2";
//    }else if(region == "韩国"){
//        r = Region::Korea;
//        return "3";
//    }else if(region == "印度"){
//        r = Region::India;
//        return "4";
//    }else if(region == "泰国"){
//        r = Region::THailand;
//        return "5";
//    }else if(region == "英国"){
//        r = Region::Britain;
//        return "6";
//    }else if(region == "日本"){
//        r = Region::Japan;
//        return "7";
//    }
//}


