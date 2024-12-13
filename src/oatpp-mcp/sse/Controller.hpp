//
// Created by Leonid S on 12/8/24.
//

#ifndef OATPP_MCP_SSE_CONTROLLER_HPP
#define OATPP_MCP_SSE_CONTROLLER_HPP

#include "ReadCallback.hpp"

#include "oatpp-mcp/event/Server.hpp"

#include "oatpp/web/protocol/http/outgoing/StreamingBody.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

namespace oatpp { namespace mcp { namespace sse {

class Controller : public oatpp::web::server::api::ApiController {
private:
  std::shared_ptr<event::Server> m_server;
  std::shared_ptr<event::Session::EventListener> m_eventListener;
public:

  Controller(const std::shared_ptr<event::Server>& mcpServer,
             const std::shared_ptr<event::Session::EventListener>& eventListener,
             OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers),
             const oatpp::String& apiPrefix = nullptr)
    : oatpp::web::server::api::ApiController(apiContentMappers, apiPrefix)
    , m_server(mcpServer)
    , m_eventListener(eventListener)
  {}

public:

  ENDPOINT("GET", "sse", sse,
           REQUEST(std::shared_ptr<IncomingRequest>, request))
  {
    auto session = m_server->startNewSession(m_eventListener);

    auto body = std::make_shared<oatpp::web::protocol::http::outgoing::StreamingBody>
      (std::make_shared<ReadCallback>(session, m_routerPrefix));

    auto response = OutgoingResponse::createShared(Status::CODE_200, body);
    response->putHeader("Cache-Control", "no-store");
    response->putHeader("Content-Type", "text/event-stream");

    return response;
  }

  ENDPOINT("POST", "sessions/{sessionId}", mcpPost,
           PATH(String, sessionId),
           BODY_STRING(String, body))
  {
    auto session = m_server->getSession(sessionId);
    if(session) {
      auto stream = session->getInStream();
      event::Event event;
      event.name = "post";
      event.data = body;
      stream->post(event);
    }
    return createResponse(Status::CODE_200, "OK");
  }

};

}}}

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif //OATPP_MCP_SSE_CONTROLLER_HPP
