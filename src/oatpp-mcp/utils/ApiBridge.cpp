//
// Created by Leonid S on 12/12/24.
//

#include "ApiBridge.hpp"
#include "oatpp/network/Server.hpp"

#include <thread>

namespace oatpp { namespace mcp { namespace utils {

ApiBridge::ApiBridge() {

  m_interface = oatpp::network::virtual_::Interface::obtainShared("mcp.bridge.virtualhost");
  m_asyncInterface = oatpp::network::virtual_::Interface::obtainShared("async.mcp.bridge.virtualhost");

  m_router = std::make_shared<oatpp::web::server::HttpRouter>();
  m_asyncRouter = std::make_shared<oatpp::web::server::HttpRouter>();

  m_executor = std::make_shared<oatpp::async::Executor>();

  m_serverConnectionProvider = std::make_shared<oatpp::network::virtual_::server::ConnectionProvider>(m_interface);
  m_asyncServerConnectionProvider = std::make_shared<oatpp::network::virtual_::server::ConnectionProvider>(m_asyncInterface);

  m_clientConnectionProvider = std::make_shared<oatpp::network::virtual_::client::ConnectionProvider>(m_interface);
  m_asyncClientConnectionProvider = std::make_shared<oatpp::network::virtual_::client::ConnectionProvider>(m_asyncInterface);

  m_connectionHandler = std::make_shared<oatpp::web::server::HttpConnectionHandler>(m_router);
  m_asyncConnectionHandler = std::make_shared<oatpp::web::server::AsyncHttpConnectionHandler>(m_router, m_executor);

  m_httpExecutor = std::make_shared<oatpp::web::client::HttpRequestExecutor>(m_clientConnectionProvider);
  m_asyncHttpExecutor = std::make_shared<oatpp::web::client::HttpRequestExecutor>(m_asyncClientConnectionProvider);

}

void ApiBridge::addEndpoint(const std::shared_ptr<oatpp::web::server::api::Endpoint>& endpoint) {
  // TODO check is async endpoint and route it view asyncRouter
  m_router->route(endpoint);
}

std::shared_ptr<oatpp::web::client::HttpRequestExecutor> ApiBridge::getHttpExecutor() const {
  return m_httpExecutor;
}

std::shared_ptr<oatpp::web::client::HttpRequestExecutor> ApiBridge::getAsyncHttpExecutor() const {
  return m_asyncHttpExecutor;
}

void ApiBridge::run() {

  std::thread t([this]{
    oatpp::network::Server server(m_serverConnectionProvider, m_connectionHandler);
    server.run();
  });

  std::thread ta([this]{
    oatpp::network::Server server(m_asyncServerConnectionProvider, m_asyncConnectionHandler);
  });

  t.join();
  ta.join();

}

}}}
