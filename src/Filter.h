#pragma once
#include <vector>

class Filter {
private:
	std::vector<float> b_coef, a_coef;
public:
	Filter(std::vector<float> b0_to_n);
	Filter(std::vector<float> b0_to_n, std::vector<float> a1_to_n);
	std::vector<float> Convolve(std::vector<float> signal);
};