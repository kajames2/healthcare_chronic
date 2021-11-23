#include "healthcare/fitness_func.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "exprtk.hpp"

namespace healthcare {

FitnessFunc::FitnessFunc(const std::string& func_str,
                         std::unordered_map<std::string, double> fitness_consts,
                         unsigned int max_age, unsigned int max_shocks,
                         unsigned int max_fitness)
    : max_age_(max_age),
      max_shocks_(max_shocks),
      max_fitness_(max_fitness),
      fitness_consts_(fitness_consts) {
  expression_str_ = func_str;
  exprtk::symbol_table<double> symbol_table;
  for (const auto& [key, value] : fitness_consts_) {
    symbol_table.add_constant(key, value);
  }
  symbol_table.add_constant("max_age", max_age_);
  symbol_table.add_constant("max_shocks", max_shocks_);
  symbol_table.add_constant("max_fitness", max_fitness_);
  symbol_table.add_constants();

  symbol_table.add_variable("age", age_);
  symbol_table.add_variable("shocks", shocks_);
  symbol_table.add_variable("fitness", fitness_);
  symbol_table.add_variable("x", x_);
  expression_.register_symbol_table(symbol_table);
  if (!parser_.compile(expression_str_, expression_)) {
    printf("Error: %s\tExpression: %s\n", parser_.error().c_str(),
           expression_str_.c_str());
    for (std::size_t i = 0; i < parser_.error_count(); ++i) {
      exprtk::parser_error::type error = parser_.get_error(i);
      printf(
          "Error: %02d Position: %02d "
          "Type: [%s] "
          "Message: %s "
          "Expression: %s\n",
          static_cast<int>(i), static_cast<int>(error.token.position),
          exprtk::parser_error::to_str(error.mode).c_str(),
          error.diagnostic.c_str(), expression_str_.c_str());
    }
    exit(1);
  }
}

unsigned int FitnessFunc::operator()(unsigned int age, unsigned int shocks,
                                     unsigned int fitness,
                                     unsigned int investment) const {
  age_ = static_cast<double>(age);
  shocks_ = static_cast<double>(shocks);
  fitness_ = static_cast<double>(fitness);
  x_ = static_cast<double>(investment);
  return static_cast<unsigned int>(
      std::clamp(static_cast<int>(expression_.value()), 0,
                 static_cast<int>(max_fitness_)));
}

}  // namespace healthcare
