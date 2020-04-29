/*
 * Author:guchangrong   2016051604218
 * data:2020-3-12
 * 管理用户初始化
 */
#include "manageuser.h"

ManageUser::ManageUser(std::string id, std::string informer, std::string bereported, std::string comment, std::string date, std::string informcount, std::string informmark)
{
    m_id =id;
    m_informer = informer;
    m_bereported = bereported;
    m_comment = comment;
    m_date = date;
    m_informcount = informcount;
    m_informmark = informmark;
}

void ManageUser::manageUserInfo(std::vector<std::string> &v)
{
    v.push_back(m_id);
    v.push_back(m_informer);
    v.push_back(m_bereported);
    v.push_back(m_comment);
    v.push_back(m_date);
    v.push_back(m_informcount);
    v.push_back(m_informmark);
}

bool ManageUser::findbByInformmark(std::string informmark)
{
   if(m_informmark == informmark){
       return true;
   } else {
       return false;
   }
}
