#pragma once
#include <vector>
#include "complex.h"

// DFT is computed just to half size of vector x
std::vector<complex> DFT(std::vector<float> x);