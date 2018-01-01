#pragma once
#include <vector>
#include "complex.h"

// Discrete Fourier Transform
// DFT is computed just to half size of vector x
std::vector<complex> DFT(std::vector<double> x);
