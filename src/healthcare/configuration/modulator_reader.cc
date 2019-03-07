#include "healthcare/configuration/modulator_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/modulator.h"
#include "healthcare/modulator/fitness_cosine.h"
#include "healthcare/modulator/fitness_fractional.h"
#include "healthcare/modulator/fitness_linear.h"
#include "healthcare/modulator/shock_cosine.h"
#include "healthcare/modulator/shock_fractional.h"
#include "healthcare/modulator/shock_linear.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Modulator> ReadModulator(
    boost::property_tree::ptree modulator_config, int max_shocks, int max_fitness) {
  std::string type = modulator_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Modulator> mod;
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
    mod = std::unique_ptr<const healthcare::Modulator>();
  }
  return mod;
}

std::unique_ptr<const healthcare::Modulator> ReadFitnessCosineModulator(
    boost::property_tree::ptree modulator_config, int max_fitness)  {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::FitnessCosine>(max_modulation, max_fitness);
}

std::unique_ptr<const healthcare::Modulator> ReadFitnessLinearModulator(
    boost::property_tree::ptree modulator_config, int max_fitness)  {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::FitnessLinear>(max_modulation, max_fitness);
}

std::unique_ptr<const healthcare::Modulator> ReadFitnessFractionalModulator(
    boost::property_tree::ptree modulator_config) {
  float j = modulator_config.get<float>("j");
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::FitnessFractional>(max_modulation, j);
}

std::unique_ptr<const healthcare::Modulator> ReadShockCosineModulator(
    boost::property_tree::ptree modulator_config, int max_shocks)  {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::ShockCosine>(max_modulation, max_shocks);
}

std::unique_ptr<const healthcare::Modulator> ReadShockLinearModulator(
    boost::property_tree::ptree modulator_config, int max_shocks)  {
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::ShockLinear>(max_modulation, max_shocks);
}

std::unique_ptr<const healthcare::Modulator> ReadShockFractionalModulator(
    boost::property_tree::ptree modulator_config) {
  float j = modulator_config.get<float>("j");
  float max_modulation = modulator_config.get<float>("max_modulation");
  return std::make_unique<healthcare::modulator::ShockFractional>(max_modulation, j);
}

}  // namespace configuration
}  // namespace healthcare
