//
// Created by David Mayboroda on 10/12/2024.
//

#include "Resource.hpp"

#include "oatpp/encoding/Base64.hpp"

namespace oatpp { namespace mcp { namespace capabilities {

oatpp::Object<dto::ServerResultResourceContent> Resource::createTextContent(const oatpp::String& uri,
                                                                            const oatpp::String& mimeType,
                                                                            const oatpp::String& text)
{
  auto result = dto::ServerResultResourceContent::createShared();
  result->uri = uri;
  result->mimeType = mimeType;
  result->text = text;
  return result;
}

oatpp::Object<dto::ServerResultResourceContent> Resource::createBinaryContent(const oatpp::String& uri,
                                                                              const oatpp::String& mimeType,
                                                                              const oatpp::String& blob)
{
  auto result = dto::ServerResultResourceContent::createShared();
  result->uri = uri;
  result->mimeType = mimeType;
  result->blob = oatpp::encoding::Base64::encode(blob);
  return result;
}

}}}