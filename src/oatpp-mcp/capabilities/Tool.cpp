//
// Created by Leonid S on 12/9/24.
//

#include "Tool.hpp"

#include "oatpp-mcp/capabilities/Utils.hpp"

#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EndpointTool

EndpointTool::EndpointTool(const std::shared_ptr<web::server::api::Endpoint>& endpoint,
                           const std::shared_ptr<mcp::utils::ObjectSchemaMapper>& schemaMapper,
                           const std::shared_ptr<utils::ApiBridge>& apiBridge)
  : m_endpoint(endpoint)
  , m_schemaMapper(schemaMapper)
  , m_apiBridge(apiBridge)
{}

oatpp::Tree EndpointTool::generateEndpointSchema() const {

  oatpp::data::mapping::Tree schema;
  oatpp::data::mapping::Tree defs;

  schema["type"] = "object";

  auto& params = schema["properties"];
  params.setMap({});

  auto& required = schema["required"];
  required.setVector(0);

  auto& info = *m_endpoint->info();

  for(auto& pp : info.pathParams.getOrder()) {
    auto& param = info.pathParams[pp];
    data::mapping::Tree req;
    req = param.name;
    required.getVector().push_back(req);
    params[param.name] = m_schemaMapper->map(param.type, defs);
  }

  for(auto& hp : info.headers.getOrder()) {
    auto& param = info.headers[hp];
    data::mapping::Tree req;
    req = param.name;
    required.getVector().push_back(req);
    params[param.name] = m_schemaMapper->map(param.type, defs);
  }

  for(auto& qp : info.queryParams.getOrder()) {
    auto& param = info.queryParams[qp];
    if(param.required) {
      data::mapping::Tree req;
      req = param.name;
      required.getVector().push_back(req);
    }
    params[param.name] = m_schemaMapper->map(param.type, defs);
  }

  if(info.body.name != nullptr && info.body.type != nullptr) {
    auto& param = info.body;
    if(param.required) {
      data::mapping::Tree req;
      req = param.name;
      required.getVector().push_back(req);
    }
    params[param.name] = m_schemaMapper->map(param.type, defs);
  }

  if(!defs.isUndefined()) {
    schema["$defs"] = std::move(defs);
  }

  return schema;

}

oatpp::String EndpointTool::prepareEndpointPath(const std::unordered_map<oatpp::String, oatpp::String>& args, Error& error) const {

  auto& info = *m_endpoint->info();
  oatpp::String pathTail;
  {
    oatpp::data::stream::BufferOutputStream ss(256);
    for(auto& qp : info.queryParams.getOrder()) {
      auto& param = info.queryParams[qp];
      auto it = args.find(param.name);
      if(it != args.end()) {
        if (ss.getCurrentPosition() == 0) {
          ss << "?";
        } else {
          ss << "&";
        }
        ss << param.name << "=" << it->second;
      }
    }
    pathTail = ss.toString();
  }

  auto pattern = oatpp::web::url::mapping::Pattern::parse(m_endpoint->info()->path);
  return pattern->reconstruct(args, pathTail);

}

EndpointTool::Headers EndpointTool::prepareEndpointHeaders(const std::unordered_map<oatpp::String, oatpp::String>& args, Error& error) const {

  Headers result;

  auto& info = *m_endpoint->info();

  for(auto& hp : info.headers.getOrder()) {
    auto& param = info.headers[hp];
    auto it = args.find(param.name);
    if(it != args.end()) {
      result.put(it->first, it->second);
    }
  }

  return result;

}

oatpp::Object<dto::Tool> EndpointTool::describe() const {

  auto tool = dto::Tool::createShared();

  tool->name = m_endpoint->info()->name;
  if(m_endpoint->info()->description) {
    tool->description = m_endpoint->info()->description;
  } else if(m_endpoint->info()->summary) {
    tool->description = m_endpoint->info()->summary;
  } else {
    tool->description = m_endpoint->info()->name;
  }

  tool->inputSchema = generateEndpointSchema();

  return tool;
}

oatpp::Object<dto::ServerResultToolsCall> EndpointTool::call(const oatpp::String& sessionId, const oatpp::Tree& args) {

  std::unordered_map<oatpp::String, oatpp::String> stringArgs;
  for(v_uint32 i = 0; i < (*args).getMap().size(); i ++) {
    auto pair = (*args).getMap()[i];
    stringArgs[pair.first] = pair.second.get().toString();
  }

  Error error;
  auto path = prepareEndpointPath(stringArgs, error);
  auto headers = prepareEndpointHeaders(stringArgs, error);

  OATPP_LOGi("EndpointTool::call", "path: '{}'", path)
  for(auto& h : headers.getAll()) {
    OATPP_LOGi("EndpointTool::call", "Header: {}: '{}'", h.first.toString(), h.second.toString())
  }

  std::shared_ptr<oatpp::web::protocol::http::outgoing::Body> body;
  auto bodyIt = stringArgs.find(m_endpoint->info()->body.name);
  if(bodyIt != stringArgs.end()) {
    body = std::make_shared<oatpp::web::protocol::http::outgoing::BufferBody>(bodyIt->second, "text/plain");
  }

  auto response = m_apiBridge->getHttpExecutor()->execute(
    m_endpoint->info()->method,
    m_endpoint->info()->path,
    headers,
    body,
    nullptr
  );

  if(!response) {
    auto result = dto::ServerResultToolsCall::createShared();
    result->content = {capabilities::Utils::createTextContent("Null response")};
    result->isError = true;
  }

  oatpp::String bodyString = response->readBodyToString();

  auto result = dto::ServerResultToolsCall::createShared();
  return result;
}

}}}
