//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_SESSION_HPP
#define OATPP_MCP_SESSION_HPP

#include "EventStream.hpp"

#include <memory>

namespace oatpp { namespace mcp {

class Session {
public:

  class EventListener {
  public:
    virtual ~EventListener() = default;
    virtual void onEvent(Session& session, const Event& event) = 0;
  };

private:
  std::shared_ptr<EventStream> m_inStream;
  std::shared_ptr<EventStream> m_outStream;
private:
  bool m_open;
  std::mutex m_mutex;
public:

  Session();

  std::shared_ptr<EventStream> getInStream();
  std::shared_ptr<EventStream> getOutStream();

  /**
   * process session
   */
  void listen(std::shared_ptr<EventListener> listener);

  bool isOpen();

  void close();

  oatpp::String getId() const;

};

}}

#endif //OATPP_MCP_SESSION_HPP
