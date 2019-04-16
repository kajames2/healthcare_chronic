#include "fitness_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/fitness.h"
#include "healthcare/fitness/composite.h"
#include "healthcare/fitness/fixed_price.h"
#include "healthcare/fitness/flat_loss.h"
#include "healthcare/fitness/proportional_loss.h"
#include "healthcare/fitness/quadratic_cost.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Fitness> ReadFitness(ptree fitness_config);
std::unique_ptr<const Fitness> ReadFixedPriceFitness(ptree fitness_config);
std::unique_ptr<const Fitness> ReadQuadraticCostFitness(ptree fit_config);
std::unique_ptr<const Fitness> ReadFlatLossFitness(ptree fitness_config);
std::unique_ptr<const Fitness> ReadProportionalLossFitness(
    ptree fitness_config);

std::unique_ptr<const Fitness> ReadFitnesses(ptree fit_config, int max_fitness,
                                             int max_budget) {
  std::vector<std::shared_ptr<const Fitness>> fits;
  for (auto& cell : fit_config) {
    fits.push_back(ReadFitness(cell.second));
  }

  return std::make_unique<fitness::Composite>(max_fitness, max_budget, fits);
}

std::unique_ptr<const Fitness> ReadFitness(ptree fit_config) {
  std::string type = fit_config.get<std::string>("type");
  std::unique_ptr<const Fitness> fit;
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
    fit = std::unique_ptr<const Fitness>();
  }
  return fit;
}

std::unique_ptr<const Fitness> ReadFixedPriceFitness(ptree fit_config) {
  double price = fit_config.get<double>("price");
  return std::make_unique<fitness::FixedPrice>(price);
}

std::unique_ptr<const Fitness> ReadQuadraticCostFitness(ptree fit_config) {
  float coeff = fit_config.get<float>("coeff");
  return std::make_unique<fitness::QuadraticCost>(coeff);
}

std::unique_ptr<const Fitness> ReadFlatLossFitness(ptree fit_config) {
  int degen = fit_config.get<int>("degen");
  return std::make_unique<fitness::FlatLoss>(degen);
}

std::unique_ptr<const Fitness> ReadProportionalLossFitness(ptree fit_config) {
  float rate = fit_config.get<float>("rate");
  return std::make_unique<fitness::ProportionalLoss>(rate);
}

}  // namespace configuration
}  // namespace healthcare
