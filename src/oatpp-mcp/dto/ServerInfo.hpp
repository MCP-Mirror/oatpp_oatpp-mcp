//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_DTO_SERVERINFO_HPP
#define OATPP_MCP_DTO_SERVERINFO_HPP

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace oatpp { namespace mcp { namespace dto {

class ServerInfo : public oatpp::DTO {

  DTO_INIT(ServerInfo, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, version);

};

}}}

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_MCP_DTO_SERVERINFO_HPP
