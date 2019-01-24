#ifndef _HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_
#define _HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_

#include <string>

#include "healthcare/configuration.h"
#include "healthcare/insurance.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Insurance> ReadInsurance(
    boost::property_tree::ptree insure_config, const Configuration& config);
std::unique_ptr<const healthcare::Insurance> ReadActuarialInsurance(
    boost::property_tree::ptree insure_config, const Configuration& config);
std::unique_ptr<const healthcare::Insurance> ReadFixedInsurance(
    boost::property_tree::ptree insure_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_
