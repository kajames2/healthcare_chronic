#ifndef HEALTHCARE_CONFIGURATION_SUBJECTIVE_PROBABILITY_READER_H_
#define HEALTHCARE_CONFIGURATION_SUBJECTIVE_PROBABILITY_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::function<float(int, int, int, float)> ReadSubjectiveProbability(
    boost::property_tree::ptree prob_config, int max_age, int max_shocks,
    int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_SUBJECTIVE_PROBABILITY_READER_H_
