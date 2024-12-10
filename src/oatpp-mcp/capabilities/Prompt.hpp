//
// Created by Leonid S on 12/10/24.
//

#ifndef OATPP_MCP_CAPABILITIES_PROMPT_HPP
#define OATPP_MCP_CAPABILITIES_PROMPT_HPP

#include "oatpp-mcp/dto/Methods.hpp"
#include "oatpp-mcp/event/Session.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Prompt {
public:

  virtual ~Prompt() = default;

  virtual oatpp::Object<dto::Prompt> describe() const = 0;
  virtual oatpp::Object<dto::ServerResultPromptsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) = 0;

};

}}}

#endif //OATPP_MCP_CAPABILITIES_PROMPT_HPP
