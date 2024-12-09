//
// Created by Leonid S on 12/9/24.
//

#include "ServerTest.hpp"

#include "tools/Logger.hpp"

#include "oatpp-mcp/sse/Controller.hpp"
#include "oatpp-mcp/Listener.hpp"
#include "oatpp-mcp/Server.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"

namespace oatpp { namespace mcp { namespace app {

namespace {

std::shared_ptr<oatpp::web::mime::ContentMappers> createApiMappers() {
  auto json = std::make_shared<oatpp::json::ObjectMapper>();
  json->serializerConfig().json.useBeautifier = true;

  auto mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
  mappers->putMapper(json);

  return mappers;
}

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

  auto mappers = createApiMappers();

  /* Setup MCP server endpoints */

  auto listener = std::make_shared<oatpp::mcp::Listener>();
  listener->addTool(std::make_shared<tools::Logger>());

  auto mcpServer = std::make_shared<oatpp::mcp::Server>();
  auto sseController = std::make_shared<oatpp::mcp::sse::Controller>(mcpServer, listener, mappers);


  /* Run HTTP server */
  runHttpServer(sseController);

}

}}}
