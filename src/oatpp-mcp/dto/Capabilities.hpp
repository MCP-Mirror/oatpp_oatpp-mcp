//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_DTO_CAPABILITIES_HPP
#define OATPP_MCP_DTO_CAPABILITIES_HPP

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace oatpp { namespace mcp { namespace dto {

class PromptArgument : public oatpp::DTO {

  DTO_INIT(PromptArgument, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, description);
  DTO_FIELD(Boolean, required);

};

class Prompt : public oatpp::DTO {

  DTO_INIT(Prompt, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, description);
  DTO_FIELD(Vector<Object<PromptArgument>>, arguments);

};

class Resource : public oatpp::DTO {

  DTO_INIT(Resource, DTO)

  DTO_FIELD(String, uri);
  DTO_FIELD(String, uriTemplate);
  DTO_FIELD(String, name);
  DTO_FIELD(String, description);
  DTO_FIELD(String, mimeType);

};

class Tool : public oatpp::DTO {

  DTO_INIT(Tool, DTO)

  DTO_FIELD(String, name);
  DTO_FIELD(String, description);
  DTO_FIELD(Tree, inputSchema);

};

class CapabilityDeclaration : public oatpp::DTO {

  DTO_INIT(CapabilityDeclaration, DTO)

  DTO_FIELD(Boolean, listChanged);

};

class ClientCapabilities : public oatpp::DTO {

  DTO_INIT(ClientCapabilities, DTO)

  DTO_FIELD(Object<CapabilityDeclaration>, roots);
  DTO_FIELD(Object<CapabilityDeclaration>, sampling);
  DTO_FIELD(Object<CapabilityDeclaration>, experimental);

};

class ServerCapabilities : public oatpp::DTO {

  DTO_INIT(ServerCapabilities, DTO)

  DTO_FIELD(Object<CapabilityDeclaration>, prompts);
  DTO_FIELD(Object<CapabilityDeclaration>, resources);
  DTO_FIELD(Object<CapabilityDeclaration>, tools);
  DTO_FIELD(Object<CapabilityDeclaration>, logging);
  DTO_FIELD(Object<CapabilityDeclaration>, experimental);

};

}}}

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_MCP_DTO_CAPABILITIES_HPP
