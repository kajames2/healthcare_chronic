#ifndef _HEALTHCARE_CONFIGURATION_PROB_READER_H_
#define _HEALTHCARE_CONFIGURATION_PROB_READER_H_

#include <string>

#include "healthcare/probability.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Probability> ReadProb(
    boost::property_tree::ptree prob_config);
std::unique_ptr<const healthcare::Probability> ReadGompertzMakehamProb(
    boost::property_tree::ptree prob_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_PROB_READER_H_
