//
// Created by Leonid S on 12/9/24.
//

#include "ServerTest.hpp"

#include "prompts/CodeReview.hpp"
#include "tools/Logger.hpp"
#include "resources/File.hpp"

#include "oatpp-mcp/Server.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"

#include <iostream>

namespace oatpp { namespace mcp { namespace app {

namespace {

void runHttpServer(const std::shared_ptr<oatpp::web::server::api::ApiController>& controller) {

  auto router = oatpp::web::server::HttpRouter::createShared();
  router->addController(controller);

  auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared
    ({"0.0.0.0", 3001, oatpp::network::Address::IP_4});

  auto connectionHandler =  oatpp::web::server::HttpConnectionHandler::createShared(router);
  oatpp::network::Server server(connectionProvider, connectionHandler);

  OATPP_LOGi("MyApp", "Server running on port {}", connectionProvider->getProperty("port").toString());
  server.run();

}

}

void ServerTest::onRun() {

  /* Create MCP server */
  oatpp::mcp::Server server;

  /* Add prompts */
  server.addPrompt(std::make_shared<prompts::CodeReview>());

  /* Add tools */
  server.addTool(std::make_shared<tools::Logger>());

  /* Add resource */
  server.addResource(std::make_shared<resource::File>());

  //server.stdioListen();

  /* Run HTTP server */
  runHttpServer(server.getSseController());

}

}}}
