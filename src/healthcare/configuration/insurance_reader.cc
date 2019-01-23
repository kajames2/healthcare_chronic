#include "healthcare/configuration/insurance_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/insurance.h"
#include "healthcare/insurance/actuarial.h"
#include "healthcare/insurance/fixed.h"
#include "healthcare/configuration.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Insurance> ReadInsurance(
    boost::property_tree::ptree insure_config, const Configuration& config) {
  std::string type = insure_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Insurance> insure;
  if (type == "Actuarial") {
    insure = ReadActuarialInsurance(insure_config, config);
  } else if (type == "Fixed") {
    insure = ReadFixedInsurance(insure_config);
  } else {
    assert(false && "Unsupported Insurance type");
    insure = std::unique_ptr<const healthcare::Insurance>();
  }
  return insure;
}

std::unique_ptr<const healthcare::Insurance> ReadActuarialInsurance(
    boost::property_tree::ptree insure_config, const Configuration& config) {
  float scale = insure_config.get<float>("scale");
  std::shared_ptr<const healthcare::Probability> prob = config.shock_prob;
  return std::make_unique<healthcare::insurance::Actuarial>(
      scale, config.shock_income_size, prob);
}

std::unique_ptr<const healthcare::Insurance> ReadFixedInsurance(
    boost::property_tree::ptree insure_config) {
  int premium = insure_config.get<int>("premium");
  return std::make_unique<healthcare::insurance::Fixed>(premium);
}

}  // namespace configuration
}  // namespace healthcare
