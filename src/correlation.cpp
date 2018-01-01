#include "correlation.h"

std::vector<float> BiasedAutoCorrelation(std::vector<float> x, int k_min, int k_max)
{
	std::vector<float> R;

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
		float sum = 0.0f;
		for (int n = 0; n < N - abs_k; n++) {
			sum += x[n] * x[n + abs_k];
		}
		R[k - k_min] = sum / static_cast<float>(N);
	}
	return R;
}

std::vector<std::vector<float>> JointProbabilityDensity(std::vector<float> x1, std::vector<float> x2, int k, float div_size)
{
	std::vector<std::vector<float>> joint_prob_density;
	
	size_t min_size = x1.size() < x2.size() ? x1.size() : x2.size();
	if (k > min_size) { return joint_prob_density; }
	size_t N = k < 0 ? min_size + k : min_size - k;

	for (float x2i = -1.0; x2i < 1.0f; x2i += div_size) {
		std::vector<float> prob_density;
		for (float x1i = -1.0; x1i < 1.0f; x1i += div_size) {
			float probability = 0.0f;
			for (size_t n = 0; n < N; n++) {
				float x1v, x2v;
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
			probability /= static_cast<float>(N);
			prob_density.push_back(probability / (div_size*div_size));
		}
		joint_prob_density.push_back(prob_density);
	}
	return joint_prob_density;
}