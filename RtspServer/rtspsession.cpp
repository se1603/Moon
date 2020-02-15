#include "rtspsession.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

const RtspMethodStr methods[RTSP_METHOD_MAX] = {
    {RTSP_OPTIONS, "OPTIONS"},
    {RTSP_DESCRIBE, "DESCRIBE"},
    {RTSP_SETUP, "SETUP"},
    {RTSP_PLAY, "PLAY"},
    {RTSP_PAUSE, "PAUSE"},
    {RTSP_TEARDOWN, "TEARDOWN"},
    {RTSP_SET_PARAMETER, "SET_PARAMETER"},
    {RTSP_GET_PARAMETER, "GET_PARAMETER"},
};

const RtspCode codes[15] = {
    { 200, "OK" },
    { 302, "Moved Temporarily" },
    { 400, "Bad Request" },
    { 401, "Unauthorized" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
    { 405, "Method Not Allowed" },
    { 454, "Session Not Found" },
    { 457, "Invalid Range" },
    { 461, "Unsupported transport" },
    { 500, "Internal Server Error" },
    { 503, "Service Unavailable" },
    { 505, "RTSP Version not supported" },
    { 551, "Option not supported" },
    { 0, NULL }
};

RtspSession::RtspSession()
{
    memset(m_recvBuff, 0, sizeof(m_recvBuff));
    m_recv_len = 0;
    m_cseq = 0;
    m_rtspChannel = 0;
    memset(m_url, 0, sizeof (m_url));
}

void RtspSession::processSession(int fd)
{
    m_sock.attachFd(fd);

    while(m_sock.getFd() > 0)
    {
        if(reciveData() < 0)
        {
            printf("ReciveData failed.\n");
        }
    }
}

int RtspSession::reciveData()
{
    int reciveLen = sizeof(m_recvBuff) - 1 - m_recv_len;
    if(reciveLen <= 0)
    {
        printf("ReciveBuffer have not enough space.\n");
        return -1;
    }
    int ret = m_sock.recive(m_recvBuff + m_recv_len, reciveLen);
    if(ret < 0)
    {
        printf("Recive data failed.\n");
        return -1;
    }
    m_recv_len += ret;
    handleData();

    return 0;
}

int RtspSession::handleData()
{
    char *reciveBuf = m_recvBuff;
    m_recvBuff[m_recv_len] = '\0';

    int ret = -1;
    while(m_recv_len > 0)
    {
        ret = 0;
        if(*reciveBuf == '$')
        {

        }
        else
        {
            int parseLen = parseDataLen(reciveBuf, m_recv_len);
            if(parseLen < 0)
                break;
            printClientCmd(reciveBuf, parseLen);
            if(handleCommand(reciveBuf,parseLen) < 0)
                return -1;
            m_recv_len -= parseLen;
            reciveBuf += parseLen;
        }
    }
    if(m_recv_len > 0)
        memmove(m_recvBuff, reciveBuf,m_recv_len);
    return ret;
}

int RtspSession::parseDataLen(const char *data, int len)
{
    const char* start = data;
    const char* endMark = "\r\n\r\n";
    const char* end = NULL;

    end = strstr(start, endMark);
    if(end == NULL)
        return -1;

    int headerLen = end - start + strlen(endMark);

    int contentLen = 0;
    const char* contentMark = "Content-Length ";
    const char* contentStart = strstr(end,contentMark);
    if(contentStart != NULL && strstr(contentStart,"\r\n") != NULL)
        contentLen = atoi(contentStart + strlen(contentMark));

    if(len < (headerLen + contentLen))
        return -1;

    return (headerLen + contentLen);
}

void RtspSession::printClientCmd(const char *data, int len)
{
    char tmp[1024];
    memset(tmp,0,sizeof (tmp));
    memcpy(tmp,data, len > (int)sizeof(tmp) - 1 ? (int)sizeof(tmp) - 1 : len);
    printf("---------------C->S--------------\n");
    printf("%s", tmp);
}

RtspMethod RtspSession::parseMethod(const char *data)
{
    RtspMethod rtsp_method = RTSP_METHOD_MAX;
    if( *data == 'O' && strncmp( data, methods[RTSP_OPTIONS].method_str, strlen(methods[RTSP_OPTIONS].method_str) ) == 0 )
        rtsp_method = RTSP_OPTIONS;
    else if( *data == 'D' && strncmp( data, methods[RTSP_DESCRIBE].method_str, strlen(methods[RTSP_DESCRIBE].method_str) ) == 0 )
        rtsp_method = RTSP_DESCRIBE;
    else if( *data == 'S' && strncmp( data, methods[RTSP_SETUP].method_str, strlen(methods[RTSP_SETUP].method_str) ) == 0 )
        rtsp_method = RTSP_SETUP;
    else if( *data == 'P' && strncmp( data, methods[RTSP_PLAY].method_str, strlen(methods[RTSP_PLAY].method_str) ) == 0 )
        rtsp_method = RTSP_PLAY;
    else if( *data == 'P' && strncmp( data, methods[RTSP_PAUSE].method_str, strlen(methods[RTSP_PAUSE].method_str) ) == 0 )
        rtsp_method = RTSP_PAUSE;
    else if( *data == 'T' && strncmp( data, methods[RTSP_TEARDOWN].method_str, strlen(methods[RTSP_TEARDOWN].method_str) ) == 0 )
        rtsp_method = RTSP_TEARDOWN;
    else if( *data == 'S' && strncmp( data, methods[RTSP_SET_PARAMETER].method_str, strlen(methods[RTSP_SET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_SET_PARAMETER;
    else if( *data == 'G' && strncmp( data, methods[RTSP_GET_PARAMETER].method_str, strlen(methods[RTSP_GET_PARAMETER].method_str) ) == 0 )
        rtsp_method = RTSP_GET_PARAMETER;
    return rtsp_method;
}

void RtspSession::codeMessage(char *result, int code)
{
    int i = 0;
    for(; ; i++)
    {
        if(code == codes[i].code)
            break;
        else if(codes[i].code == 0)
        {
            i = 2;
            break;
        }
    }

    sprintf(result,"RTSP/1.0 %d %s\r\n"
                   "CSeq: %d\r\n",
            codes[i].code,codes[i].code_str,m_cseq);
}

int RtspSession::handleCmd_OPTIONS()
{
    char sendBuff[512];
    codeMessage(sendBuff,200);

    char result[512];
    sprintf(result,
            "Public: OPTIONS, DESCRIBE, SETUP, PLAY\r\n"
            "\r\n");
    strcat(sendBuff,result);
    return sendMessage(sendBuff,strlen(sendBuff));
}

int RtspSession::handleCmd_SETUP(const char *data, int len)
{
    char sendBuf[512];
    if(strstr(data, "RTP/AVP/TCP") == NULL)
    {
        codeMessage(sendBuf,461);
        char result[512];
        sprintf(result,
                "\r\n");
        strcat(sendBuf,result);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    const char* interleaved = strstr(data, "interleaved=");
    if(interleaved == NULL)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    m_rtspChannel = atoi(interleaved + strlen("interleaved="));

    if(m_rtspChannel < 0)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    snprintf(m_session, sizeof(m_session), "Session: %X\r\n",(uint64_t)getCurrentUs());
    codeMessage(sendBuf,200);
    char result[512];
    snprintf(result, sizeof(result),
             "%s"
             "Transport: RTP/AVP/TCP;unicast;interleaved=%d-%d\r\n\r\n",
              m_session, m_rtspChannel, m_rtspChannel + 1);
    strcat(sendBuf,result);
    return sendMessage(sendBuf,strlen(sendBuf));
}

int RtspSession::handleCmd_DESCRIBE(const char *data, int len)
{
    char sendBuf[512];
    if(strstr(m_url, "rtsp://") == NULL)
    {
        codeMessage(sendBuf,400);
        return sendMessage(sendBuf,strlen(sendBuf));
    }

    char *fileName = strstr(strstr(m_url,"rtsp://") + strlen("rtsp://"), "/") + 1;
    if(m_dataSource.init(fileName) < 0)
    {
        codeMessage(sendBuf,404);
        return sendMessage(sendBuf,strlen(sendBuf));
    }
    const char* sdp = m_dataSource.getSdp();

    codeMessage(sendBuf,200);
    char result[512];

    sprintf(result, "Content-Base: %s\r\n"
                    "Content-type: application/sdp\r\n"
                    "Content-length: %d\r\n\r\n"
                    "%s",
            m_url,
            strlen(sdp),
            sdp);
    strcat(sendBuf,result);
    return sendMessage(sendBuf,strlen(sendBuf));
}

int RtspSession::handleCmd_PLAY(const char *data, int len)
{
    int range = m_dataSource.getRange();
    int startSec = 0;
    int endSec = range;

    const char* rangeStr = strstr(data, "Range: npt=");
    if(rangeStr != NULL)
    {
        startSec = atoi(rangeStr + strlen("Range: npt="));
        const char* endSecPos = strstr(rangeStr + strlen("Range: npt="),"-");
        if(endSecPos != NULL)
        {
            int sec = atoi(endSecPos + 1);
            if(sec != 0)
                endSec = sec;
        }
    }
    m_dataSource.preparePlay(startSec,endSec);
    DataSource::MediaInfo mediaInfo;
    m_dataSource.getMediaInfo(0,mediaInfo);
    char sendBuf[512];
    codeMessage(sendBuf,200);
    char result[512];
    snprintf(result, sizeof (result),
             "Range: npt=%d.000-%d.000\r\n"
             "RTP-Info: url=%s/%s;seq=%d;rtptime=%u\r\n\r\n",
             startSec,endSec,m_url,mediaInfo.track_id,mediaInfo.seq,mediaInfo.rtp_time);
    strcat(sendBuf,result);
    return sendMessage(sendBuf,strlen(sendBuf));
}

int RtspSession::handleCommand(const char *data, int len)
{
    char method[40];
    parseData(data,len,method);
    RtspMethod rMethod = parseMethod(data);

    if( rMethod == RTSP_METHOD_MAX ){
        printf("Unsupported this method.\n");
        return -1;
    }

    switch(rMethod){
    case RTSP_OPTIONS:
        return handleCmd_OPTIONS();
    case RTSP_SETUP:
        return handleCmd_SETUP(data,len);
    case RTSP_DESCRIBE:
        return handleCmd_DESCRIBE(data,len);
    case RTSP_PLAY:
        return handleCmd_PLAY(data,len);
    }
    return 0;
}

void RtspSession::parseData(const char *data, int len, char *method)
{
    char tmpbuf[1024];
    int i = 0;
    for(; i < len; ++i)
    {
        tmpbuf[i] = data[i];
    }

    char *tmp;
    char line[512];
    char version[40];

    /* 解析方法 */
    tmp = getLineFromBuf(tmpbuf, line);
    if(sscanf(line, "%s %s %s\r\n", method, m_url, version) != 3)
    {
        printf("parse first line err.\n");
    }

    /* 解析序列号 */
    tmp = getLineFromBuf(tmp, line);
    if(sscanf(line, "CSeq: %d\r\n", &m_cseq) != 1)
    {
        printf("parse second line err.\n");
    }
}

char *RtspSession::getLineFromBuf(char *buf, char *line)
{
    while(*buf != '\n')
    {
        *line = *buf;
        line++;
        buf++;
    }

    *line = '\n';
    ++line;
    *line = '\0';

    ++buf;
    return buf;
}

int RtspSession::sendMessage(const char *data, int len)
{
    printf("---------------S->C--------------\n");
    printf("%s", data);
    m_sock.send(data,len);
}

uint64_t RtspSession::getCurrentUs()
{
    struct timeval cur_time;
    gettimeofday( &cur_time, NULL );
    return cur_time.tv_sec*1000000+cur_time.tv_usec;
}
