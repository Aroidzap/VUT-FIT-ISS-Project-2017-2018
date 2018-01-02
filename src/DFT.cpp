#include "DFT.h"
#include "constants.h"

std::vector<complex> DFT(const std::vector<double> x)
{
	std::vector<complex> X;
	unsigned int N = static_cast<unsigned int>(x.size());
	unsigned int K = N / 2;
	for (unsigned int k = 0; k < K; k++) {
		complex sum(0, 0);
		for (unsigned int n = 0; n < N; n++) {
			sum = sum + x[n] * e_to_j(-2.0*PI*static_cast<double>(k*n)/static_cast<double>(N));
		}
		X.push_back(sum);
	}
	return X;
}
