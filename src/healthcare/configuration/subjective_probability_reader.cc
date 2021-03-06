#include "subjective_probability_reader.h"

#include <cassert>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <iostream>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "exprtk.hpp"

namespace healthcare {
namespace configuration {

using ::boost::property_tree::ptree;

std::function<float(int, int, int, float)> MakeSubjProbFunc(
    std::string func_str, std::unordered_map<std::string, double> prob_consts,
    int max_age, int max_shocks, int max_fitness) {
  std::string expression_str = func_str;
  exprtk::symbol_table<double> symbol_table;
  for (const auto& [key, value] : prob_consts) {
    symbol_table.add_constant(key, value);
  }
  symbol_table.add_constant("max_age", max_age);
  symbol_table.add_constant("max_shocks", max_shocks);
  symbol_table.add_constant("max_fitness", max_fitness);
  symbol_table.add_constants();

  double age = 1;
  double shocks = 0;
  double fitness = 0;
  double prob = 0;
  symbol_table.add_variable("age", age);
  symbol_table.add_variable("shocks", shocks);
  symbol_table.add_variable("fitness", fitness);
  symbol_table.add_variable("prob", prob);

  exprtk::expression<double> expression;
  expression.register_symbol_table(symbol_table);
  exprtk::parser<double> parser;
  if (!parser.compile(expression_str, expression)) {
    printf("Error: %s\tExpression: %s\n", parser.error().c_str(),
           expression_str.c_str());
    for (std::size_t i = 0; i < parser.error_count(); ++i) {
      exprtk::parser_error::type error = parser.get_error(i);
      printf(
          "Error: %02d Position: %02d "
          "Type: [%s] "
          "Message: %s "
          "Expression: %s\n",
          static_cast<int>(i), static_cast<int>(error.token.position),
          exprtk::parser_error::to_str(error.mode).c_str(),
          error.diagnostic.c_str(), expression_str.c_str());
    }
    exit(1);
  }
  return [expression, &age, &shocks, &fitness, &prob](
             int age_in, int shocks_in, int fitness_in, float prob_in) {
    age = static_cast<double>(age_in);
    shocks = static_cast<double>(shocks_in);
    fitness = static_cast<double>(fitness_in);
    prob = static_cast<double>(prob_in);
    return expression.value();
  };
}

std::function<float(int, int, int, float)> ReadSubjectiveProbability(ptree prob_config,
                                                      int max_age,
                                                      int max_shocks,
                                                      int max_fitness) {
  std::string func_str = prob_config.get<std::string>("function");
  std::unordered_map<std::string, double> const_map;
  for (auto it : prob_config) {
    boost::optional<float> f = it.second.get_value_optional<float>();
    if (f) {
      const_map[it.first] = f.value();
    }
  }
  auto func =  MakeSubjProbFunc(func_str, const_map, max_age, max_shocks, max_fitness);
  return func;
}

}  // namespace configuration
}  // namespace healthcare
