
#ifndef test_app_api_UserController_hpp
#define test_app_api_UserController_hpp

#include "oatpp-mcp/app/api/dto/PageDto.hpp"
#include "oatpp-mcp/app/api/dto/StatusDto.hpp"
#include "oatpp-mcp/app/api/dto/UserDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController {
public:
  UserController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
public:
  
  ENDPOINT_INFO(createUser) {
    info->summary = "Create new User";

    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "users", createUser,
           BODY_DTO(Object<UserDto>, userDto))
  {
    OATPP_LOGd("UserController", "createUser")
    auto stub = UserDto::createShared();
    return createDtoResponse(Status::CODE_200, stub);
  }
  
  
  ENDPOINT_INFO(putUser) {
    info->summary = "Update User by userId";

    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("PUT", "users/{userId}", putUser,
           PATH(Int32, userId),
           BODY_DTO(Object<UserDto>, userDto))
  {
    OATPP_LOGd("UserController", "putUser")
    userDto->id = userId;
    return createDtoResponse(Status::CODE_200, userDto);
  }
  
  
  ENDPOINT_INFO(getUserById) {
    info->summary = "Get one User by userId";

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("GET", "users/{userId}", getUserById,
           PATH(Int32, userId))
  {
    OATPP_LOGd("UserController", "getUserById")
    auto stub = UserDto::createShared();
    stub->id = userId;
    return createDtoResponse(Status::CODE_200, stub);
  }
  
  
  ENDPOINT_INFO(getUsers) {
    info->summary = "get all stored users";

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/offset/{offset}/limit/{limit}/*", getUsers,
           PATH(UInt32, offset),
           PATH(UInt32, limit),
           QUERY(String, searchPhrase))
  {
    OATPP_LOGd("UserController", "getUsers")
    auto page = UsersPageDto::createShared();
    page->count = 1;
    page->offset = offset;
    page->limit = limit;
    page->items = {};
    return createDtoResponse(Status::CODE_200, page);
  }
  
  
  ENDPOINT_INFO(deleteUser) {
    info->summary = "Delete User by userId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "users/{userId}", deleteUser,
           PATH(Int32, userId))
  {
    OATPP_LOGd("UserController", "createUser")
    auto stub = StatusDto::createShared();
    stub->code = 200;
    stub->status = "Okay";
    stub->message = "Doing just fine";
    return createDtoResponse(Status::CODE_200, stub);
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* test_app_api_UserController_hpp */
