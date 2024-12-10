//
// Created by Leonid S on 12/9/24.
//

#include "Tool.hpp"
#include "Utils.hpp"

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
  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {Utils::createTextContent(text)};
  result->isError = isError;
  return result;
}

oatpp::Object<dto::ServerResultToolsCall> Tool::createImageResult(const oatpp::String& binaryImageData, const oatpp::String& mimeType) {
  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {Utils::createImageContent(binaryImageData, mimeType)};
  result->isError = false;
  return result;
}

oatpp::Object<dto::ServerResultToolsCall> Tool::createResourceResult(const oatpp::String& uri, const oatpp::String& mimeType, const oatpp::String& text) {
  auto result = oatpp::mcp::dto::ServerResultToolsCall::createShared();
  result->content = {Utils::createResourceContent(uri, mimeType, text)};
  result->isError = false;
  return result;
}

}}}
