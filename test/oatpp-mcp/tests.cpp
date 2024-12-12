#include "oatpp-mcp/app/ServerTest.hpp"

#include <iostream>

namespace {

class SilentLogger : public oatpp::Logger {
public:

  void log(v_uint32 priority, const std::string& tag, const std::string& message) override {
    // Do nothing
  }

};

void runTests() {
  OATPP_RUN_TEST(oatpp::mcp::app::ServerTest);
}

}

int main() {

  oatpp::Environment::init(
    std::make_shared<SilentLogger>()
  );

  runTests();

  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

  OATPP_ASSERT(oatpp::Environment::getObjectsCount() == 0);

  oatpp::Environment::destroy();

  return 0;
}
