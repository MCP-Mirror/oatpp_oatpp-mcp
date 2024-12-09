//
// Created by Leonid S on 12/8/24.
//

#include "Session.hpp"
#include "oatpp/utils/Conversion.hpp"
#include "oatpp/base/Log.hpp"

namespace oatpp { namespace mcp {

Session::Session()
  : m_inStream(std::make_shared<EventStream>())
  , m_outStream(std::make_shared<EventStream>())
  , m_open(true)
{}

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
    auto event = m_inStream->read();
    if(event) {
      listener->onEvent(*this, event);
    }
  }

}

bool Session::isOpen() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_open;
}

void Session::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_open = false;
  m_inStream->close();
  m_outStream->close();
}

oatpp::String Session::getId() const {
  auto memId = reinterpret_cast<v_uint64>(this);
  return oatpp::utils::Conversion::uint64ToStr(memId);
}

}}
