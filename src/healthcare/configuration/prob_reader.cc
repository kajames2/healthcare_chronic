#include "healthcare/configuration/prob_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/probability.h"
#include "healthcare/probability/gompertz_makeham.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Probability> ReadProb(
    boost::property_tree::ptree prob_config) {
  std::string type = prob_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Probability> prob;
  if (type == "GompertzMakeham") {
    prob = ReadGompertzMakehamProb(prob_config);
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
  return std::make_unique<healthcare::probability::GompertzMakeham>(lambda, alpha, beta);
}

}  // namespace configuration
}  // namespace healthcare
