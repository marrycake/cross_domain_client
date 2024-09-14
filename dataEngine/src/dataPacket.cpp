#include "dataPacket.h"

#include "hashGenerator.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/spdlog.h"

bool DataPacket::checkPacketValidate() {
  auto result = HashGenerator::sha256(encryptContent);
  return result == signature;
}

void DataPacket::display() {
  spdlog::debug("dataProvider:");
  dataProvider.display();
  spdlog::debug("directoryItemInfo:");
  directoryItemInfo.display();
  spdlog::debug("encryptContent: {:<30}", spdlog::to_hex(encryptContent));
  spdlog::debug("encryptKey: {:<30}", spdlog::to_hex(encryptKey));
  spdlog::debug("signature: {:<30}", spdlog::to_hex(signature));
}