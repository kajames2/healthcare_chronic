#ifndef HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_
#define HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/modulator.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Modulator> ReadModulator(
    boost::property_tree::ptree modulator_config, int max_shocks,
    int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_MODULATOR_READER_H_
