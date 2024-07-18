#include "stringUtil.h"
#include "fileHelper.h"

bool StringUtil::compare(const char *src, const char *dest, unsigned int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (*(src++) != *(dest++))
        {
            return false;
        }
    }
    return true;
}

std::string StringUtil::extactFullFileName(const std::string &path)
{
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        return path; // 文件路径中没有目录分隔符，直接返回整个字符串
    }
    return path.substr(pos + 1);
}

std::string StringUtil::extractFileName(const std::string &fullFileName)
{
    size_t pos = fullFileName.find_last_of('.');
    if (pos == std::string::npos)
    {
        return fullFileName;
    }
    return fullFileName.substr(0, fullFileName.size() - pos);
}

std::string StringUtil::extractFileStuffix(const std::string &path)
{
    size_t pos = path.find_last_of('.');
    if (pos == std::string::npos)
    {
        return path;
    }
    return path.substr(pos + 1);
}

std::string StringUtil::extractFileFolder(const std::string &path)
{
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        return path; // 文件路径中没有目录分隔符，直接返回整个字符串
    }
    return path.substr(0, pos);
}

std::string StringUtil::getUniqueFilePath(const std::string &folder, const std::string &fileName, const std::string &suffix)
{
    std::string newPath = folder + "/" + fileName + "." + suffix;

    int index = 0;
    while (FileHelper::checkFileExistence(newPath))
    {
        index += 1;
        newPath = folder + "/" + fileName + "(" + std::to_string(index) + ")." + suffix;
    }

    return newPath;
}