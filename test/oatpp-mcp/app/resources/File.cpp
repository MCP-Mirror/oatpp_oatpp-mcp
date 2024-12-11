//
// Created by David Mayboroda on 10/12/2024.
//
#include "File.hpp"

#include "oatpp-mcp/capabilities/Utils.hpp"

namespace oatpp { namespace mcp { namespace app { namespace resource {

oatpp::Object<dto::Resource> File::describe() const {
    auto resource = dto::Resource::createShared();
    resource->name = "main.rs";
    resource->description = "Primary application entry point";
    resource->uri = "file:///project/src/main.rs";
    resource->mimeType="text/x-rust";
    return resource;
}

oatpp::Object<dto::ServerResultResourceCall> File::call(const oatpp::String &sessionId) {

    auto result = dto::ServerResultResourceCall::createShared();
    oatpp::data::mapping::Tree content;
    content["uri"] = "file:///project/src/main.rs";
    content["mimeType"] = "text/x-rust";
    content["text"] = "fn main() {\n    println!(\"Hello world!\");\n}";
    result->contents->push_back(content);
    return result;
}

}}}}