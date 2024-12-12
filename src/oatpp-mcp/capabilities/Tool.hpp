//
// Created by Leonid S on 12/9/24.
//

#ifndef OATPP_MCP_CAPABILITIES_TOOL_HPP
#define OATPP_MCP_CAPABILITIES_TOOL_HPP

#include "oatpp-mcp/utils/ApiBridge.hpp"

#include "oatpp-mcp/dto/Methods.hpp"
#include "oatpp-mcp/event/Session.hpp"
#include "oatpp-mcp/utils/JsonSchema.hpp"

#include "oatpp/web/server/api/Endpoint.hpp"
#include "oatpp/web/protocol/http/Http.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Tool {
public:

  virtual ~Tool() = default;

  virtual oatpp::Object<dto::Tool> describe() const = 0;
  virtual oatpp::Object<dto::ServerResultToolsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) = 0;

};

class EndpointTool : public Tool {
public:
  struct Components {
    std::shared_ptr<utils::ApiBridge> apiBridge;
    std::shared_ptr<mcp::utils::ObjectSchemaMapper> schemaMapper;
    std::shared_ptr<oatpp::web::mime::ContentMappers> mappers;
  };
private:
  typedef oatpp::web::protocol::http::Headers Headers;
private:

  struct Error {
    oatpp::String message;
  };

private:
  oatpp::Tree generateEndpointSchema() const;
  oatpp::String prepareEndpointPath(const std::unordered_map<oatpp::String, oatpp::String>& args, Error& error) const;
  Headers prepareEndpointHeaders(const std::unordered_map<oatpp::String, oatpp::String>& args, Error& error) const;
private:
  std::shared_ptr<web::server::api::Endpoint> m_endpoint;
  Components m_components;
public:

  EndpointTool(const std::shared_ptr<web::server::api::Endpoint>& endpoint,
               const Components& components);

  oatpp::Object<dto::Tool> describe() const override;
  oatpp::Object<dto::ServerResultToolsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) override;

};

}}}

#endif //OATPP_MCP_CAPABILITIES_TOOL_HPP
