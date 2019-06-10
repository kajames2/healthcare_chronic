#include "joy_reader.h"

#include <cassert>
#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "healthcare/joy.h"
#include "healthcare/joy/fractional.h"
#include "healthcare/joy/health_dependent.h"
#include "healthcare/joy/health_dependent_steve.h"
#include "healthcare/joy/health_dependent_dustin.h"
#include "healthcare/joy/health_dependent_fan.h"
#include "healthcare/joy/mod_decorator.h"
#include "modulator_reader.h"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::unique_ptr<const Joy> ReadFractionalJoy(ptree joy_config);
std::unique_ptr<const Joy> ReadHealthDependentJoy(ptree joy_config,
                                                  int max_shocks);
std::unique_ptr<const Joy> ReadHealthDependentJoySteve(ptree joy_config,
                                                  int max_shocks);
std::unique_ptr<const Joy> ReadHealthDependentJoyDustin(ptree joy_config,
                                                  int max_shocks);
std::unique_ptr<const Joy> ReadHealthDependentJoyFan(ptree joy_config,
                                                  int max_shocks, int max_fitness);

std::unique_ptr<const Joy> ReadJoy(ptree joy_config, int max_shocks,
                                   int max_fitness) {
  std::string type = joy_config.get<std::string>("type");
  std::unique_ptr<const Joy> joy;
  if (type == "Fractional") {
    joy = ReadFractionalJoy(joy_config);
  } else if (type == "HealthDependent") {
    joy = ReadHealthDependentJoy(joy_config, max_shocks);
  } else if (type == "HealthDependentSteve") {
    joy = ReadHealthDependentJoySteve(joy_config, max_shocks);
  } else if (type == "HealthDependentDustin") {
    joy = ReadHealthDependentJoyDustin(joy_config, max_shocks);
  } else if (type == "HealthDependentFan") {
    joy = ReadHealthDependentJoyFan(joy_config, max_shocks, max_fitness);
  } else {
    assert(false && "Unsupported Joy type");
    joy = std::unique_ptr<const Joy>();
  }
  if (joy_config.count("mod")) {
    std::unique_ptr<const Modulator> mod =
        ReadModulator(joy_config.get_child("mod"), max_shocks, max_fitness);
    joy = std::make_unique<joy::ModDecorator>(std::move(joy), std::move(mod));
  }
  return joy;
}

std::unique_ptr<const Joy> ReadFractionalJoy(ptree joy_config) {
  float j = joy_config.get<float>("j");
  return std::make_unique<joy::Fractional>(j);
}

std::unique_ptr<const Joy> ReadHealthDependentJoy(ptree joy_config,
                                                  int max_shocks) {
  double gamma_health = joy_config.get<float>("gamma_health");
  double gamma_consumption = joy_config.get<float>("gamma_consumption");
  float fitness_r = joy_config.get<float>("fitness_r");
  return std::make_unique<joy::HealthDependent>(gamma_health, gamma_consumption,
                                                max_shocks, fitness_r);
}

std::unique_ptr<const Joy> ReadHealthDependentJoySteve(ptree joy_config,
                                                  int max_shocks) {
  double gamma_health = joy_config.get<float>("gamma_health");
  double gamma_consumption = joy_config.get<float>("gamma_consumption");
  float fitness_r = joy_config.get<float>("fitness_r");
  float lambda = joy_config.get<float>("lambda");
  float mu = joy_config.get<float>("mu");
  return std::make_unique<joy::HealthDependentSteve>(gamma_health, gamma_consumption,
                                                max_shocks, fitness_r,lambda, mu);
}

std::unique_ptr<const Joy> ReadHealthDependentJoyDustin(ptree joy_config,
                                                  int max_shocks) {
  double gamma_health = joy_config.get<float>("gamma_health");
  double gamma_consumption = joy_config.get<float>("gamma_consumption");
  float fitness_r = joy_config.get<float>("fitness_r");
  float lambda = joy_config.get<float>("lambda");
  float mu = joy_config.get<float>("mu");
  return std::make_unique<joy::HealthDependentDustin>(gamma_health, gamma_consumption,
                                                max_shocks, fitness_r,lambda, mu);
}

std::unique_ptr<const Joy> ReadHealthDependentJoyFan(ptree joy_config,
                                                  int max_shocks, int max_fitness) {
  double gamma_health = joy_config.get<float>("gamma_health");
  double gamma_consumption = joy_config.get<float>("gamma_consumption");
  float p = joy_config.get<float>("p");
  float k = joy_config.get<float>("k");
  float c = joy_config.get<float>("c");
  return std::make_unique<joy::HealthDependentFan>(gamma_health, gamma_consumption,
						   p, k, c,
                                                   max_shocks, max_fitness);
}

}  // namespace configuration
}  // namespace healthcare
