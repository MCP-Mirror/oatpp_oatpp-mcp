//
// Created by Leonid S on 12/8/24.
//

#include "EventStream.hpp"

namespace oatpp { namespace mcp {

EventStream::EventStream(v_uint32 maxQueueSize)
  : m_maxQueueSize(maxQueueSize)
  , m_open(true)
{}

void EventStream::post(const Event& event) {

  {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_queue.size() >= m_maxQueueSize || !m_open) {
      return; // discard event
    }

    m_queue.push_back(event);
  }

  m_cv.notify_one();

}

Event EventStream::read() {

  Event result;

  std::unique_lock<std::mutex> lock(m_mutex);

  while (m_queue.empty() && m_open) {
    m_cv.wait(lock);
  }

  if(!m_open) return {};

  result = m_queue.front();
  m_queue.pop_front();

  lock.unlock();
  m_cv.notify_one();

  return result;

}

void EventStream::close() {
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_open = false;
  }
  m_cv.notify_all();
}

}}
