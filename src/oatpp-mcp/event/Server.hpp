//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_EVENT_SERVER_HPP
#define OATPP_MCP_EVENT_SERVER_HPP

#include "Session.hpp"

#include <unordered_map>
#include <mutex>

namespace oatpp { namespace mcp { namespace event {

class Server {
private:
  std::shared_ptr<Session::Pinger> m_pinger;
private:
  std::unordered_map<oatpp::String, std::shared_ptr<Session>> m_sessions;
private:
  mutable std::mutex m_mutex;
public:

  Server(const std::shared_ptr<Session::Pinger>& pinger = nullptr);

  std::shared_ptr<Session> startNewSession(const std::shared_ptr<Session::EventListener>& listener);

  std::shared_ptr<Session> getSession(const oatpp::String& sessionId) const;

};

}}}

#endif //OATPP_MCP_EVENT_SERVER_HPP
