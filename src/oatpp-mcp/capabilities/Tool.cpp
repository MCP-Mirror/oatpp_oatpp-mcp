//
// Created by Leonid S on 12/9/24.
//

#include "Tool.hpp"

#include "oatpp/encoding/Base64.hpp"

#include <exception>

namespace oatpp { namespace mcp { namespace capabilities {

oatpp::Object<dto::ServerResultToolsCall> Tool::call(const oatpp::String& sessionId, const oatpp::Tree& args) {
  try {
    return onCall(sessionId, args);
  } catch (std::exception& e) {
    return createTextResult(oatpp::String("Unhandled error: ") + e.what(), true);
  }
}

oatpp::Object<dto::ServerResultToolsCall> Tool::createTextResult(const oatpp::String& text, bool isError) {
  oatpp::data::mapping::Tree content;

  content["type"] = "text";
  content["text"] = text;

  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {content};
  result->isError = isError;

  return result;
}

oatpp::Object<dto::ServerResultToolsCall> Tool::createImageResult(const oatpp::String& binaryImageData, const oatpp::String& mimeType) {
  oatpp::data::mapping::Tree content;

  content["type"] = "image";
  content["data"] = oatpp::encoding::Base64::encode(binaryImageData);
  content["mimeType"] = mimeType;

  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {content};
  result->isError = false;

  return result;
}

oatpp::Object<dto::ServerResultToolsCall> Tool::createResourceResult(const oatpp::String& uri, const oatpp::String& mimeType, const oatpp::String& text) {
  oatpp::data::mapping::Tree content;

  content["type"] = "resource";
  auto& node = content["resource"];
  node["uri"] = uri;
  node["mimeType"] = mimeType;
  node["text"] = text;

  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {content};
  result->isError = false;

  return result;
}

}}}
