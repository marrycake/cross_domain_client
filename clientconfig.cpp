#include "clientconfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/xml_parser.hpp>
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
    std::string publicKeyStr = clientConf.get<std::string>(getKeyPublicKey());
    std::string privateKeyStr = clientConf.get<std::string>(getKeyPrivateKey());

    publicKey = RsaHelper::loadPublicKeyFromStr(publicKeyStr);
    privateKey = RsaHelper::loadPrivateKeyFromStr(privateKeyStr);
    token = clientConf.get<std::string>(getKeyToken());
  } catch (const boost::property_tree::ptree_error& e) {
    std::cerr << "Error accessing XML data: " << e.what() << '\n';
  }
}

void ClientConfig::dump() {
  boost::property_tree::ptree root;
  boost::property_tree::ptree clientConf;

  auto keyPair = RsaHelper::genKeyPair(2048);
  publicKey = keyPair.first;
  privateKey = keyPair.second;
  auto publicKeyStr = RsaHelper::dumpPublicKeyToStr(publicKey);
  auto privateKeyStr = RsaHelper::dumpPrivateKeyToStr(privateKey);

  clientConf.add(getKeyServerUrl(), "http://127.0.0.1:8080");
  clientConf.add(getKeyPublicKey(), publicKeyStr);
  clientConf.add(getKeyPrivateKey(), privateKeyStr);
  clientConf.add(getKeyToken(), "");

  root.add_child(getKeyRoot(), clientConf);

  boost::property_tree::write_xml(confPath, root, std::locale());
}

void ClientConfig::changeToken(const std::string& token) {
  this->token = token;
  boost::property_tree::ptree root;
  try {
    boost::property_tree::read_xml(confPath, root);
  } catch (const std::exception& e) {
    std::cerr << "Error reading XML file: " << e.what() << std::endl;
    return;
  }

  boost::property_tree::ptree& clientConf = root.get_child(getKeyRoot());
  clientConf.put(getKeyToken(), token);

  boost::property_tree::write_xml(confPath, root, std::locale());
}
