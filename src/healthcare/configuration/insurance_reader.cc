#include "insurance_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/configuration.h"
#include "healthcare/insurance.h"
#include "healthcare/insurance/actuarial.h"
#include "healthcare/insurance/fixed.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Insurance> ReadActuarialInsurance(
    ptree insure_config, const Configuration& config);
std::unique_ptr<const Insurance> ReadFixedInsurance(ptree insure_config);

std::unique_ptr<const Insurance> ReadInsurance(ptree insure_config,
                                               const Configuration& config) {
  std::string type = insure_config.get<std::string>("type");
  std::unique_ptr<const Insurance> insure;
  if (type == "Actuarial") {
    insure = ReadActuarialInsurance(insure_config, config);
  } else if (type == "Fixed") {
    insure = ReadFixedInsurance(insure_config);
  } else {
    assert(false && "Unsupported Insurance type");
    insure = std::unique_ptr<const Insurance>();
  }
  return insure;
}

std::unique_ptr<const Insurance> ReadActuarialInsurance(
    ptree insure_config, const Configuration& config) {
  float scale = insure_config.get<float>("scale");
  std::shared_ptr<const Probability> prob = config.shock_prob;
  return std::make_unique<insurance::Actuarial>(scale, config.shock_income_size,
                                                prob);
}

std::unique_ptr<const Insurance> ReadFixedInsurance(ptree insure_config) {
  int premium = insure_config.get<int>("premium");
  return std::make_unique<insurance::Fixed>(premium);
}

}  // namespace configuration
}  // namespace healthcare
