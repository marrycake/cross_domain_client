#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string>
class StringUtil
{
public:
    static bool compare(const char *src, const char *dest, unsigned int len);
    static std::string extactFullFileName(const std::string &path);
    static std::string extractFileName(const std::string &fullFileName);
    static std::string extractFileStuffix(const std::string &path);
    static std::string extractFileFolder(const std::string &path);
    static std::string getUniqueFilePath(const std::string &folder, const std::string &fileName, const std::string &suffix);
};

#endif // STRINGUTIL_H