#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "tsfilereader.h"
#include "socket.h"
#include <unistd.h>
#include "threadpool.h"

#define MAX_MEDIA_NUM 1
#define Sleep( X ) usleep( 1000*X )

struct RtpTcpHeader
{
    int8_t	dollar;
    int8_t	channel;
    int16_t	len;
};

struct RtpHeader
{
    /* byte 0 */
    uint8_t csrcLen: 4;  			// CSRC count
    uint8_t extension: 1;   			// header extend
    uint8_t padding: 1;   			// padding flag
    uint8_t version : 2;		// version

    /* byte 1 */
    uint8_t payloadType: 7;		// payload type
    uint8_t marker: 1;				// mark bit

    /* bytes 2,3 */
    uint16_t seq;				// sequence number;
    /* bytes 4-7 */
    uint32_t timestamp;				// timestamp
    /* bytes 8-11 */
    uint32_t ssrc;				// sync source
};

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
    void rtpSendFrame();

    int getMediaInfo(int mediaIndex, MediaInfo& mediaInfo);
    int play(Socket* sock, int rtp_ch);
    int preparePlay(int startSec,int endSec);
    int pause();

    uint64_t getCurrentUs(); //获取系统运行至此时的微秒时间
    uint64_t getCurrentMs(); //获取系统运行至此时的毫秒时间
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

    ThreadPool *threadpool;
};

#endif // DATASOURCE_H
