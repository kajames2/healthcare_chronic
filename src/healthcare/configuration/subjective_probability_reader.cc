#include "subjective_probability_reader.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "exprtk.hpp"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<ProbDepFunc> ReadSubjectiveProbability(
    ptree prob_config, unsigned int max_age, unsigned int max_shocks,
    unsigned int max_fitness) {
  std::string func_str = prob_config.get<std::string>("function");
  std::unordered_map<std::string, double> const_map;
  for (auto it : prob_config) {
    boost::optional<float> f = it.second.get_value_optional<float>();
    if (f) {
      const_map[it.first] = f.value();
    }
  }
  return std::make_unique<ProbDepFunc>(func_str, const_map, max_age, max_shocks,
                                       max_fitness);
}

}  // namespace configuration
}  // namespace healthcare
