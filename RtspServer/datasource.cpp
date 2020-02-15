#include "datasource.h"
#include <string.h>

DataSource::DataSource()
{
    memset(m_sdp, 0, sizeof (m_sdp));
    m_range = 0;
    m_mediaNum = MAX_MEDIA_NUM;
    memset(m_media_info, 0, sizeof (m_media_info));
    m_start_sec = 0;
    m_end_sec = 0;
    m_sock = NULL;
    m_rtp_ch = 0;
    m_start_pcr = -1;
    m_start_ms = -1;
    m_last_pcr = -1;
}

int DataSource::init(const char *fileName)
{
    if(m_reader.openFile(fileName) < 0)
        return -1;
    m_range = m_reader.getFileRange();
    m_end_sec = m_range;
    strncpy(m_media_info[0].track_id, "track1", sizeof (m_media_info[0].track_id));
    snprintf(m_sdp,sizeof (m_sdp),
             "v=0\r\n"
             "o=- 0 1 IN IP4 0.0.0.0\r\n"
             "s=RTSP Server\r\n"
             "i=%s\r\n"
             "t=0 0\r\n"
             "a=control:*\r\n"
             "a=range:npt=0-%d\r\n"
             "m=video 0 RTP/AVP 33\r\n"
             "a=control:%s\r\n",
             fileName,m_range,m_media_info[0].track_id);
    return 0;
}

const char *DataSource::getSdp()
{
    return m_sdp;
}

int DataSource::getRange()
{
    return m_range;
}

int DataSource::getMediaNum()
{
    return m_mediaNum;
}

int DataSource::getMediaInfo(int mediaIndex, DataSource::MediaInfo &mediaInfo)
{
    if(mediaIndex >= m_mediaNum)
        return -1;
    mediaInfo = m_media_info[mediaIndex];
    return 0;
}

int DataSource::play(Socket *sock, int rtp_ch)
{
    m_sock = sock;
    m_rtp_ch = rtp_ch;
    return 0;
}

int DataSource::preparePlay(int startSec, int endSec)
{
    if(endSec != -1 && endSec <= m_range)
        m_end_sec = startSec;
    if(startSec != -1 && startSec < m_end_sec)
    {
        m_start_sec = startSec;
        m_reader.seekByTime(m_start_sec);
    }
    return 0;
}

int DataSource::pause()
{
    m_sock = NULL;
    return 0;
}
