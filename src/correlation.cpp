#include "correlation.h"

std::vector<double> BiasedAutoCorrelation(std::vector<double> x, int k_min, int k_max)
{
	std::vector<double> R;

	//check and swap values if necessary
	if (k_min > k_max) {
		auto tmp = k_min;
		k_min = k_max;
		k_max = tmp;
	}

	R.resize(k_max - k_min + 1);
	int N = static_cast<int>(x.size());

	for (int k = k_min; k <= k_max; k++) {
		int abs_k = k < 0 ? -k : k;
		double sum = 0.0f;
		for (int n = 0; n < N - abs_k; n++) {
			sum += x[n] * x[n + abs_k];
		}
		R[k - k_min] = sum / static_cast<double>(N);
	}
	return R;
}

std::vector<std::vector<double>> JointProbabilityDensity(std::vector<double> x1, std::vector<double> x2, int k, double div_size)
{
	std::vector<std::vector<double>> joint_prob_density;
	
	size_t min_size = x1.size() < x2.size() ? x1.size() : x2.size();
	if (k > min_size) { return joint_prob_density; }
	size_t N = k < 0 ? min_size + k : min_size - k;

	for (double x2i = -1.0; x2i < 1.0f; x2i += div_size) {
		std::vector<double> prob_density;
		for (double x1i = -1.0; x1i < 1.0f; x1i += div_size) {
			double probability = 0.0f;
			for (size_t n = 0; n < N; n++) {
				double x1v, x2v;
				if (k >= 0) {
					x1v = x1[n];
					x2v = x2[n + k];
				}
				else {
					x1v = x1[n + k];
					x2v = x2[n];
				}
				if ((x1v >= x1i) && (x1v < x1i + div_size) &&
					(x2v >= x2i) && (x2v < x2i + div_size)) {
					probability += 1.0f;
				}
			}
			probability /= static_cast<double>(N);
			prob_density.push_back(probability / (div_size*div_size));
		}
		joint_prob_density.push_back(prob_density);
	}
	return joint_prob_density;
}