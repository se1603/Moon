#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "tsfilereader.h"
#include "socket.h"

#define MAX_MEDIA_NUM 1

class DataSource
{
public:
    DataSource();

    struct MediaInfo{
        char track_id[32];
        uint16_t seq;
        uint32_t rtp_time;
        uint32_t ssrc;
    };

    int init(const char* fileName);
    const char* getSdp();
    int getRange();
    int getMediaNum();

    int getMediaInfo(int mediaIndex, MediaInfo& mediaInfo);
    int play(Socket* sock, int rtp_ch);
    int preparePlay(int startSec,int endSec);
    int pause();

private:
    char m_sdp[1024 * 2];
    int m_range;
    int m_mediaNum;

    MediaInfo m_media_info[MAX_MEDIA_NUM];
    int m_start_sec;   //起始秒
    int m_end_sec;   //结束秒

    int m_rtp_ch;    //rtp_ch < 0 RTP OVER UDP; rtp_ch >= 0 RTP OVER RTSP

    TsFileReader m_reader;
    Socket *m_sock;

    uint64_t m_start_pcr;  //起始时间戳
    uint64_t m_start_ms;
    uint64_t m_last_pcr;   //结束时间戳
};

#endif // DATASOURCE_H
