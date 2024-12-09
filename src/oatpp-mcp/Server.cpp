//
// Created by Leonid S on 12/8/24.
//

#include "Server.hpp"

#include "oatpp/base/Log.hpp"

#include <thread>

namespace oatpp { namespace mcp {

Server::Server(const std::shared_ptr<Session::Pinger>& pinger)
  : m_handle(std::make_shared<Handle>())
  , m_pinger(pinger)
{}

std::shared_ptr<Session> Server::startNewSession(const std::shared_ptr<Session::EventListener>& listener) {

  if(!m_handle) return nullptr;

  auto session = std::make_shared<Session>(m_pinger);
  m_handle->sessions[session->getId()] = session;

  OATPP_LOGd("[oatpp::mcp::Server::startNewSession()]", "New session started {}", session->getId())

  std::thread t([this, session, listener]{
    session->listen(listener);
    m_handle->sessions.erase(session->getId());
    OATPP_LOGd("Server", "sessions count={}", m_handle->sessions.size())
  });

  t.detach();

  return session;
}

std::shared_ptr<Session> Server::getSession(const oatpp::String& sessionId) const {
  if(!m_handle) return nullptr;
  auto it = m_handle->sessions.find(sessionId);
  if(it != m_handle->sessions.end()) {
    return it->second;
  }
  return nullptr;
}

}}