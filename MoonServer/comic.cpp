#include "comic.h"

Comic::Comic(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<Actor *> actors, std::vector<Director *> directors, std::vector<ComicType> types, int episode, std::vector<int> recommends)
{
    m_name = name;
    m_introduction = introduction;
    m_region = region;
    m_post = posts;
    m_actors = actors;
    m_director = directors;
    m_type = types;
    m_recommend = recommends;
    m_episode = episode;
}

std::vector<std::string> Comic::show(bool recommend)
{
    std::vector<std::string> showcomic;

    showcomic.push_back(m_name);
    if(recommend)
        showcomic.push_back(m_post[1]);
    else {
        showcomic.push_back(m_post[0]);
    }
    return  showcomic;
}

void Comic::findComicByType(ComicType type, std::vector<Comic> &comics)
{
    for(auto t : m_type)
    {
        if(t == type)
            comics.push_back(*this);
    }
}

void Comic::findComicByRecommend(int recommend, std::vector<Comic> &comics)
{
    for(auto c:m_recommend){
        if(c == recommend){
            comics.push_back(*this);
        }
    }
}

void Comic::recodeInfo(std::string name, std::vector<std::string> &v)
{
    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        v.push_back(m_introduction);
        v.push_back("3");
        auto regin = m_region;
        switch(regin){
        case Region::American:{
            v.push_back("美国");
            break;
        }
        case Region::Britain:{
            v.push_back("英国");
            break;
        }
        case Region::China:{
            v.push_back("中国");
            break;
        }
        case Region::India:{
            v.push_back("印度");
            break;
        }
        case Region::Korea:{
            v.push_back("韩国");
            break;
        }
        case Region::THailand:{
            v.push_back("泰国");
            break;
        }
        case Region::Japan:{
            v.push_back("日本");
            break;
        }
        default:break;
        }
        v.push_back(m_post[0]);
        for(auto t: m_type){
            if(t == ComicType::Campus){
                v.push_back("校园");
            }
            if(t == ComicType::WarmBlood){
                v.push_back("热血");
            }
            if(t== ComicType::RobotWars){
                 v.push_back("机战");
            }
            if(t== ComicType::Kayoing){
                v.push_back("美少女");
            }
            if(t == ComicType::Combat){
                v.push_back("格斗");
            }
            if(t == ComicType::Love){
                 v.push_back("恋爱");
            }
            if(t == ComicType::Youth){
                v.push_back("青春");
            }
            if(t == ComicType::WarmBlood){
                v.push_back("热血");
            }
        }
    }else{
        return;
    }
}
void Comic::getActorInfo(std::string name, std::vector<std::string> &v)
{
    std::vector<std::string> resource;

    auto a = m_actors;
    for(int i = 0;i != a.size();i++){
        auto tem = a[i];
        tem->actorInfo(resource);
    }

    auto d = m_director;
    for(int i = 0;i != d.size();i++){
        auto tem = d[i];
        tem->directorInfo(resource);
    }
    v = resource;
}
bool Comic::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Comic::save(std::map<std::string, Comic> &comics)
{
    comics[m_name] = *this;
}

void Comic::showPost(std::string &post)
{
    post = m_post[0];
}
void Comic::showIntrodution(std::string &in)
{
    in = m_introduction;
}
std::vector<Director *> Comic::showDirector()
{
    return m_director;
}

std::vector<Actor *> Comic::showActor()
{
    return m_actors;
}

bool Comic::findByTypeName(std::string type)
{
    std::string t;
    if(m_type[0] == ComicType::Love){
        t = "恋爱";
    }else if(m_type[0] == ComicType::Youth){
        t = "青春";
    }else if(m_type[0] == ComicType::Campus){
        t = "校园";
    }else if(m_type[0] == ComicType::Combat){
        t = "格斗";
    }else if(m_type[0] == ComicType::Kayoing){
        t = "美少女";
    }else if(m_type[0] == ComicType::RobotWars){
        t = "机战";
    }else if(m_type[0] == ComicType::WarmBlood){
        t = "热血";
    }

    if(t == type)
        return true;
    else
        return false;
}
