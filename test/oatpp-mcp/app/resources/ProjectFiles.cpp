//
// Created by David Mayboroda on 10/12/2024.
//
#include "ProjectFiles.hpp"

#include "oatpp-mcp/capabilities/Utils.hpp"

namespace oatpp { namespace mcp { namespace app { namespace resource {

oatpp::Object<dto::Resource> ProjectFiles::describe() const {
  auto resource = dto::Resource::createShared();
  resource->uriTemplate = "file:///{path}";
  resource->name = "Project Files";
  resource->description = "Access files in the project directory";
  resource->mimeType="text/plain";
  return resource;
}

oatpp::Object<dto::ServerResultResourceCall> ProjectFiles::call(const oatpp::String& sessionId, const Router::Route& route) {
  auto result = dto::ServerResultResourceCall::createShared();
  result->contents = {
    createTextContent("File:///" + route.getMatchMap().getVariable("path"),
                      "text/plain",
                      "<<File content>>")
  };
  return result;
}

}}}}