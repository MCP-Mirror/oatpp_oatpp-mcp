#ifndef test_app_api_dto_UserDto_hpp
#define test_app_api_dto_UserDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
     VALUE(GUEST, 0, "ROLE_GUEST"),
     VALUE(ADMIN, 1, "ROLE_ADMIN")
)

class UserDto : public oatpp::DTO {
  
  DTO_INIT(UserDto, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, userName, "username");
  DTO_FIELD(String, email, "email");
  DTO_FIELD(String, password, "password");

  DTO_FIELD(Enum<Role>::AsString, role, "role");

  DTO_FIELD(Vector<Object<UserDto>>, friends);

};

#include OATPP_CODEGEN_END(DTO)

#endif /* test_app_api_dto_UserDto_hpp */
