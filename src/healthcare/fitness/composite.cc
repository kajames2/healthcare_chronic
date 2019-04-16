#include "healthcare/fitness/composite.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace healthcare {
namespace fitness {

Composite::Composite(int max_fitness, int max_budget,
                     std::vector<std::shared_ptr<const Fitness>> fits)
    : max_fitness_(max_fitness), fits_(fits) {
  for (int s_fit = 0; s_fit <= max_fitness; ++s_fit) {
    std::vector<int> costs(max_fitness + 1, 10000);
    for (int i = 0; i <= max_budget; ++i) {
      int end_fit = GetFitness(s_fit, i);
      if (i < costs[end_fit]) {
        costs[end_fit] = i;
      }
    }
    costs_.push_back(costs);
  }
}

double Composite::GetDecimalFitness(double fitness,
                                    int fitness_investment) const {
  for (const auto &func : fits_) {
    fitness = func->GetDecimalFitness(fitness, fitness_investment);
  }
  return std::clamp(fitness, 0.0, static_cast<double>(max_fitness_));
}

int Composite::GetFitnessCost(int fitness, int end_fitness) const {
  return costs_[fitness][end_fitness];
}

}  // namespace fitness
}  // namespace healthcare
