#include "DFT.h"

#define M_PI 3.14159265358979323846f

std::vector<complex> DFT(std::vector<float> x)
{
	std::vector<complex> X;
	unsigned int N = static_cast<unsigned int>(x.size());
	unsigned int K = N / 2;
	for (unsigned int k = 0; k < K; k++) {
		complex sum(0, 0);
		for (unsigned int n = 0; n < N; n++) {
			sum = sum + x[n] * e_to_j(-2.0f*M_PI*static_cast<float>(k*n)/static_cast<float>(N));
		}
		X.push_back(sum);
	}
	return X;
}
