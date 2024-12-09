//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_DTO_JSONRPC_HPP
#define OATPP_MCP_DTO_JSONRPC_HPP

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace oatpp { namespace mcp { namespace dto {

class RpcCall : oatpp::DTO {

  DTO_INIT(RpcCall, DTO)

  DTO_FIELD(String, jsonrpc) = "2.0";
  DTO_FIELD(Any, id);
  DTO_FIELD(String, method);
  DTO_FIELD(Tree, params);

};

class RpcResult : oatpp::DTO {

  DTO_INIT(RpcResult, DTO)

  DTO_FIELD(String, jsonrpc) = "2.0";
  DTO_FIELD(Any, id);
  DTO_FIELD(Tree, result);
  DTO_FIELD(Tree, error);

};

}}}

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_MCP_DTO_JSONRPC_HPP
