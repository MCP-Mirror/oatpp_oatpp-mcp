//
// Created by Leonid S on 12/10/24.
//

#include "Utils.hpp"
#include "oatpp/encoding/Base64.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

oatpp::data::mapping::Tree Utils::createTextContent(const oatpp::String& text) {
  oatpp::data::mapping::Tree content;
  content["type"] = "text";
  content["text"] = text;
  return content;
}

oatpp::data::mapping::Tree Utils::createImageContent(const oatpp::String& binaryImageData, const oatpp::String& mimeType) {
  oatpp::data::mapping::Tree content;
  content["type"] = "image";
  content["data"] = oatpp::encoding::Base64::encode(binaryImageData);
  content["mimeType"] = mimeType;
  return content;
}

oatpp::data::mapping::Tree Utils::createResourceContent(const oatpp::String& uri, const oatpp::String& mimeType, const oatpp::String& text) {
  oatpp::data::mapping::Tree content;
  content["type"] = "resource";
  auto& node = content["resource"];
  node["uri"] = uri;
  node["mimeType"] = mimeType;
  node["text"] = text;
  return content;
}

}}}