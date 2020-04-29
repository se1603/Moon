#include "advert.h"
#include "movieandtelevision.h"

Advert::Advert(std::string name, std::string company, std::string clicks, std::string duetime)
{
    m_name = name;
    m_company = company;
    m_clicks = clicks;
    m_duetime = duetime;
}

void Advert::showDetails(std::vector<std::string> &vec)
{
    vec.push_back(m_name);
    vec.push_back(m_company);
    vec.push_back(m_clicks);
    vec.push_back(m_duetime);
}

bool Advert::theSame(Advert *a)
{
    if(m_name == a->m_name/* && m_company == a->m_company && m_duetime == a->m_duetime*/){
        return true;
    }else{
        return false;
    }
}

bool Advert::theSameName(std::string name)
{
    if(m_name == name)
        return true;
    else
        return false;
}

bool Advert::sameCompany(std::string companyname)
{
    if(m_company == companyname)
        return true;
    else
        return false;
}

int Advert::showClicks()
{
    return atoi(m_clicks.c_str());
}

void Advert::addVideoLink(MovieAndTelevision* mv)
{
    m_videos.push_back(mv);
//    std::cout << "Now: " << m_name << " " << m_videos.size() << std::endl;
}

bool Advert::deleteVideoLink(std::string videoname)
{
    for(auto item = m_videos.begin(); item != m_videos.end(); ++item){
        if((*item)->isSame(videoname) == true){
            m_videos.erase(item);
            return true;
        }
    }
    return false;
}

bool Advert::isVideoEmpty()
{
    if(m_videos.size() == 0)
        return true;
    else
        return false;
}

void Advert::changetime(std::string newdate)
{
    m_duetime = newdate;
}

//void Advert::print()
//{
//    std::cout << ":" << m_name << m_company << m_clicks << m_duetime << std::endl;
//}
