add_executable(module-tests
        oatpp-mcp/app/prompts/CodeReview.cpp
        oatpp-mcp/app/prompts/CodeReview.hpp
        oatpp-mcp/app/tools/Logger.cpp
        oatpp-mcp/app/tools/Logger.hpp
        oatpp-mcp/app/ServerTest.cpp
        oatpp-mcp/app/ServerTest.hpp
        oatpp-mcp/tests.cpp
        oatpp-mcp/app/resources/File.hpp
        oatpp-mcp/app/resources/File.cpp
)

set_target_properties(module-tests PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(module-tests
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

if(OATPP_MODULES_LOCATION STREQUAL OATPP_MODULES_LOCATION_EXTERNAL)
    add_dependencies(module-tests ${LIB_OATPP_EXTERNAL})
endif()

add_dependencies(module-tests ${OATPP_THIS_MODULE_NAME})

target_link_oatpp(module-tests)

target_link_libraries(module-tests
        PRIVATE ${OATPP_THIS_MODULE_NAME}
)

## TODO link dependencies here (if some)

add_test(module-tests module-tests)