#ifndef _HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_
#define _HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_

#include <string>

#include "healthcare/modulator.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Modulator> ReadModulator(
    boost::property_tree::ptree modulator_config, int max_shocks, int max_fitness);
std::unique_ptr<const healthcare::Modulator> ReadFitnessCosineModulator(
    boost::property_tree::ptree modulator_config, int max_fitness);
std::unique_ptr<const healthcare::Modulator> ReadFitnessLinearModulator(
    boost::property_tree::ptree modulator_config, int max_fitness);
std::unique_ptr<const healthcare::Modulator> ReadFitnessFractionalModulator(
    boost::property_tree::ptree modulator_config);
std::unique_ptr<const healthcare::Modulator> ReadShockCosineModulator(
    boost::property_tree::ptree modulator_config, int max_shocks);
std::unique_ptr<const healthcare::Modulator> ReadShockLinearModulator(
    boost::property_tree::ptree modulator_config, int max_shocks);
std::unique_ptr<const healthcare::Modulator> ReadShockFractionalModulator(
    boost::property_tree::ptree modulator_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_
