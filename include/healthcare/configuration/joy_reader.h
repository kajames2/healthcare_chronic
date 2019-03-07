#ifndef _HEALTHCARE_CONFIGURATION_JOY_READER_H_
#define _HEALTHCARE_CONFIGURATION_JOY_READER_H_

#include <string>

#include "healthcare/enjoyment.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Enjoyment> ReadEnjoyment(
    boost::property_tree::ptree joy_config);
std::unique_ptr<const healthcare::Enjoyment> ReadFractionalJoy(
    boost::property_tree::ptree joy_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_JOY_READER_H_
