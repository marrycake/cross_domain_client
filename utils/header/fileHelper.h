#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QString>
#include <string>
#include <vector>

#include "arrayScope.h"

class FileHelper {
 public:
  static void writeToFile(const char *msg, int len, const std::string &path,
                          bool append = false);
  static void writeToFile(const std::string &msg, const std::string &path,
                          bool append = false);
  static bool checkFileExistence(const std::string &filePath);
  static bool checkFileExistence(const QString &filePath);
  static ArrayScope<char> readFile(const std::string &path);
  static unsigned int getFileSize(const std::string &path);
  static std::vector<char> readLastNBytes(const std::string &filename, int n);
  static std::vector<char> readBytesFromPosition(const std::string &filePath,
                                                 std::streampos position,
                                                 std::size_t numBytes);
  static bool checkDirExist(const QString &dir);
  static void mkdirIfNotExist(const QString &dir);
};

#endif  // FILEHELPER_H