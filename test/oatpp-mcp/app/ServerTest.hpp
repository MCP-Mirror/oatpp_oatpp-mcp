//
// Created by Leonid S on 12/9/24.
//

#ifndef OATPP_MCP_APP_SERVERTEST_HPP
#define OATPP_MCP_APP_SERVERTEST_HPP

#include "oatpp-test/UnitTest.hpp"

namespace oatpp { namespace mcp { namespace app {

class ServerTest : public oatpp::test::UnitTest {
public:

  ServerTest() : UnitTest("TEST[app::ServerTest]"){}
  void onRun() override;

};

}}}

#endif //OATPP_MCP_APP_SERVERTEST_HPP
