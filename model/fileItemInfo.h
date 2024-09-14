#ifndef FILEITEMINFO_H
#define FILEITEMINFO_H

#include <QString>
#include <cstdint>

enum FileCateGory {
  FILE_CATEGORY,
  DIR_CATEGORY,
  DOMAIN_CATEGORY,
  UNKOWN_CATEGORY
};

class FileItemInfo {
 public:
  explicit FileItemInfo(uint64_t fileId, const QString &fileName,
                        FileCateGory fileCategory, uint32_t privilige)
      : fileId(fileId),
        name(fileName),
        category(fileCategory),
        privilege(privilige){};

  uint64_t getFileId() const { return fileId; }

  const QString &getName() const { return name; }

  FileCateGory getCategory() const { return category; }

  uint32_t getPrivilege() const { return privilege; }

  // Setter methods
  void setFileId(uint64_t fileId) { this->fileId = fileId; }

  void setName(const QString &newName) { this->name = newName; }

  void setCategory(FileCateGory newCategory) { this->category = newCategory; }

  void setPrivilege(uint32_t newPrivilege) { this->privilege = newPrivilege; }

 private:
  uint64_t fileId;
  QString name;
  FileCateGory category;
  uint32_t privilege;
};

#endif  // FILEITEMINFO_H