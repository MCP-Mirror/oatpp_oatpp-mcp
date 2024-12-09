//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_SERVER_HPP
#define OATPP_MCP_SERVER_HPP

#include "Session.hpp"

#include <unordered_map>

namespace oatpp { namespace mcp {

class Server {
private:

  struct Handle {
    std::unordered_map<oatpp::String, std::shared_ptr<Session>> sessions;
  };

private:
  std::shared_ptr<Handle> m_handle;
public:

  Server();

  std::shared_ptr<Session> startNewSession(const std::shared_ptr<Session::EventListener>& listener);

  std::shared_ptr<Session> getSession(const oatpp::String& sessionId) const;

};

}}

#endif //OATPP_MCP_SERVER_HPP
