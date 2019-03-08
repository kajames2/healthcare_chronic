#include "prob_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/probability.h"
#include "healthcare/probability/gompertz_makeham.h"
#include "healthcare/probability/gompertz_shocks.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Probability> ReadGompertzMakehamProb(ptree prob_config);
std::unique_ptr<const Probability> ReadGompertzShocksProb(ptree prob_config);

std::unique_ptr<const Probability> ReadProb(ptree prob_config) {
  std::string type = prob_config.get<std::string>("type");
  std::unique_ptr<const Probability> prob;
  if (type == "GompertzMakeham") {
    prob = ReadGompertzMakehamProb(prob_config);
  } else if (type == "GompertzShocks") {
    prob = ReadGompertzShocksProb(prob_config);
  } else {
    assert(false && "Unsupported Probability type");
    prob = std::unique_ptr<const Probability>();
  }
  return prob;
}

std::unique_ptr<const Probability> ReadGompertzMakehamProb(ptree prob_config) {
  float lambda = prob_config.get<float>("lambda");
  float alpha = prob_config.get<float>("alpha");
  float beta = prob_config.get<float>("beta");
  return std::make_unique<probability::GompertzMakeham>(lambda, alpha, beta);
}

std::unique_ptr<const Probability> ReadGompertzShocksProb(ptree prob_config) {
  float age_coeff = prob_config.get<float>("age_coeff");
  float age_rate = prob_config.get<float>("age_rate");
  float shock_coeff = prob_config.get<float>("shock_coeff");
  float shock_rate = prob_config.get<float>("shock_rate");
  return std::make_unique<probability::GompertzShocks>(age_coeff, age_rate,
                                                       shock_coeff, shock_rate);
}

}  // namespace configuration
}  // namespace healthcare
