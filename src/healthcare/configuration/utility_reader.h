#ifndef HEALTHCARE_CONFIGURATION_UTILITY_READER_H_
#define HEALTHCARE_CONFIGURATION_UTILITY_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/utility_func.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<UtilityFunc> ReadUtility(
    boost::property_tree::ptree util_config, unsigned int max_age,
    unsigned int max_shocks, unsigned int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_UTILITY_READER_H_
