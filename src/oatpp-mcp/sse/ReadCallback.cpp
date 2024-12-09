//
// Created by Leonid S on 12/8/24.
//

#include "ReadCallback.hpp"

#include "oatpp/data/stream/BufferStream.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp { namespace sse {

ReadCallback::ReadCallback(const oatpp::String& sessionId, const std::shared_ptr<EventInputStream>& eventStream)
  : m_sessionId(sessionId)
  , m_eventStream(eventStream)
  , m_initialized(false)
{}

oatpp::String ReadCallback::initEvent() {

  Event event;
  event.name = "endpoint";
  event.data = "/sessions/" + m_sessionId;

  oatpp::data::stream::BufferOutputStream ss(256);
  ss << "event: " << event.name << "\n";
  ss << "data: " << event.data << "\n\n";
  return ss.toString();
}

oatpp::String ReadCallback::waitEvent() {

  auto event = m_eventStream->read();

  OATPP_LOGd("Event", "[{}] <-- : {}", m_sessionId, event.data)

  if(event) {
    oatpp::data::stream::BufferOutputStream ss(256);
    ss << "event: " << event.name << "\n";
    ss << "data: " << event.data << "\n\n";
    return ss.toString();
  }

  return nullptr;

}

oatpp::v_io_size ReadCallback::read(void *buffer, v_buff_size count, oatpp::async::Action &action) {

  if(m_inlineData.bytesLeft == 0) {
    if(m_initialized) {
      m_currMessage = waitEvent();
    } else {
      m_currMessage = initEvent();
      m_initialized = true;
    }
    if(m_currMessage) m_inlineData.set(m_currMessage->data(), m_currMessage->size());
  }

  v_buff_size desiredToRead = m_inlineData.bytesLeft;
  if (desiredToRead > 0) {
    if (desiredToRead > count) desiredToRead = count;
    std::memcpy(buffer, m_inlineData.currBufferPtr, desiredToRead);
    m_inlineData.inc(desiredToRead);
    return desiredToRead;
  }

  return 0;

}

}}}