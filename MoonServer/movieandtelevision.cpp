#include "movieandtelevision.h"
#include "advert.h"

MovieAndTelevision::MovieAndTelevision()
{

}

void MovieAndTelevision::searchInfo(std::vector<std::string> &vec)
{
    vec.push_back(m_name);
    vec.push_back(m_post[0]);
    vec.push_back(m_introduction);
    vec.push_back(std::to_string(m_episode));
}

bool MovieAndTelevision::isSame(std::string n)
{
    if(m_name == n)
        return true;
    else
        return false;
}

void MovieAndTelevision::showInfo(std::vector<std::string> &a_collections)
{
    a_collections.push_back(m_name);
    a_collections.push_back(m_post[0]);
}

void MovieAndTelevision::addAdvertLink(Advert *a)
{
    int flag = 0;
    for(auto &item:m_adverts){
        if(item->theSame(a) == true){
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        m_adverts.push_back(a);
    }

    //    std::cout << "Now:" << m_name << " Adverts:" << m_adverts.size() << std::endl;
    //    for(auto &a:m_adverts){
    //        a->print();
    //    }
}

std::vector<Advert *> MovieAndTelevision::showAdvertLink()
{
    //    std::cout << "this is size:" << m_adverts.size() << std::endl;
    return m_adverts;
}

bool MovieAndTelevision::deleteAdvertLink(std::string advertname)
{
    for(auto item = m_adverts.begin(); item != m_adverts.end(); ++item){
        if((*item)->theSameName(advertname) == true){
            item = m_adverts.erase(item);
            return true;
        }
    }
    return false;
}
