//
// Created by Leonid S on 12/9/24.
//

#ifndef OATPP_MCP_APP_PROMPTS_CODEREVIEW_HPP
#define OATPP_MCP_APP_PROMPTS_CODEREVIEW_HPP

#include "oatpp-mcp/capabilities/Prompt.hpp"

namespace oatpp { namespace mcp { namespace app { namespace prompts {

class CodeReview : public oatpp::mcp::capabilities::Prompt {
public:

  oatpp::Object<dto::Prompt> describe() const override;
  oatpp::Object<dto::ServerResultPromptsCall> call(const oatpp::String& sessionId, const oatpp::Tree& args) override;

};

}}}}

#endif //OATPP_MCP_APP_PROMPTS_CODEREVIEW_HPP
