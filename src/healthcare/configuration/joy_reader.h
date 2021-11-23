#ifndef HEALTHCARE_CONFIGURATION_JOY_READER_H_
#define HEALTHCARE_CONFIGURATION_JOY_READER_H_

#include <iostream>
#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "exprtk.hpp"
#include "healthcare/joy_func.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<JoyFunc> ReadJoy(boost::property_tree::ptree joy_config,
                                 unsigned int max_age, unsigned int max_shocks,
                                 unsigned int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_JOY_READER_H_
