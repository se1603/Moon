#include "udpsocket.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

UdpSocket::UdpSocket()
{
    memset(&m_remoteAddr,0,sizeof (m_remoteAddr));
}

UdpSocket::~UdpSocket()
{

}

int UdpSocket::openSocket(const char *ip, int port)
{
    if(Socket::openSocket(SOCK_DGRAM) < 0)
        return -1;

    struct in_addr addr;
    addr.s_addr = inet_addr(ip);
    if(addr.s_addr == INADDR_NONE)
    {
        printf("inet_addr failed. Errorn info: %s\n",strerror(errno));
        closeSocket();
        return -1;
    }

    int bindRet = -1;
    uint32_t ip_host = ntohl(addr.s_addr);

    //设置多播
    if(ip_host >= 0xe0000000 && ip_host < 0xf0000000)
    {
        struct ip_mreq mul_ip_mreq;
        memcpy(&(mul_ip_mreq.imr_multiaddr), &addr.s_addr, sizeof (struct in_addr));
        mul_ip_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if(setsockopt(m_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&mul_ip_mreq, sizeof(struct ip_mreq) ) < 0)
        {
            closeSocket();
            printf("setsockopt IP_ADD_MEMBERSHIP failed, %s\n",strerror(errno));
            return -1;
        }
        bindRet = bindSocket("0.0.0.0",port);
    }

    bindRet = bindSocket(ip,port);
    if(bindRet < 0)
    {
        closeSocket();
        return -1;
    }
    return 0;
}

int UdpSocket::setRemote(const char *ip, int port)
{
    return getAddr(ip,port,m_remoteAddr);
}

int UdpSocket::send(const char *buf, int len)
{
    if(buf == NULL || len <= 0)
        return -1;
    int ret = sendto(m_fd, buf, len, 0, (sockaddr*)&m_remoteAddr, sizeof(m_remoteAddr));
    if(ret < 0)
    {
        if(errno == EWOULDBLOCK || errno == EINTR || errno == EWOULDBLOCK)
            return 0;
        return -1;
    }
    return ret;
}

int UdpSocket::recive(char *buf, int len)
{
    int ret = -1;
    struct sockaddr_in tmp_addr;
    socklen_t addr_len = sizeof( tmp_addr );
    ret = ::recvfrom(m_fd, buf, len, 0, (sockaddr *)&tmp_addr, &addr_len);
    if( ret < 0 )
    {
        if(errno == EWOULDBLOCK || errno == EINTR || errno == EWOULDBLOCK)
            return 0;
        return -1;
    }
    return ret;
}

int UdpSocket::setMulticastTTL(uint8_t TTL)
{
    if(setsockopt( m_fd, SOL_IP, IP_MULTICAST_TTL, (char *)&TTL, sizeof(TTL) ) < 0)
    {
        printf("IP_MULTICAST_TTL failed, %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int UdpSocket::setMulticastLoop(bool isloop)
{
    int loop = (isloop == true ? 1 : 0);
    if(setsockopt( m_fd, SOL_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop) ) < 0)
    {
        printf("IP_MULTICAST_LOOP failed, %s\n", strerror(errno));
        return -1;
    }
    return 0;
}
