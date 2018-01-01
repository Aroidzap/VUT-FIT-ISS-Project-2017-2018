#pragma once
#include <vector>

std::vector<float> BiasedAutoCorrelation(std::vector<float> x, int min_shift, int max_shift);
std::vector<std::vector<float>> JointProbabilityDensity(std::vector<float> x1, std::vector<float> x2, int x2_shift);