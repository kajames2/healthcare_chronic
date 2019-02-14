#include "healthcare/configuration/job_reader.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "healthcare/job.h"
#include "healthcare/job/flat.h"
#include "healthcare/job/age_linear.h"
#include "healthcare/job/defined.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace healthcare {
namespace configuration {

std::unique_ptr<const healthcare::Job> ReadJob(
    boost::property_tree::ptree job_config) {
  std::string type = job_config.get<std::string>("type");
  std::unique_ptr<const healthcare::Job> job;
  if (type == "Flat") {
    job = ReadFlatJob(job_config);
  } else if (type == "AgeLinear") {
    job = ReadAgeLinearJob(job_config);
  } else if (type == "Defined") {
    job = ReadDefinedJob(job_config);
  } else {
    assert(false && "Unsupported job type");
    job = std::unique_ptr<const healthcare::Job>();
  }
  return job;
}

std::unique_ptr<const healthcare::Job> ReadFlatJob(
    boost::property_tree::ptree job_config) {
  int rate = job_config.get<int>("rate");
  return std::make_unique<healthcare::job::Flat>(rate);
}

std::unique_ptr<const healthcare::Job> ReadAgeLinearJob(
    boost::property_tree::ptree job_config) {
  float intercept = job_config.get<float>("intercept");
  float slope = job_config.get<float>("slope");
  return std::make_unique<healthcare::job::AgeLinear>(intercept, slope);
}

std::unique_ptr<const healthcare::Job> ReadDefinedJob(
    boost::property_tree::ptree job_config) {
  std::vector<int> incomes;
  for (auto& cell : job_config.get_child("incomes")) {
    incomes.emplace_back(cell.second.get_value<int>());
  }
  return std::make_unique<healthcare::job::Defined>(incomes);
}


}  // namespace configuration
}  // namespace healthcare
