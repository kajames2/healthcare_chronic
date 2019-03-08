#ifndef HEALTHCARE_CONFIGURATION_READER_H_
#define HEALTHCARE_CONFIGURATION_READER_H_

#include <string>

#include "healthcare/configuration.h"

namespace healthcare {
namespace configuration {

Configuration ReadConfigurationFile(std::string filename);

}  // namespace configuration
}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_READER_H_
