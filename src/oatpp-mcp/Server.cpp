//
// Created by Leonid S on 12/10/24.
//

#include "Server.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"

namespace oatpp { namespace mcp {

Server::Server()
  : m_pinger(std::make_shared<oatpp::mcp::Pinger>())
  , m_eventListener(std::make_shared<oatpp::mcp::Listener>())
  , m_eventServer(std::make_shared<oatpp::mcp::event::Server>(m_pinger))
{
  auto json = std::make_shared<oatpp::json::ObjectMapper>();
  json->serializerConfig().json.useBeautifier = true;

  m_mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
  m_mappers->putMapper(json);
}

void Server::addPrompt(const std::shared_ptr<capabilities::Prompt>& prompt) {
  m_eventListener->addPrompt(prompt);
}

void Server::addTool(const std::shared_ptr<capabilities::Tool>& tool) {
  m_eventListener->addTool(tool);
}

std::shared_ptr<web::server::api::ApiController> Server::getSseController() {
  if(!m_sseController) {
    m_sseController = std::make_shared<oatpp::mcp::sse::Controller>(m_eventServer, m_eventListener, m_mappers);
  }
  return m_sseController;
}

}}
