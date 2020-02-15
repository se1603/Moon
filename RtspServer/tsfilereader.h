#ifndef TSFILEREADER_H
#define TSFILEREADER_H

#include <stdio.h>
#include "tsparse.h"

#define TSPKTLEN 188

class TsFileReader
{
public:
    TsFileReader();
    ~TsFileReader();

    int openFile(const char* filename);
    int readFile();
    int getFileRange();
    bool seekByTime(uint64_t sec);
    int getTsPKT(char *buf, int len, uint64_t&pcr);

private:
    FILE* m_file;
    char m_dataBuff[TSPKTLEN];
    uint64_t m_fileSize;          //文件大小
    uint64_t m_current_pcr;  //当前读到的位置
    uint64_t m_first_pcr;    //文件起始位置
    uint64_t m_last_pcr;     //文件结束位置
};


#endif // TSFILEREADER_H
