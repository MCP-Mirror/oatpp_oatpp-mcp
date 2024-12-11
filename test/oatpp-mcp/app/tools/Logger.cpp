//
// Created by Leonid S on 12/9/24.
//

#include "Logger.hpp"

#include "oatpp-mcp/capabilities/Utils.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp { namespace app { namespace tools {

oatpp::Object<dto::Tool> Logger::describe() const {
  oatpp::data::mapping::Tree schema;
  schema["type"] = "object";
  schema["properties"]["message"]["type"] = "string";
  schema["required"].setVector(1);
  schema["required"][0] = "message";

  auto tool = dto::Tool::createShared();
  tool->name = "console.log";
  tool->description = "Log something to server's console";
  tool->inputSchema = schema;
  return tool;
}

oatpp::Object<dto::ServerResultToolsCall> Logger::call(const oatpp::String& sessionId, const oatpp::Tree& args) {
  auto result = dto::ServerResultToolsCall::createShared();

  auto message = args["message"].getString();
  OATPP_LOGd("[TOOL]", "LOGGING MESSAGE: {}", message)

  result->content = {
    capabilities::Utils::createTextContent("message was successfully logged")
  };

  return result;
}

}}}}
