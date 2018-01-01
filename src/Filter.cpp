#include "Filter.h"

Filter::Filter(std::vector<double> b0_to_n) : b_coef(b0_to_n), a_coef() {}
Filter::Filter(std::vector<double> b0_to_n, std::vector<double> a1_to_n) : b_coef(b0_to_n), a_coef(a1_to_n) {}

std::vector<double> Filter::Convolve(std::vector<double> signal)
{
	std::vector<double> output;
	output.resize(signal.size());
	int signal_size = static_cast<int>(signal.size());
	int b_coef_size = static_cast<int>(b_coef.size());
	int a_coef_size = static_cast<int>(a_coef.size());

	for (int i = 0; i < signal_size; i++) {
		double sum = 0.0;
		for (int n = b_coef_size - 1; n >= 0; n--) {
			int idx = i - n;
			if (idx >= 0) {
				sum += signal[idx] * b_coef[n];
			}
		}
		for (int n = a_coef_size; n > 0; n--) {
			int idx = i - n;
			if (idx >= 0) {
				sum += output[idx] * a_coef[n - 1];
			}
		}
		output[i] = sum;
	}
	return output;
}
