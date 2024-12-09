//
// Created by Leonid S on 12/8/24.
//

#include "Listener.hpp"

#include "oatpp/utils/Conversion.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp {

Pinger::Pinger()
  : m_pingId(0)
{
  m_mapper.serializerConfig().mapper.includeNullFields = false;
}

void Pinger::onPing(event::Session& session) {

  m_pingId ++;

  auto call = dto::RpcCall::createShared();
  call->id = "ping_" + oatpp::utils::Conversion::uint64ToStr(m_pingId);
  call->method = "ping";

  event::Event event;
  event.name = "message";
  event.data = m_mapper.writeToString(call);
  session.getOutStream()->post(event);

}

Listener::Listener() {
  m_mapper.serializerConfig().mapper.includeNullFields = false;
  m_remapper.objectToTreeConfig().includeNullFields = false;
}

void Listener::addTool(const std::shared_ptr<capabilities::Tool>& tool) {
  auto description = tool->describe();
  if(description && description->name && !description->name->empty()) {
    m_tools[description->name] = tool;
  }
}

void Listener::sendRpcResult(event::Session& session, const oatpp::Object<dto::RpcResult>& result) {
  event::Event event;
  event.name = "message";
  event.data = m_mapper.writeToString(result);

  session.getOutStream()->post(event);
}

oatpp::Object<dto::ServerCapabilities> Listener::getServerCapabilities() {
  auto caps = dto::ServerCapabilities::createShared();
  if(!m_tools.empty()) {
    caps->tools = dto::CapabilityDeclaration::createShared();
    caps->tools->listChanged = true;
  }
  return caps;
}

void Listener::toolsCall(event::Session& session, const oatpp::Object<dto::RpcCall>& call) {

  auto rpcResult = dto::RpcResult::createShared();
  rpcResult->id = call->id;

  auto callParams = m_remapper.remap<oatpp::Object<dto::ClientParamsToolsCall>>(call->params);
  auto it = m_tools.find(callParams->name);

  if(it != m_tools.end()) {
    auto result = it->second->call(session.getId(), callParams->arguments);
    rpcResult->result = m_remapper.remap<oatpp::Tree>(result);
  } else {
    oatpp::data::mapping::Tree error;
    error["code"] = -32602;
    error["message"] = "Unknown tool: invalid_tool_name";
    rpcResult->error = error;
  }

  sendRpcResult(session, rpcResult);

}

void Listener::toolsList(event::Session& session, const oatpp::Object<dto::RpcCall>& call) {

  auto rpcResult = dto::RpcResult::createShared();
  rpcResult->id = call->id;

  auto callParams = m_remapper.remap<oatpp::Object<dto::ClientParamsToolsList>>(call->params);

  auto result = dto::ServerResultToolsList::createShared();
  result->tools = {};
  for(auto& p : m_tools) {
    result->tools->push_back(p.second->describe());
  }

  rpcResult->result = m_remapper.remap<oatpp::Tree>(result);
  sendRpcResult(session, rpcResult);

}

void Listener::onInitialize(event::Session& session, const oatpp::Object<dto::RpcCall>& call) {

  auto rpcResult = dto::RpcResult::createShared();
  rpcResult->id = call->id;

  auto callParams = m_remapper.remap<oatpp::Object<dto::ClientParamsInitialize>>(call->params);
  // TODO save client capabilities

  auto result = dto::ServerResultInitialize::createShared();
  result->protocolVersion = "2024-11-05";
  result->capabilities = getServerCapabilities();
  result->serverInfo = dto::ServerInfo::createShared();
  result->serverInfo->name = "Oat++ MCP Server";
  result->serverInfo->version = "0.0.1";

  rpcResult->result = m_remapper.remap<oatpp::Tree>(result);
  sendRpcResult(session, rpcResult);

}

void Listener::onPing(event::Session& session, const oatpp::Object<dto::RpcCall>& call) {
  auto rpcResult = dto::RpcResult::createShared();
  rpcResult->id = call->id;
  rpcResult->result->setMap({});
  sendRpcResult(session, rpcResult);
}

void Listener::onEvent(event::Session& session, const event::Event& event) {

  OATPP_LOGd("Event", "[{}] --> : {}", session.getId(), event.data)

  auto parsedEvent = m_mapper.readFromString<oatpp::Tree>(event.data);
  if(!parsedEvent->isMap() || parsedEvent["method"].isNull() || parsedEvent["method"].isUndefined()) {
    return; // message is NOT a call - IGNORE
  }

  auto call = m_remapper.remap<oatpp::Object<dto::RpcCall>>(parsedEvent);

  if(call->method == "ping") {
    onPing(session, call);
  } else if(call->method == "initialize") {
    onInitialize(session, call);
  } else if(call->method == "tools/list") {
    toolsList(session, call);
  } else if(call->method == "tools/call") {
    toolsCall(session, call);
  }

}

}}
