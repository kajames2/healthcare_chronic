#include "healthcare/configuration/fitness_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/fitness.h"
#include "healthcare/fitness/composite.h"
#include "healthcare/fitness/fixed_price.h"
#include "healthcare/fitness/flat_loss.h"
#include "healthcare/fitness/proportional_loss.h"
#include "healthcare/fitness/quadratic_cost.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Fitness> ReadFitnesses(
    boost::property_tree::ptree fit_config, int max_fitness, int max_budget) {
  std::vector<std::shared_ptr<const healthcare::Fitness>> fits;
  for (auto& cell : fit_config) {
    fits.push_back(
        ReadFitness(cell.second));
  }
  
  return std::make_unique<healthcare::fitness::Composite>(
      max_fitness, max_budget, fits);
}

std::unique_ptr<const healthcare::Fitness> ReadFitness(
    boost::property_tree::ptree fit_config) {
  std::string type = fit_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Fitness> fit;
  if (type == "FixedPrice") {
    fit = ReadFixedPriceFitness(fit_config);
  } else if (type == "FlatLoss") {
    fit = ReadFlatLossFitness(fit_config);
  } else if (type == "ProportionalLoss") {
    fit = ReadProportionalLossFitness(fit_config);
  } else if (type == "QuadraticCost") {
    fit = ReadQuadraticCostFitness(fit_config);
  } else {
    assert(false && "Unsupported Fitness type");
    fit = std::unique_ptr<const healthcare::Fitness>();
  }
  return fit;
}


std::unique_ptr<const healthcare::Fitness> ReadFixedPriceFitness(
    boost::property_tree::ptree fit_config) {
  int price = fit_config.get<int>("price");
  return std::make_unique<healthcare::fitness::FixedPrice>(price);
}

std::unique_ptr<const healthcare::Fitness> ReadQuadraticCostFitness(
    boost::property_tree::ptree fit_config) {
  int coeff = fit_config.get<int>("coeff");
  return std::make_unique<healthcare::fitness::QuadraticCost>(coeff);
}

std::unique_ptr<const healthcare::Fitness> ReadFlatLossFitness(
    boost::property_tree::ptree fit_config) {
  int degen = fit_config.get<int>("degen");
  return std::make_unique<healthcare::fitness::FlatLoss>(degen);
}

std::unique_ptr<const healthcare::Fitness> ReadProportionalLossFitness(
    boost::property_tree::ptree fit_config) {
  float rate = fit_config.get<float>("rate");
  return std::make_unique<healthcare::fitness::ProportionalLoss>(rate);
}

}  // namespace configuration
}  // namespace healthcare
