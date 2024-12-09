//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_SSE_READCALLBACK_HPP
#define OATPP_MCP_SSE_READCALLBACK_HPP

#include "oatpp-mcp/Session.hpp"

#include "oatpp/data/stream/Stream.hpp"

namespace oatpp { namespace mcp { namespace sse {

class ReadCallback : public oatpp::data::stream::ReadCallback {
private:
  std::shared_ptr<Session> m_session;
  bool m_initialized;
private:
  oatpp::String m_currMessage;
  oatpp::data::buffer::InlineWriteData m_inlineData;
public:

  ReadCallback(const std::shared_ptr<Session>& session);

  ~ReadCallback() override;

  oatpp::String initEvent();
  oatpp::String waitEvent();
  oatpp::v_io_size read(void *buffer, v_buff_size count, oatpp::async::Action& action) override;

};

}}}

#endif //OATPP_MCP_SSE_READCALLBACK_HPP
