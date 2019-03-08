#ifndef HEALTHCARE_CONFIGURATION_FITNESS_READER_H_
#define HEALTHCARE_CONFIGURATION_FITNESS_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/fitness.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Fitness> ReadFitnesses(
    boost::property_tree::ptree fitness_config, int max_fitness,
    int max_budget);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_FITNESS_READER_H_
