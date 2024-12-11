//
// Created by David Mayboroda on 10/12/2024.
//

#ifndef OATPP_MCP_FILE_HPP
#define OATPP_MCP_FILE_HPP
#include "oatpp-mcp/capabilities/Resource.hpp"

namespace oatpp { namespace mcp { namespace app { namespace resource {

class File : public oatpp::mcp::capabilities::Resource {
public:

    oatpp::Object<dto::Resource> describe() const override;
    oatpp::Object<dto::ServerResultResourceCall> call(const oatpp::String& sessionId) override;
};

}}}}
#endif //OATPP_MCP_FILE_HPP
