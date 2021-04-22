#ifndef HEALTHCARE_CONFIGURATION_UTILITY_READER_H_
#define HEALTHCARE_CONFIGURATION_UTILITY_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::function<double(int, int, int, double)> ReadUtility(
    boost::property_tree::ptree util_config, int max_age, int max_shocks,
    int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_UTILITY_READER_H_
