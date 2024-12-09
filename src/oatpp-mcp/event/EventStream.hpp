//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_EVENT_EVENTSTREAM_HPP
#define OATPP_MCP_EVENT_EVENTSTREAM_HPP

#include "oatpp/Types.hpp"

#include <mutex>
#include <condition_variable>
#include <list>
#include <chrono>

namespace oatpp { namespace mcp { namespace event {

struct Event {

  oatpp::String name;
  oatpp::String data;

  explicit inline operator bool() const {
    return name != nullptr && data != nullptr;
  }

};

class EventInputStream {
public:
  virtual ~EventInputStream() = default;
  virtual Event read(const std::chrono::duration<v_int64, std::milli>& timeout) = 0;
};

class EventOutputStream {
public:
  virtual ~EventOutputStream() = default;
  virtual void post(const Event& event) = 0;
};

class EventStream : public EventInputStream, public EventOutputStream {
private:
  v_uint32 m_maxQueueSize;
private:
  std::list<Event> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_cv;
private:
  bool m_open;
public:

  explicit EventStream(v_uint32 maxQueueSize = 100);

  void post(const Event& event) override;
  Event read(const std::chrono::duration<v_int64, std::milli>& timeout = std::chrono::milliseconds(0)) override;

  void close();
  bool isOpen();

};

}}}

#endif //OATPP_MCP_EVENT_EVENTSTREAM_HPP
