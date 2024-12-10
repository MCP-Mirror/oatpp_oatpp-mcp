//
// Created by Leonid S on 12/9/24.
//

#ifndef OATPP_MCP_APP_TOOLS_LOGGER_HPP
#define OATPP_MCP_APP_TOOLS_LOGGER_HPP

#include "oatpp-mcp/capabilities/Tool.hpp"

namespace oatpp { namespace mcp { namespace app { namespace tools {

class Logger : public oatpp::mcp::capabilities::Tool {
public:

  oatpp::Object<dto::Tool> describe() const override;
  oatpp::Object<dto::ServerResultToolsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) override;

};

}}}}

#endif //OATPP_MCP_APP_TOOLS_LOGGER_HPP
