#ifndef HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_
#define HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/configuration.h"
#include "healthcare/insurance.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Insurance> ReadInsurance(
    boost::property_tree::ptree insure_config, const Configuration& config);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_INSURANCE_READER_H_
