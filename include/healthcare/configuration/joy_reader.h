#ifndef HEALTHCARE_CONFIGURATION_JOY_READER_H_
#define HEALTHCARE_CONFIGURATION_JOY_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/enjoyment.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Enjoyment> ReadEnjoyment(
    boost::property_tree::ptree joy_config);
std::unique_ptr<const healthcare::Enjoyment> ReadFractionalJoy(
    boost::property_tree::ptree joy_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_JOY_READER_H_
