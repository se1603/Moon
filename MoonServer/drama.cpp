#include "drama.h"


Drama::Drama(std::string name, std::string introduction, Region region, std::vector<std::string> posts, std::vector<Actor *> actors, std::vector<Director *> directors, std::vector<DramaType> types, int episode, std::vector<int> recommends)
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

std::vector<std::string> Drama::show(bool recommend)
{
    std::vector<std::string> showDrama;

       showDrama.push_back(m_name);
       if(recommend)
           showDrama.push_back(m_post[1]);
       else {
           showDrama.push_back(m_post[0]);
       }
       return  showDrama;
}

void Drama::findDramaByType(DramaType type, std::vector<Drama> &Dramas)
{
    for(auto t : m_type)
        {
            if(t == type)
                Dramas.push_back(*this);
    }
}

void Drama::findDramaByRecommend(int recommend, std::vector<Drama> &Dramas)
{
    for(auto c:m_recommend){
            if(c == recommend){
                Dramas.push_back(*this);
            }
    }
}

bool Drama::findByName(std::string name)
{
    if(m_name == name){
        return true;
    }else{
        return false;
    }
}

void Drama::recodeInfo(std::string name, std::vector<std::string> &v)
{
    if(m_name == name){
        auto i = std::to_string(m_episode);
        v.push_back(i);
        v.push_back(m_introduction);
        v.push_back("2");
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
            switch(t){
            case DramaType::Family:{
                v.push_back("家庭");
                break;
            }
            case DramaType::MartialArts:{
                v.push_back("武侠");
                break;
            }
            case DramaType::AncientCostume:{
                v.push_back("古装");
                break;
            }
            case DramaType::History:{
                v.push_back("历史");
                break;
            }
            case DramaType::Idol:{
                v.push_back("偶像");
                break;
            }
            case DramaType::Metropolis:{
                v.push_back("都市");
                break;
            }
            case DramaType::Suspense:{
                v.push_back("悬疑");
                break;
            }
            default:v.push_back("科幻");
                break;
            }
        }
    }else{
        return;
    }
}
void Drama::getActorInfo(std::string name, std::vector<std::string> &v)
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
void Drama::save(std::map<std::string, Drama> &Dramas)
{
    Dramas[m_name] = *this;
}

void Drama::showPost(std::string &post)
{
    post = m_post[0];
}

void Drama::showIntrodution(std::string &in)
{
    in = m_introduction;
}
std::vector<Director *> Drama::showDirector()
{
    return m_director;
}

std::vector<Actor *> Drama::showActor()
{
    return m_actors;
}

bool Drama::findByTypeName(std::string type)
{
    std::string t;
    if(m_type[0] == DramaType::Idol){
        t = "偶像";
    }else if(m_type[0] == DramaType::Family){
        t = "家庭";
    }else if(m_type[0] == DramaType::History){
        t = "历史";
    }else if(m_type[0] == DramaType::Suspense){
        t = "悬疑";
    }else if(m_type[0] == DramaType::Metropolis){
        t = "都市";
    }else if(m_type[0] == DramaType::MartialArts){
        t = "武侠";
    }else if(m_type[0] == DramaType::AncientCostume){
        t = "古装";
    }else if(m_type[0] == DramaType::ScienceFiction){
        t = "科幻";
    }

    if(t == type)
        return true;
    else
        return false;
}
