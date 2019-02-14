#ifndef _HEALTHCARE_CONFIGURATION_JOB_READER_H_
#define _HEALTHCARE_CONFIGURATION_JOB_READER_H_

#include <string>

#include "healthcare/job.h"

#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Job> ReadJob(
    boost::property_tree::ptree job_config);
std::unique_ptr<const healthcare::Job> ReadFlatJob(
    boost::property_tree::ptree job_config);
std::unique_ptr<const healthcare::Job> ReadAgeLinearJob(
    boost::property_tree::ptree job_config);
std::unique_ptr<const healthcare::Job> ReadDefinedJob(
    boost::property_tree::ptree job_config);
}  // namespace configuration
}  // namespace healthcare

#endif  // _HEALTHCARE_CONFIGURATION_JOB_READER_H_
