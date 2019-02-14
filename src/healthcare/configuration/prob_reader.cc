#include "healthcare/configuration/prob_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/probability.h"
#include "healthcare/probability/gompertz_makeham.h"
#include "healthcare/probability/gompertz_shocks.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Probability> ReadProb(
    boost::property_tree::ptree prob_config, int max_fitness) {
  std::string type = prob_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Probability> prob;
  if (type == "GompertzMakeham") {
    prob = ReadGompertzMakehamProb(prob_config);
  } else if (type == "GompertzShocks") {
    prob = ReadGompertzShocksProb(prob_config, max_fitness);
  } else {
    assert(false && "Unsupported Probability type");
    prob = std::unique_ptr<const healthcare::Probability>();
  }
  return prob;
}

std::unique_ptr<const healthcare::Probability> ReadGompertzMakehamProb(
    boost::property_tree::ptree prob_config) {
  float lambda = prob_config.get<float>("lambda");
  float alpha = prob_config.get<float>("alpha");
  float beta = prob_config.get<float>("beta");
  return std::make_unique<healthcare::probability::GompertzMakeham>(
      lambda, alpha, beta);
}

std::unique_ptr<const healthcare::Probability> ReadGompertzShocksProb(
    boost::property_tree::ptree prob_config, int max_fitness) {
  float age_coeff = prob_config.get<float>("age_coeff");
  float age_rate = prob_config.get<float>("age_rate");
  float shock_coeff = prob_config.get<float>("shock_coeff");
  float shock_rate = prob_config.get<float>("shock_rate");
  float max_fitness_mod = prob_config.get<float>("max_fitness_modifier");
  return std::make_unique<healthcare::probability::GompertzShocks>(
      age_coeff, age_rate, shock_coeff, shock_rate, max_fitness_mod,
      max_fitness);
}

}  // namespace configuration
}  // namespace healthcare
