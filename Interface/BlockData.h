#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include <array>

struct Block_t
{
    Block_t(const char *buf, const long int nSize);
    std::string strBuffer;
    long long        nPts = 0;
    long long        nDts = 0;
    long long        nDuration = 0;//时长
};

#endif // BLOCKDATA_H
