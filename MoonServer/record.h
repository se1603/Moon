/* Author:董梦丹
* Date:2019-11-29
* Note:历史记录
*/
#ifndef RECORD_H
#define RECORD_H
#include "movieandtelevision.h"

class Audience;
class Record
{
    friend class Audience;
public:
    Record(std::string startPlayTime, std::string duration, Audience* a, MovieAndTelevision* m);

    void showRecord(std::vector<std::string> &a_record);
    void showAllInfo(std::vector<std::string> &r);
    void changeInfo(std::string startTime, std::string duration);
    bool verifyName(std::string r);
private:
    std::string m_startPlayTime;
    std::string m_duration;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // RECORD_H
