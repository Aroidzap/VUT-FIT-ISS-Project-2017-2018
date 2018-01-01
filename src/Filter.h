#pragma once
#include <vector>

class Filter {
private:
	std::vector<double> b_coef, a_coef;
public:
	Filter(std::vector<double> b0_to_n);
	Filter(std::vector<double> b0_to_n, std::vector<double> a1_to_n);
	std::vector<double> Convolve(std::vector<double> signal);
};