//
// Created by Leonid S on 12/9/24.
//

#ifndef OATPP_MCP_CAPABILITIES_TOOL_HPP
#define OATPP_MCP_CAPABILITIES_TOOL_HPP

#include "oatpp-mcp/dto/Methods.hpp"
#include "oatpp-mcp/event/Session.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Tool {
public:

  virtual ~Tool() = default;

  virtual oatpp::Object<dto::Tool> describe() const = 0;
  virtual oatpp::Object<dto::ServerResultToolsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) = 0;

};

}}}

#endif //OATPP_MCP_CAPABILITIES_TOOL_HPP
