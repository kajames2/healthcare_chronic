#ifndef HEALTHCARE_CONFIGURATION_JOB_READER_H_
#define HEALTHCARE_CONFIGURATION_JOB_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::function<int(int, int, int)> ReadJob(
    boost::property_tree::ptree job_config, int max_age, int max_shocks,
    int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_JOB_READER_H_
