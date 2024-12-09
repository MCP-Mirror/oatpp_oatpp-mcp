//
// Created by Leonid S on 12/8/24.
//

#include "Session.hpp"
#include "oatpp/utils/Conversion.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp {

Session::Session(const std::shared_ptr<Pinger>& pinger)
  : m_pinger(pinger)
  , m_inStream(std::make_shared<EventStream>())
  , m_outStream(std::make_shared<EventStream>())
  , m_open(true)
{}

Session::~Session() {
  close();
  OATPP_LOGd("AAA", "Session::~Session()")
}

std::shared_ptr<EventStream> Session::getInStream() {
  return m_inStream;
}

std::shared_ptr<EventStream> Session::getOutStream() {
  return m_outStream;
}

void Session::listen(std::shared_ptr<EventListener> listener) {

  if(!listener) {
    OATPP_LOGe("[oatpp::mcp::Session::listen()]", "Error - listener should NOT be null")
    return;
  }

  while (isOpen()) {
    auto event = m_inStream->read(std::chrono::milliseconds(5000));
    if(event) {
      listener->onEvent(*this, event);
    } else if (m_pinger) {
      m_pinger->onPing(*this);
    }
  }

}

bool Session::isOpen() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if(!m_inStream->isOpen()) {
    closeNonBlocking();
  }
  return m_open;
}

void Session::closeNonBlocking() {
  m_open = false;
  m_inStream->close();
  m_outStream->close();
}

void Session::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  closeNonBlocking();
}

oatpp::String Session::getId() const {
  auto memId = reinterpret_cast<v_uint64>(this);
  return oatpp::utils::Conversion::uint64ToStr(memId);
}

}}
