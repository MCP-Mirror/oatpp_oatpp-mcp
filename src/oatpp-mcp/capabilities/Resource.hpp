//
// Created by David Mayboroda on 10/12/2024.
//

#ifndef OATPP_MCP_RESOURCE_HPP
#define OATPP_MCP_RESOURCE_HPP

#include "oatpp-mcp/dto/Methods.hpp"
#include "oatpp-mcp/event/Session.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Resource {
public:

    virtual ~Resource() = default;

    virtual oatpp::Object<dto::Resource> describe() const = 0;
    virtual oatpp::Object<dto::ServerResultResourceCall> call(const oatpp::String& sessionId) = 0;

};

}}}
#endif //OATPP_MCP_RESOURCE_HPP