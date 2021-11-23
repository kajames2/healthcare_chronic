#include "joy_reader.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "exprtk.hpp"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

//   std::string expression_str = func_str;
//   exprtk::symbol_table<double> symbol_table;
//   for (const auto& [key, value] : joy_consts) {
//     symbol_table.add_constant(key, value);
//   }
//   symbol_table.add_constant("max_age", max_age);
//   symbol_table.add_constant("max_shocks", max_shocks);
//   symbol_table.add_constant("max_fitness", max_fitness);
//   symbol_table.add_constants();

//   double age = 1;
//   double shocks = 0;
//   double fitness = 0;
//   double x = 0;
//   symbol_table.add_variable("age", age);
//   symbol_table.add_variable("shocks", shocks);
//   symbol_table.add_variable("fitness", fitness);
//   symbol_table.add_variable("x", x);

//   exprtk::expression<double> expression;
//   expression.register_symbol_table(symbol_table);
//   exprtk::parser<double> parser;
//   if (!parser.compile(expression_str, expression)) {
//     printf("Error: %s\tExpression: %s\n", parser.error().c_str(),
//            expression_str.c_str());
//     for (std::size_t i = 0; i < parser.error_count(); ++i) {
//       exprtk::parser_error::type error = parser.get_error(i);
//       printf(
//           "Error: %02d Position: %02d "
//           "Type: [%s] "
//           "Message: %s "
//           "Expression: %s\n",
//           static_cast<int>(i), static_cast<int>(error.token.position),
//           exprtk::parser_error::to_str(error.mode).c_str(),
//           error.diagnostic.c_str(), expression_str.c_str());
//     }
//     exit(1);
//   }
//   return [expression, &age, &shocks, &fitness, &x](
//              unsigned int age_in, unsigned int shocks_in,
//              unsigned int fitness_in, unsigned int investment_in) {
//     age = static_cast<double>(age_in);
//     shocks = static_cast<double>(shocks_in);
//     std::cout << fitness_in << "," << static_cast<double>(fitness_in) << ","
//               << fitness << std::endl;
//     fitness = static_cast<double>(fitness_in);
//     std::cout << fitness_in << "," << static_cast<double>(fitness_in) << ","
//               << fitness << std::endl;
//     x = static_cast<double>(investment_in);
//     std::cout << age << "," << shocks << "," << fitness << "," << x << ","
//               << expression.value() << std::endl;
//     return expression.value();
//   };
// }

std::unique_ptr<JoyFunc> ReadJoy(ptree joy_config, unsigned int max_age,
                                 unsigned int max_shocks,
                                 unsigned int max_fitness) {
  std::string func_str = joy_config.get<std::string>("function");
  std::unordered_map<std::string, double> const_map;
  for (auto it : joy_config) {
    boost::optional<float> f = it.second.get_value_optional<float>();
    if (f) {
      const_map[it.first] = f.value();
    }
  }
  return std::make_unique<JoyFunc>(func_str, const_map, max_age, max_shocks,
                                   max_fitness);
}

}  // namespace configuration
}  // namespace healthcare
