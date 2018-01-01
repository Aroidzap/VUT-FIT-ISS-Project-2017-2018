#pragma once
#include "complex.h"

// Discrete Transfer Function
class DTF {
private:
	float b0, b1, b2, a1, a2;
	complex n0, n1, p0, p1;
	void ComputeZeroesPoles();
public:
	DTF(float b0, float b1, float b2, float a1, float a2);
	void GetZeroesPoles(complex &n0, complex &n1, complex &p0, complex &p1);

	// H(e^jw)
	complex operator()(complex e_to_jomega); 
};