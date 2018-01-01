#pragma once
#include <vector>

std::vector<float> BiasedAutoCorrelation(std::vector<float> x, int k_min, int k_max);
std::vector<std::vector<float>> JointProbabilityDensity(std::vector<float> x1, std::vector<float> x2, int k, float div_size);