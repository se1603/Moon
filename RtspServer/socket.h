#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>

#define INVALID_SOCKET_FD -1

class Socket
{
public:
    Socket();
    virtual ~Socket();

    void closeSocket(); //关闭套接字
    int getFd() const; //获取套接字描述符
    int attachFd(int fd);  //绑定套接字描述符,0成功，-1失败
    int detachFd();  //解除绑定，返回之前绑定的ID

    virtual int send(const char* buf, int len) {return  -1;}  //发送消息
    virtual int recive(char *buf, int len) {return -1;} //接受消息

protected:
    int openSocket(int socketType);
    int bindSocket(const char *ip, int port);
    int getAddr(const char* ip, int port, sockaddr_in& addr);
    int setBlock(bool isBlock);  //设置套接字描述符阻塞
    int setAddrReuse();   //避免突然中断重启时 地址占用

    int m_fd;  //套接字描述符
};

#endif // SOCKET_H
