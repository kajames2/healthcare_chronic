#include "joy_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/joy.h"
#include "healthcare/joy/fractional.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Joy> ReadFractionalJoy(ptree joy_config);

std::unique_ptr<const Joy> ReadJoy(ptree joy_config) {
  std::string type = joy_config.get<std::string>("type");
  std::unique_ptr<const Joy> joy;
  if (type == "Fractional") {
    joy = ReadFractionalJoy(joy_config);
  } else {
    assert(false && "Unsupported Joy type");
    joy = std::unique_ptr<const Joy>();
  }
  return joy;
}

std::unique_ptr<const Joy> ReadFractionalJoy(ptree joy_config) {
  float j = joy_config.get<float>("j");
  return std::make_unique<joy::Fractional>(j);
}

}  // namespace configuration
}  // namespace healthcare
