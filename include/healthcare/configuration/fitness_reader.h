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
std::unique_ptr<const healthcare::Fitness> ReadFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadFixedPriceFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadQuadraticCostFitness(
    boost::property_tree::ptree fit_config);
std::unique_ptr<const healthcare::Fitness> ReadFlatLossFitness(
    boost::property_tree::ptree fitness_config);
std::unique_ptr<const healthcare::Fitness> ReadProportionalLossFitness(
    boost::property_tree::ptree fitness_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_FITNESS_READER_H_
