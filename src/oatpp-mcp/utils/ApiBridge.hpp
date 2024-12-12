//
// Created by Leonid S on 12/12/24.
//

#ifndef OATPP_MCP_UTILS_APIBRIDGE_HPP
#define OATPP_MCP_UTILS_APIBRIDGE_HPP

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/AsyncHttpConnectionHandler.hpp"

#include "oatpp/network/ConnectionPool.hpp"

#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/client/ConnectionProvider.hpp"
#include "oatpp/network/virtual_/Interface.hpp"

namespace oatpp { namespace mcp { namespace utils {

/**
 * Class that forwards API calls from MCP to ApiControllers.
 */
class ApiBridge {
private:
  std::shared_ptr<oatpp::network::virtual_::Interface> m_interface;
  std::shared_ptr<oatpp::network::virtual_::Interface> m_asyncInterface;
  std::shared_ptr<oatpp::web::server::HttpRouter> m_router;
  std::shared_ptr<oatpp::web::server::HttpRouter> m_asyncRouter;
private:
  std::shared_ptr<oatpp::network::ServerConnectionProvider> m_serverConnectionProvider;
  std::shared_ptr<oatpp::network::ServerConnectionProvider> m_asyncServerConnectionProvider;
  std::shared_ptr<oatpp::network::ClientConnectionProvider> m_clientConnectionProvider;
  std::shared_ptr<oatpp::network::ClientConnectionProvider> m_asyncClientConnectionProvider;
private:
  std::shared_ptr<oatpp::async::Executor> m_executor;
  std::shared_ptr<oatpp::web::server::HttpConnectionHandler> m_connectionHandler;
  std::shared_ptr<oatpp::web::server::AsyncHttpConnectionHandler> m_asyncConnectionHandler;
private:
  std::shared_ptr<oatpp::web::client::HttpRequestExecutor> m_httpExecutor;
  std::shared_ptr<oatpp::web::client::HttpRequestExecutor> m_asyncHttpExecutor;
public:

  ApiBridge();

  void addEndpoint(const std::shared_ptr<oatpp::web::server::api::Endpoint>& endpoint);

  std::shared_ptr<oatpp::web::client::HttpRequestExecutor> getHttpExecutor() const;
  std::shared_ptr<oatpp::web::client::HttpRequestExecutor> getAsyncHttpExecutor() const;

  void run();

};

}}}

#endif //OATPP_MCP_UTILS_APIBRIDGE_HPP
