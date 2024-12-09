//
// Created by Leonid S on 12/8/24.
//

#include "EventStream.hpp"

namespace oatpp { namespace mcp { namespace event {

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

Event EventStream::read(const std::chrono::duration<v_int64, std::milli>& timeout) {

  Event result;

  std::unique_lock<std::mutex> lock(m_mutex);

  if(timeout.count() == 0) {
    while (m_queue.empty() && m_open) {
      m_cv.wait(lock);
    }
  } else {
    auto now = std::chrono::system_clock::now();
    auto waitUntil = now + timeout;
    while (m_queue.empty() && m_open && now < waitUntil) {
      m_cv.wait_until(lock, waitUntil);
      now = std::chrono::system_clock::now();
    }
  }

  if(!m_open || m_queue.empty()) return {};

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

bool EventStream::isOpen() {
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_open;
}

}}}
