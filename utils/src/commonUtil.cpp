#include "commonUtil.h"

int CommonUtil::byteToInt(char b)
{
    int i = b;
    if (i < 0)
    {
        i += 256;
    }

    return i;
}

void CommonUtil::intToByte(int num, char *result)
{
    result[0] = (num >> 24) & 0xFF;
    result[1] = (num >> 16) & 0xFF;
    result[2] = (num >> 8) & 0xFF;
    result[3] = num & 0xFF;
}

int CommonUtil::bytesToint(char *data)
{
    return (static_cast<unsigned char>(data[0]) << 24) |
           (static_cast<unsigned char>(data[1]) << 16) |
           (static_cast<unsigned char>(data[2]) << 8) |
           (static_cast<unsigned char>(data[3]));
}