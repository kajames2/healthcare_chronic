#ifndef HEALTHCARE_CONFIGURATION_READER_H_
#define HEALTHCARE_CONFIGURATION_READER_H_

#include <string>

#include "healthcare/configuration.h"

namespace healthcare {

Configuration ReadConfigurationFile(std::string filename);

}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_READER_H_
