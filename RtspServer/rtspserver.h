#ifndef RTSPSERVER_H
#define RTSPSERVER_H

#include "tcpsocket.h"
#include "threadpool.h"
#include <map>
#include "rtspsession.h"

class RtspServer : public Socket
{
public:
    RtspServer();

    int start(const char *ip, int port);
    int acceptClient(int sockfd, char *ip, int *port);
    void processClient(int fd);

private:
    ThreadPool threadPool;
    std::map<long, RtspSession*> m_sessionMap;
};

#endif // RTSPSERVER_H
