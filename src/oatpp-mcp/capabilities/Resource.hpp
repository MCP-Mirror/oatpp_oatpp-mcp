//
// Created by David Mayboroda on 10/12/2024.
//

#ifndef OATPP_MCP_CAPABILITIES_RESOURCE_HPP
#define OATPP_MCP_CAPABILITIES_RESOURCE_HPP

#include "oatpp-mcp/dto/Methods.hpp"
#include "oatpp-mcp/event/Session.hpp"
#include "oatpp/web/url/mapping/Router.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Resource {
public:
  typedef oatpp::web::url::mapping::Router<std::shared_ptr<Resource>> Router;
public:

  virtual ~Resource() = default;

  virtual oatpp::Object<dto::Resource> describe() const = 0;
  virtual oatpp::Object<dto::ServerResultResourceCall> call(const oatpp::String& sessionId, const Router::Route& route) = 0;

  static oatpp::Object<dto::ServerResultResourceContent> createTextContent(const oatpp::String& uri,
                                                                           const oatpp::String& mimeType,
                                                                           const oatpp::String& text);

  static oatpp::Object<dto::ServerResultResourceContent> createBinaryContent(const oatpp::String& uri,
                                                                             const oatpp::String& mimeType,
                                                                             const oatpp::String& blob);

};

}}}
#endif //OATPP_MCP_CAPABILITIES_RESOURCE_HPP