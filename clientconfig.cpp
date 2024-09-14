#include "clientconfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cstdint>
#include <string>

#include "rsaHelper.h"

void ClientConfig::load() {
  boost::property_tree::ptree root;
  try {
    boost::property_tree::read_xml(confPath, root);
  } catch (const boost::property_tree::xml_parser_error& e) {
    std::cerr << "Error reading XML file: " << e.what() << '\n';
    return;
  }

  try {
    boost::property_tree::ptree clientConf = root.get_child(getKeyRoot());
    serverUrl = clientConf.get<std::string>(getKeyServerUrl());
    boost::property_tree::ptree userConf =
        clientConf.get_child(getKeyUserInfo());
    userInfo.setUserId(userConf.get<uint64_t>(getKeyUserId()));
    userInfo.setUserName(userConf.get<std::string>(getKeyUserName()));
    userInfo.setUserPrivilige(userConf.get<uint32_t>(getKeyUserPrivilige()));
    userInfo.setToken(userConf.get<std::string>(getKeyToken()));
    userInfo.setUserPublicKey(RsaHelper::loadPublicKeyFromStr(
        userConf.get<std::string>(getKeyPublicKey())));
    userInfo.setUserPrivateKey(RsaHelper::loadPrivateKeyFromStr(
        userConf.get<std::string>(getKeyPrivateKey())));
  } catch (const boost::property_tree::ptree_error& e) {
    std::cerr << "Error accessing XML data: " << e.what() << '\n';
  }
}

void ClientConfig::dump() {
  boost::property_tree::ptree root;
  boost::property_tree::ptree clientConf;
  boost::property_tree::ptree userConf;

  userConf.put(getKeyUserId(), 1);
  userConf.put(getKeyUserName(), "");
  userConf.put(getKeyUserPrivilige(), 0);
  userConf.put(getKeyToken(), "");
  auto keyPair = RsaHelper::genKeyPair(2048);
  userConf.put(getKeyPublicKey(), RsaHelper::dumpPublicKeyToStr(keyPair.first));
  userConf.put(getKeyPrivateKey(),
               RsaHelper::dumpPrivateKeyToStr(keyPair.second));

  clientConf.put(getKeyServerUrl(), "http://127.0.0.1:8080");

  clientConf.add_child(getKeyUserInfo(), userConf);

  root.add_child(getKeyRoot(), clientConf);

  boost::property_tree::write_xml(confPath, root, std::locale());
}

void ClientConfig::redump() {
  boost::property_tree::ptree root;
  try {
    boost::property_tree::read_xml(confPath, root);
  } catch (const std::exception& e) {
    std::cerr << "Error reading XML file: " << e.what() << std::endl;
    return;
  }

  boost::property_tree::ptree& clientConf = root.get_child(getKeyRoot());
  clientConf.put(getKeyServerUrl(), serverUrl);

  boost::property_tree::ptree& userConf =
      clientConf.get_child(getKeyUserInfo());
  userConf.put(getKeyUserId(), userInfo.getUserId());
  userConf.put(getKeyUserName(), userInfo.getUserName());
  userConf.put(getKeyUserPrivilige(), userInfo.getUserPrivilige());
  userConf.put(getKeyToken(), userInfo.getToken());
  userConf.put(getKeyPublicKey(),
               RsaHelper::dumpPublicKeyToStr(userInfo.getUserPublicKey()));
  userConf.put(getKeyPrivateKey(),
               RsaHelper::dumpPrivateKeyToStr(userInfo.getUserPrivateKey()));
  boost::property_tree::write_xml(confPath, root, std::locale());
}
