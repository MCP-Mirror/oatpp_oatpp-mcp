//
// Created by Leonid S on 12/10/24.
//

#ifndef OATPP_MCP_CAPABILITIES_UTILS_HPP
#define OATPP_MCP_CAPABILITIES_UTILS_HPP

#include "oatpp-mcp/dto/Methods.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

class Utils {
public:
  static oatpp::data::mapping::Tree createTextContent(const oatpp::String& text);
  static oatpp::data::mapping::Tree createImageContent(const oatpp::String& binaryImageData, const oatpp::String& mimeType);
  static oatpp::data::mapping::Tree createResourceContent(const oatpp::String& uri, const oatpp::String& mimeType, const oatpp::String& text);
};

}}}

#endif //OATPP_MCP_CAPABILITIES_UTILS_HPP
