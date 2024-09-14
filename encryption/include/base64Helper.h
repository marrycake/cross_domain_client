#ifndef BASE64HELPER_H
#define BASE64HELPER_H

#include <string>
class Base64Helper {
 public:
  static std::string encode(const std::string &data);
  static std::string decode(const std::string &data);
};

#endif  // BASE64HELPER_H