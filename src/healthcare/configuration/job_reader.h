#ifndef HEALTHCARE_CONFIGURATION_JOB_READER_H_
#define HEALTHCARE_CONFIGURATION_JOB_READER_H_

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include "healthcare/job.h"

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Job> ReadJob(
    boost::property_tree::ptree job_config);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_JOB_READER_H_
