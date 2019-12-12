/* Author:董梦丹
* Date:2019-11-29
* Note:收藏
*/
#ifndef COLLECTION_H
#define COLLECTION_H
#include "movieandtelevision.h"

class Audience;
class Collection
{
    friend class Audience;
public:
    Collection(std::string collecttime,Audience* a,MovieAndTelevision* m);
private:
    std::string m_collectionTime;

    Audience* m_audience;
    MovieAndTelevision* m_movieAndTelevision;
};

#endif // COLLECTION_H
