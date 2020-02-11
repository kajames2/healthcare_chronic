#include "shifter_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/shifter.h"
#include "healthcare/shifter/constant.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Shifter> ReadConstantShifter(
    ptree shifter_config, int max_shocks);
std::unique_ptr<const Shifter> ReadShifter(ptree shifter_config,
                                           int max_age,
                                           int max_shocks,
                                           int max_fitness) {
  std::string type = shifter_config.get<std::string>("type");
  std::unique_ptr<const Shifter> shift;
  if (type == "Constant") {
    shift = ReadConstantShifter(shifter_config, max_shocks);
  }
  return shift;
}

std::unique_ptr<const Shifter> ReadConstantShifter(
    ptree shifter_config, int max_shocks) {
  float shift = shifter_config.get<float>("shift");
  return std::make_unique<shifter::Constant>(shift, max_shocks);
}

}  // namespace configuration
}  // namespace healthcare
