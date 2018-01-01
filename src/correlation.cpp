#include "Correlation.h"

std::vector<float> BiasedAutoCorrelation(std::vector<float> x, int min_shift, int max_shift)
{
	std::vector<float> R;

	//check and swap values if necessary
	if (min_shift > max_shift) {
		auto tmp = min_shift;
		min_shift = max_shift;
		max_shift = tmp;
	}

	R.resize(max_shift - min_shift + 1);
	int N = static_cast<int>(x.size());

	for (int k = min_shift; k <= max_shift; k++) {
		int abs_k = k < 0 ? -k : k;
		float sum = 0.0f;
		for (int n = 0; n < N - abs_k; n++) {
			sum += x[n] * x[n + abs_k];
		}
		R[k - min_shift] = sum / static_cast<float>(N);
	}
	return R;
}

std::vector<std::vector<float>> JointProbabilityDensity(std::vector<float> x1, std::vector<float> x2, int x2_shift)
{
	return std::vector<std::vector<float>>();
}
