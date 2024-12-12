//
// Created by Leonid S on 12/12/24.
//

#ifndef OATPP_MCP_UTILS_JSONSCHEMA_HPP
#define OATPP_MCP_UTILS_JSONSCHEMA_HPP

#include "oatpp/data/mapping/ObjectMapper.hpp"
#include "oatpp/json/ObjectMapper.hpp"

namespace oatpp { namespace mcp { namespace utils {

class ObjectSchemaMapper : public base::Countable {
public:

  struct Config {
    bool useUnqualifiedFieldNames = false;
    bool useUnqualifiedEnumNames = false;
    std::vector<std::string> enabledInterpretations = {};
  };

public:

  struct State {

    const Config* config;
    data::mapping::Tree* tree;
    data::mapping::Tree* defs;
    std::unordered_set<oatpp::String>* knownSchemas;
    data::mapping::ErrorStack errorStack;

  };

public:
  typedef void (*MapperMethod)(const ObjectSchemaMapper*, State&, const oatpp::Type*);
public:

  static void mapBoolean(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapFloat(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapInteger(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapString(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapTree(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapAny(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapEnum(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);

  static void mapCollection(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);
  static void mapMap(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);

  static void mapObject(const ObjectSchemaMapper* mapper, State& state, const oatpp::Type* type);

private:
  oatpp::json::ObjectMapper m_jsonMapper;
  std::vector<MapperMethod> m_methods;
public:

  ObjectSchemaMapper();

  void setMapperMethod(const data::type::ClassId& classId, MapperMethod method);

  void map(State& state, const oatpp::Type* type) const;

  oatpp::data::mapping::Tree map(const oatpp::Type* type, data::mapping::Tree& defs) const;

};

}}}

#endif //OATPP_MCP_UTILS_JSONSCHEMA_HPP
