#ifndef RTSPSESSION_H
#define RTSPSESSION_H

#include "tcpsocket.h"
#include "datasource.h"

#define MAX_BUFFER_LEN 1024 * 4

typedef enum{
    RTSP_OPTIONS = 0,
    RTSP_DESCRIBE = 1,
    RTSP_SETUP = 2,
    RTSP_PLAY = 3,
    RTSP_PAUSE = 4,
    RTSP_TEARDOWN = 5,
    RTSP_SET_PARAMETER = 6,
    RTSP_GET_PARAMETER = 7,
    RTSP_METHOD_MAX
}RtspMethod;

struct RtspMethodStr{
    int method;
    const char* method_str;
};

extern const RtspMethodStr methods[RTSP_METHOD_MAX];

struct RtspCode{
    int code;
    const char* code_str;
};

extern const RtspCode codes[15];

class RtspSession
{
public:
    RtspSession();

    void processSession(int fd);
    int reciveData();
    int handleData();
    int parseDataLen(const char* data, int len);    //解析消息长度
    void printClientCmd(const char* data, int len);    //打印客户端命令
    int handleCommand(const char* data, int len);   //处理命令
    void parseData(const char* data, int len, char *method);

    static char* getLineFromBuf(char* buf, char* line);
    int sendMessage(const char* data, int len);

    uint64_t getCurrentUs(); //获取系统运行至此时的微秒时间

private:
    RtspMethod parseMethod(const char* data);    //解析方法
    int handleCmd_OPTIONS();
    int handleCmd_SETUP(const char* data, int len);
    int handleCmd_DESCRIBE(const char* data, int len);
    int handleCmd_PLAY(const char* data, int len);
    void codeMessage(char* result, int code);

    TcpSocket m_sock;
    DataSource m_dataSource;
    char m_recvBuff[MAX_BUFFER_LEN];
    uint32_t m_recv_len;

    int m_cseq;  //序列号
    int m_rtspChannel;  //RTP OVER TCP时的通道
    char m_url[256];   //Rtsp地址
    char m_session[128];
};

#endif // RTSPSESSION_H
