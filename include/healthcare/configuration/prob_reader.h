#ifndef HEALTHCARE_CONFIGURATION_PROB_READER_H_
#define HEALTHCARE_CONFIGURATION_PROB_READER_H_

#include <string>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/probability.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Probability> ReadProb(
    boost::property_tree::ptree prob_config);
std::unique_ptr<const healthcare::Probability> ReadGompertzMakehamProb(
    boost::property_tree::ptree prob_config);
std::unique_ptr<const healthcare::Probability> ReadGompertzShocksProb(
    boost::property_tree::ptree prob_config);
}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_PROB_READER_H_
