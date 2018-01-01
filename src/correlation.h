#pragma once
#include <vector>

std::vector<double> BiasedAutoCorrelation(std::vector<double> x, int k_min, int k_max);
std::vector<std::vector<double>> JointProbabilityDensity(std::vector<double> x1, std::vector<double> x2, int k, double div_size);