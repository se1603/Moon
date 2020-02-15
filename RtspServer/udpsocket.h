#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "socket.h"

class UdpSocket : public Socket
{
public:
    UdpSocket();
    ~UdpSocket();

    int openSocket(const char *ip,int port);
    int setRemote(const char* ip, int port);
    int send(const char *buf, int len);
    int recive(char *buf, int len);

    int setMulticastTTL( uint8_t TTL ); //设置多播发送报文的TTL,返回值： -1 失败 0 成功
    int setMulticastLoop( bool isloop ); //设置是否禁止组播数据回送，true-回送，false-不回送。返回值: -1 失败 0 成功

private:
    struct sockaddr_in m_remoteAddr;
};

#endif // UDPSOCKET_H
