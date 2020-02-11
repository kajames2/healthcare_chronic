#include "modifier_reader.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/modifier.h"
#include "healthcare/modifier/composite.h"
#include "healthcare/modifier/constant.h"
#include "healthcare/modifier/cosine.h"
#include "healthcare/modifier/fractional.h"
#include "healthcare/modifier/linear.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Modifier> ReadConstantModifier(ptree modifier_config,
                                                     modifier::Func);
std::unique_ptr<const Modifier> ReadCosineModifier(ptree modifier_config,
                                                   modifier::Param,
                                                   modifier::Func,
                                                   int max_param);
std::unique_ptr<const Modifier> ReadLinearModifier(ptree modifier_config,
                                                   modifier::Param,
                                                   modifier::Func,
                                                   int max_param);
std::unique_ptr<const Modifier> ReadFractionalModifier(ptree modifier_config,
                                                       modifier::Param,
                                                       modifier::Func);
std::unique_ptr<const Modifier> ReadModifier(ptree modifier_config, int max_age,
                                             int max_shocks, int max_fitness);

std::unique_ptr<const Modifier> ReadModifiers(ptree modifier_config,
                                              int max_age, int max_shocks,
                                              int max_fitness) {
  std::vector<std::shared_ptr<const Modifier>> mods;
  for (auto& cell : modifier_config) {
    mods.push_back(ReadModifier(cell.second, max_age, max_shocks, max_fitness));
  }

  return std::make_unique<modifier::Composite>(mods);
}

std::unique_ptr<const Modifier> ReadModifier(ptree modifier_config, int max_age,
                                             int max_shocks, int max_fitness) {
  std::string type = modifier_config.get<std::string>("type");
  std::string func = modifier_config.get<std::string>("func");
  modifier::Func mod_func;
  if (func == "Add") {
    mod_func = modifier::Func::ADD;
  } else if (func == "Multiply") {
    mod_func = modifier::Func::MULTIPLY;
  } else {
    assert(false && "Unsupported Modifier Function type");
  }
  std::unique_ptr<const Modifier> mod;
  if (type == "Constant") {
    mod = ReadConstantModifier(modifier_config, mod_func);
  } else {
    std::string param = modifier_config.get<std::string>("param");

    int max_param;
    modifier::Param mod_param;
    if (param == "Age") {
      mod_param = modifier::Param::AGE;
      max_param = max_age;
    } else if (param == "Shocks") {
      mod_param = modifier::Param::SHOCKS;
      max_param = max_shocks;
    } else if (param == "Fitness") {
      mod_param = modifier::Param::FITNESS;
      max_param = max_fitness;
    } else {
      assert(false && "Unsupported Modifier Parameter type");
    }

    if (type == "Cosine") {
      mod = ReadCosineModifier(modifier_config, mod_param, mod_func, max_param);
    } else if (type == "Linear") {
      mod = ReadLinearModifier(modifier_config, mod_param, mod_func, max_param);
    } else if (type == "Fractional") {
      mod = ReadFractionalModifier(modifier_config, mod_param, mod_func);
    } else {
      assert(false && "Unsupported Modifier type");
      mod = std::unique_ptr<const Modifier>();
    }
  }
  return mod;
}

std::unique_ptr<const Modifier> ReadConstantModifier(ptree modifier_config,
                                                     modifier::Func func) {
  float max_modification = modifier_config.get<float>("max_modification");
  return std::make_unique<modifier::Constant>(func, max_modification);
}

std::unique_ptr<const Modifier> ReadCosineModifier(ptree modifier_config,
                                                   modifier::Param param,
                                                   modifier::Func func,
                                                   int max_param) {
  float max_modification = modifier_config.get<float>("max_modification");
  return std::make_unique<modifier::Cosine>(param, func, max_modification,
                                            max_param);
}

std::unique_ptr<const Modifier> ReadLinearModifier(ptree modifier_config,
                                                   modifier::Param param,
                                                   modifier::Func func,
                                                   int max_param) {
  float max_modification = modifier_config.get<float>("max_modification");
  return std::make_unique<modifier::Linear>(param, func, max_modification,
                                            max_param);
}

std::unique_ptr<const Modifier> ReadFractionalModifier(ptree modifier_config,
                                                       modifier::Param param,
                                                       modifier::Func func) {
  float j = modifier_config.get<float>("j");
  float max_modification = modifier_config.get<float>("max_modification");
  return std::make_unique<modifier::Fractional>(param, func, max_modification,
                                                j);
}

}  // namespace configuration
}  // namespace healthcare
