#include "modulator_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/modulator.h"
#include "healthcare/modulator/fitness_cosine.h"
#include "healthcare/modulator/fitness_fractional.h"
#include "healthcare/modulator/fitness_linear.h"
#include "healthcare/modulator/shock_cosine.h"
#include "healthcare/modulator/shock_fractional.h"
#include "healthcare/modulator/shock_linear.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Modulator> ReadFitnessCosineModulator(
    ptree modulator_config, int max_fitness);
std::unique_ptr<const Modulator> ReadFitnessLinearModulator(
    ptree modulator_config, int max_fitness);
std::unique_ptr<const Modulator> ReadFitnessFractionalModulator(
    ptree modulator_config);
std::unique_ptr<const Modulator> ReadShockCosineModulator(
    ptree modulator_config, int max_shocks);
std::unique_ptr<const Modulator> ReadShockLinearModulator(
    ptree modulator_config, int max_shocks);
std::unique_ptr<const Modulator> ReadShockFractionalModulator(
    ptree modulator_config);

std::unique_ptr<const Modulator> ReadModulator(ptree modulator_config,
                                               int max_shocks,
                                               int max_fitness) {
  std::string type = modulator_config.get<std::string>("type");
  std::unique_ptr<const Modulator> mod;
  if (type == "FitnessCosine") {
    mod = ReadFitnessCosineModulator(modulator_config, max_fitness);
  } else if (type == "FitnessLinear") {
    mod = ReadFitnessLinearModulator(modulator_config, max_fitness);
  } else if (type == "FitnessFractional") {
    mod = ReadFitnessFractionalModulator(modulator_config);
  } else if (type == "ShockCosine") {
    mod = ReadShockCosineModulator(modulator_config, max_shocks);
  } else if (type == "ShockLinear") {
    mod = ReadShockLinearModulator(modulator_config, max_shocks);
  } else if (type == "ShockFractional") {
    mod = ReadShockFractionalModulator(modulator_config);
  } else {
    assert(false && "Unsupported Modulator type");
    mod = std::unique_ptr<const Modulator>();
  }
  return mod;
}

std::unique_ptr<const Modulator> ReadFitnessCosineModulator(
    ptree modulator_config, int max_fitness) {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::FitnessCosine>(max_modulation,
                                                    max_fitness);
}

std::unique_ptr<const Modulator> ReadFitnessLinearModulator(
    ptree modulator_config, int max_fitness) {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::FitnessLinear>(max_modulation,
                                                    max_fitness);
}

std::unique_ptr<const Modulator> ReadFitnessFractionalModulator(
    ptree modulator_config) {
  float j = modulator_config.get<float>("j");
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::FitnessFractional>(max_modulation, j);
}

std::unique_ptr<const Modulator> ReadShockCosineModulator(
    ptree modulator_config, int max_shocks) {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::ShockCosine>(max_modulation, max_shocks);
}

std::unique_ptr<const Modulator> ReadShockLinearModulator(
    ptree modulator_config, int max_shocks) {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::ShockLinear>(max_modulation, max_shocks);
}

std::unique_ptr<const Modulator> ReadShockFractionalModulator(
    ptree modulator_config) {
  float j = modulator_config.get<float>("j");
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<modulator::ShockFractional>(max_modulation, j);
}

}  // namespace configuration
}  // namespace healthcare
