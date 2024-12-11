//
// Created by Leonid S on 12/8/24.
//

#include "Server.hpp"

#include "oatpp/base/Log.hpp"

#include <thread>

namespace oatpp { namespace mcp { namespace event {

Server::Server(const std::shared_ptr<Session::Pinger>& pinger)
  : m_pinger(pinger)
{}

std::shared_ptr<Session> Server::startNewSession(const std::shared_ptr<Session::EventListener>& listener) {

  auto session = std::make_shared<Session>(m_pinger);
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_sessions[session->getId()] = session;
  }

  OATPP_LOGd("[oatpp::mcp::Server::startNewSession()]", "New session started {}", session->getId())

  std::thread t([this, session, listener]{
    session->listen(listener);
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_sessions.erase(session->getId());
      OATPP_LOGd("Server", "sessions count={}", m_sessions.size())
    }
  });

  t.detach();

  return session;
}

std::shared_ptr<Session> Server::getSession(const oatpp::String& sessionId) const {
  std::lock_guard<std::mutex> lock(m_mutex);
  auto it = m_sessions.find(sessionId);
  if(it != m_sessions.end()) {
    return it->second;
  }
  return nullptr;
}

}}}