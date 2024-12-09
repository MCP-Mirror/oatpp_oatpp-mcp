//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_LISTENER_HPP
#define OATPP_MCP_LISTENER_HPP

#include "dto/JsonRpc.hpp"
#include "dto/Methods.hpp"

#include "capabilities/Tool.hpp"

#include "event/Session.hpp"

#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/data/mapping/ObjectRemapper.hpp"

namespace oatpp { namespace mcp {

class Pinger : public event::Session::Pinger {
private:
  std::atomic<v_uint64> m_pingId;
  oatpp::json::ObjectMapper m_mapper;
public:
  Pinger();
  void onPing(event::Session& session) override;
};

class Listener : public event::Session::EventListener {
private:
  oatpp::json::ObjectMapper m_mapper;
  oatpp::data::mapping::ObjectRemapper m_remapper;
private:
  void sendRpcResult(event::Session& session, const oatpp::Object<dto::RpcResult>& result);
  oatpp::Object<dto::ServerCapabilities> getServerCapabilities();
private:
  void toolsCall(event::Session& session, const oatpp::Object<dto::RpcCall>& call);
  void toolsList(event::Session& session, const oatpp::Object<dto::RpcCall>& call);
  void onInitialize(event::Session& session, const oatpp::Object<dto::RpcCall>& call);
private:
  void onPing(event::Session& session, const oatpp::Object<dto::RpcCall>& call);
private:
  std::unordered_map<oatpp::String, std::shared_ptr<capabilities::Tool>> m_tools;
public:

  Listener();

  void addTool(const std::shared_ptr<capabilities::Tool>& tool);

  void onEvent(event::Session& session, const event::Event& event) override;

};

}}

#endif //MY_PROJECT_LISTENER_HPP
