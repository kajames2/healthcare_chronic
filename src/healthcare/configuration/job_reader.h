#ifndef HEALTHCARE_CONFIGURATION_JOB_READER_H_
#define HEALTHCARE_CONFIGURATION_JOB_READER_H_

#include <memory>
#include <string>
#include "healthcare/job_func.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<JobFunc> ReadJob(boost::property_tree::ptree job_config,
                                 unsigned int max_age, unsigned int max_shocks,
                                 unsigned int max_fitness);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_JOB_READER_H_
