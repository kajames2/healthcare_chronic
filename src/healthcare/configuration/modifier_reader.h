#ifndef HEALTHCARE_CONFIGURATION_MODIFIER_READER_H_
#define HEALTHCARE_CONFIGURATION_MODIFIER_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/modifier.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Modifier> ReadModifiers(
    boost::property_tree::ptree modifier_config, int max_age, int max_shocks,
    int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_MODIFIER_READER_H_
