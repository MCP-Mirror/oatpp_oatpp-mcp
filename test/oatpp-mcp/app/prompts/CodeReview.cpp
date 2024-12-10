//
// Created by Leonid S on 12/9/24.
//

#include "CodeReview.hpp"

#include "oatpp-mcp/capabilities/Utils.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp { namespace app { namespace prompts {

oatpp::Object<dto::Prompt> CodeReview::describe() const {

  auto arg1 = dto::PromptArgument::createShared();
  arg1->name = "code";
  arg1->description = "Asks the LLM to analyze code quality and suggest improvements";
  arg1->required = true;

  auto prompt = dto::Prompt::createShared();
  prompt->name = "code_review";
  prompt->description = "Log something to server's console";
  prompt->arguments = {arg1};

  return prompt;
}

oatpp::Object<dto::ServerResultPromptsCall> CodeReview::call(const oatpp::String& sessionId, const oatpp::Tree& args) {

  auto message = dto::ServerResultPromptsMessage::createShared();
  message->role = dto::Role::USER;
  message->content = capabilities::Utils::createTextContent("Please review this Python code: " + args["code"].getString());

  auto result = dto::ServerResultPromptsCall::createShared();
  result->description = "Code review prompt";
  result->messages = {message};

  return result;

}

}}}}
