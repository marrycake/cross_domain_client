#include "fileHelper.h"

#include <QDir>
#include <QFile>
#include <filesystem>
#include <fstream>
#include <iostream>


void FileHelper::writeToFile(const char *msg, int len, const std::string &path,
                             bool append) {
  std::ofstream outfile;

  if (append) {
    outfile.open(path, std::ios::binary | std::ios::app);
  } else {
    outfile.open(path, std::ios::binary);
  }

  if (!outfile.is_open()) {
    throw std::runtime_error("Failed to open file: " + path);
  }

  outfile.write(msg, len);

  if (outfile.fail()) {
    throw std::runtime_error("Failed to write to file: " + path);
  }

  outfile.close();
}

void FileHelper::writeToFile(const std::string &msg, const std::string &path,
                             bool append) {
  writeToFile(msg.data(), msg.length(), path, append);
}

ArrayScope<char> FileHelper::readFile(const std::string &path) {
  std::ifstream inputFile(path, std::ios::binary);
  unsigned int size = getFileSize(path);
  ArrayScope<char> array(size);

  if (inputFile.is_open()) {
    inputFile.read(array.data(), array.size());
    inputFile.close();
  } else {
    throw std::runtime_error("Unable to open file: " + path);
  }

  return array;
}

unsigned int FileHelper::getFileSize(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  return file.tellg();
}

std::vector<char> FileHelper::readLastNBytes(const std::string &filename,
                                             int n) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return {};
  }

  // 获取文件大小
  unsigned int fileSize = file.tellg();

  // 确保 n 不超过文件大小
  n = std::min(n, static_cast<int>(fileSize));

  // 移动文件指针到倒数第 n 个字节
  file.seekg(fileSize - n);

  // 读取剩余的数据
  std::vector<char> buffer(n);
  file.read(buffer.data(), n);

  file.close();

  return buffer;
}

std::vector<char> FileHelper::readBytesFromPosition(const std::string &filePath,
                                                    std::streampos position,
                                                    std::size_t numBytes) {
  std::vector<char> buffer(numBytes);

  // 打开文件，以二进制模式
  std::ifstream file(filePath, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return {};
  }

  // 移动文件指针到指定位置
  file.seekg(position);
  if (!file) {
    std::cerr << "Failed to seek to position: " << position << std::endl;
    return {};
  }

  // 读取指定数量的字节
  file.read(buffer.data(), numBytes);
  if (!file) {
    std::cerr << "Failed to read bytes from file" << std::endl;
    // 如果读取失败，调整实际读取的字节数
    buffer.resize(file.gcount());
  }

  file.close();
  return buffer;
}

bool FileHelper::checkFileExistence(const std::string &filePath) {
  std::ifstream file(filePath);
  return file.good();
}

bool FileHelper::checkFileExistence(const QString &filePath) {
  QFileInfo fileInfo(filePath);
  return fileInfo.exists() && fileInfo.isFile();
}

bool FileHelper::checkDirExist(const QString &dir) {
  QDir directory(dir);
  return directory.exists();
}

void FileHelper::mkdirIfNotExist(const QString &dir) {
  QDir directory;
  if (!directory.exists(dir)) {
    directory.mkpath(dir);
  }
}
