#include "job_reader.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/job.h"
#include "healthcare/job/age_linear.h"
#include "healthcare/job/defined.h"
#include "healthcare/job/flat.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Job> ReadFlatJob(ptree job_config);
std::unique_ptr<const Job> ReadAgeLinearJob(ptree job_config);
std::unique_ptr<const Job> ReadDefinedJob(ptree job_config);

std::unique_ptr<const Job> ReadJob(ptree job_config) {
  std::string type = job_config.get<std::string>("type");
  std::unique_ptr<const Job> job;
  if (type == "Flat") {
    job = ReadFlatJob(job_config);
  } else if (type == "AgeLinear") {
    job = ReadAgeLinearJob(job_config);
  } else if (type == "Defined") {
    job = ReadDefinedJob(job_config);
  } else {
    assert(false && "Unsupported job type");
    job = std::unique_ptr<const Job>();
  }
  return job;
}

std::unique_ptr<const Job> ReadFlatJob(ptree job_config) {
  int rate = job_config.get<int>("rate");
  return std::make_unique<job::Flat>(rate);
}

std::unique_ptr<const Job> ReadAgeLinearJob(ptree job_config) {
  float intercept = job_config.get<float>("intercept");
  float slope = job_config.get<float>("slope");
  return std::make_unique<job::AgeLinear>(intercept, slope);
}

std::unique_ptr<const Job> ReadDefinedJob(ptree job_config) {
  std::vector<int> incomes;
  for (auto& cell : job_config.get_child("incomes")) {
    incomes.emplace_back(cell.second.get_value<int>());
  }
  return std::make_unique<job::Defined>(incomes);
}

}  // namespace configuration
}  // namespace healthcare
