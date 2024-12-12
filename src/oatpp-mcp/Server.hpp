//
// Created by Leonid S on 12/10/24.
//

#ifndef OATPP_MCP_SERVER_HPP
#define OATPP_MCP_SERVER_HPP

#include "Listener.hpp"

#include "event/Server.hpp"
#include "sse/Controller.hpp"

#include "utils/ApiBridge.hpp"

namespace oatpp { namespace mcp {

class Server {
private:
  std::shared_ptr<oatpp::mcp::Pinger> m_pinger;
  std::shared_ptr<oatpp::mcp::Listener> m_eventListener;
  std::shared_ptr<oatpp::mcp::event::Server> m_eventServer;
private:
  std::shared_ptr<oatpp::mcp::utils::ObjectSchemaMapper> m_schemaMapper;
  std::shared_ptr<oatpp::web::mime::ContentMappers> m_mappers;
  std::shared_ptr<oatpp::mcp::sse::Controller> m_sseController;
private:
  std::shared_ptr<utils::ApiBridge> m_apiBridge;
public:

  Server();

  virtual ~Server() = default;

  void addPrompt(const std::shared_ptr<capabilities::Prompt>& prompt);
  void addTool(const std::shared_ptr<capabilities::Tool>& tool);
  void addResource(const std::shared_ptr<capabilities::Resource>& resource);

  void addEndpoints(const oatpp::web::server::api::Endpoints& endpoints);

  /**
   * (Lazy) Get ApiController with endpoints for
   * Server-Sent-Events
   * @return
   */
  std::shared_ptr<web::server::api::ApiController> getSseController();

  /**
   * Listen to stdio.
   * Make sure this server is the only one who reads/writes to stdio.
   */
  void stdioListen();

};

}}

#endif //OATPP_MCP_SERVER_HPP
