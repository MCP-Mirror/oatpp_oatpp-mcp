//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_DTO_METHODS_HPP
#define OATPP_MCP_DTO_METHODS_HPP

#include "Capabilities.hpp"
#include "ClientInfo.hpp"
#include "ServerInfo.hpp"

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace oatpp { namespace mcp { namespace dto {

class ClientParamsInitialize : oatpp::DTO {

  DTO_INIT(ClientParamsInitialize, DTO)

  DTO_FIELD(String, protocolVersion);
  DTO_FIELD(Object<ClientCapabilities>, capabilities);
  DTO_FIELD(Object<ClientInfo>, clientInfo);

};

class ServerResultInitialize : oatpp::DTO {

  DTO_INIT(ServerResultInitialize, DTO)

  DTO_FIELD(String, protocolVersion);
  DTO_FIELD(Object<ServerCapabilities>, capabilities);
  DTO_FIELD(Object<ServerInfo>, serverInfo);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TOOLS

class ClientParamsToolsList : oatpp::DTO {

  DTO_INIT(ClientParamsToolsList, DTO)

  DTO_FIELD(String, cursor);

};

class ServerResultToolsList : oatpp::DTO {

  DTO_INIT(ServerResultToolsList, DTO)

  DTO_FIELD(Vector<Object<Tool>>, tools);
  DTO_FIELD(String, nextCursor);

};

class ClientParamsToolsCall : oatpp::DTO {

  DTO_INIT(ClientParamsToolsCall, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Tree, arguments);

};

class ServerResultToolsCall : oatpp::DTO {

  DTO_INIT(ServerResultToolsCall, DTO)

  DTO_FIELD(Vector<Tree>, content);
  DTO_FIELD(Boolean, isError);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROMPTS

class ClientParamsPromptsList : oatpp::DTO {

  DTO_INIT(ClientParamsPromptsList, DTO)

  DTO_FIELD(String, cursor);

};

class ServerResultPromptsList : oatpp::DTO {

  DTO_INIT(ServerResultPromptsList, DTO)

  DTO_FIELD(Vector<Object<Prompt>>, prompts);
  DTO_FIELD(String, nextCursor);

};

class ClientParamsPromptsCall : oatpp::DTO {

  DTO_INIT(ClientParamsPromptsCall, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(Tree, arguments);

};

ENUM(Role, v_uint32,
     VALUE(USER, 0, "user"),
     VALUE(ASSISTANT, 1, "assistant")
)

class ServerResultPromptsMessage : oatpp::DTO {

  DTO_INIT(ServerResultPromptsMessage, DTO)

  DTO_FIELD(Enum<Role>::AsString, role);
  DTO_FIELD(Tree, content);

};

class ServerResultPromptsCall : oatpp::DTO {

  DTO_INIT(ServerResultPromptsCall, DTO)

  DTO_FIELD(String, description);
  DTO_FIELD(Vector<Object<ServerResultPromptsMessage>>, messages);

};

}}}

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_MCP_DTO_METHODS_HPP
