#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <vector>
class CommonUtil
{
public:
    static int byteToInt(char b);
    static void intToByte(int num, char *result);
    static int bytesToint(char *);
};

#endif // COMMONUTIL_H