//
// Created by Leonid S on 12/10/24.
//

#include "Server.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"

#include <iostream>
#include <thread>

namespace oatpp { namespace mcp {

Server::Server()
  : m_pinger(std::make_shared<oatpp::mcp::Pinger>())
  , m_eventListener(std::make_shared<oatpp::mcp::Listener>())
  , m_eventServer(std::make_shared<oatpp::mcp::event::Server>(m_pinger))
{

  m_schemaMapper = std::make_shared<oatpp::mcp::utils::ObjectSchemaMapper>();

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

void Server::addResource(const std::shared_ptr<capabilities::Resource> &resource) {
  m_eventListener->addResource(resource);
}

void Server::addEndpoints(const oatpp::web::server::api::Endpoints& endpoints) {
  for(auto& endpoint : endpoints.list) {
    auto tool = std::make_shared<capabilities::EndpointTool>(endpoint, m_schemaMapper);
    addTool(tool);
  }
}

std::shared_ptr<web::server::api::ApiController> Server::getSseController() {
  if(!m_sseController) {
    m_sseController = std::make_shared<oatpp::mcp::sse::Controller>(m_eventServer, m_eventListener, m_mappers);
  }
  return m_sseController;
}

void Server::stdioListen() {

  auto session = m_eventServer->startNewSession(m_eventListener);

  std::thread tin([session]{
    std::string line;
    while (std::getline(std::cin, line) && session->isOpen()) {
      event::Event e;
      e.name = "stdio";
      e.data = line;
      session->getInStream()->post(e);
    }
  });

  std::thread tout([session]{
    while (session->isOpen()) {
      auto e = session->getOutStream()->read(std::chrono::milliseconds(0) /* wait until event */ );
      std::cout << *e.data << std::endl;
    }
  });

  tin.join();
  tout.join();

}

}}
