#ifndef _HEALTHCARE_CONFIGURATION_FITNESS_READER_H_
#define _HEALTHCARE_CONFIGURATION_FITNESS_READER_H_

#include <string>

#include "healthcare/fitness.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Fitness> ReadFitnesses(
    boost::property_tree::ptree fitness_config, int max_fitness, int max_budget);
std::unique_ptr<const healthcare::Fitness> ReadFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadFixedPriceFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadFlatLossFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadProportionalLossFitness(
    boost::property_tree::ptree fitness_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_FITNESS_READER_H_
