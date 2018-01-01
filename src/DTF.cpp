#include "DTF.h"
#include <math.h>

DTF::DTF(double b0, double b1, double b2, double a1, double a2) : b0(b0), b1(b1), b2(b2), a1(a1), a2(a2)
{
	ComputeZeroesPoles();
}

void DTF::ComputeZeroesPoles()
{
	complex Dn_sqrt = complex_sqrt(b1 * b1 - 4 * b0 * b2);
	this->n0 = (-b1 + Dn_sqrt) / (2.0f * b0);
	this->n1 = (-b1 - Dn_sqrt) / (2.0f * b0);
	complex Dp_sqrt = complex_sqrt(a1 * a1 - 4 * a2);
	this->p0 = (-a1 + Dp_sqrt) / 2.0f;
	this->p1 = (-a1 - Dp_sqrt) / 2.0f;
}

complex DTF::operator()(complex e_to_jomega)
{
	double modulus = b0 * (e_to_jomega - n0).modulus() * (e_to_jomega - n1).modulus();
	modulus = modulus / ((e_to_jomega - p0).modulus() * (e_to_jomega - p1).modulus());
	double arg = (e_to_jomega - n0).arg() + (e_to_jomega - n1).arg() - (e_to_jomega - p0).arg() - (e_to_jomega - p1).arg();
	return complex(modulus * cos(arg), modulus * sin(arg));
}

void DTF::GetZeroesPoles(complex & n0, complex & n1, complex & p0, complex & p1)
{
	n0 = this->n0;
	n1 = this->n1;
	p0 = this->p0;
	p1 = this->p1;
}