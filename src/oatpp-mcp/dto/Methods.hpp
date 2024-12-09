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

}}}

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_MCP_DTO_METHODS_HPP
