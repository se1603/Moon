/* Author:董梦丹
* Date:2019-11-29
* Note:用户
*/
#ifndef AUDIENCE_H
#define AUDIENCE_H
#include "collection.h"
#include "record.h"
#include <map>

class Audience
{
public:
    Audience(std::string name,std::string password,std::string avatar,
             std::vector<Collection> collections,
             std::vector<Record> records);
    Audience(std::string name);
    Audience();

    bool verifyLogin(std::string name);
    bool verifyName(std::string name);
    bool verifyPassword(std::string password);

    void show(std::vector<std::string> &audienceinfo);
    void showname(std::vector<std::string> &a);
    void addCollection(Collection c);
    void addRecord(Record r);
    void showCollection(std::multimap<std::string, MovieAndTelevision *> &collectionmap);
    void showRecord(std::multimap<std::string, MovieAndTelevision *> &recordmap);
    bool judgeRecord(std::string recordname);
    void changeRecord(std::string recordname, std::string startPlayTime,
                      std::string duration);
private:
    std::string m_name;
    std::string m_password;
    std::string m_avatar;

    std::vector<Collection> m_collections;
    std::vector<Record> m_records;
};

#endif // AUDIENCE_H
