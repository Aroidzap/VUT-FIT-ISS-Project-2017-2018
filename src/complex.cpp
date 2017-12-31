#include "complex.h"
#include <math.h>

complex::complex() : re(), im() {}
complex::complex(float re) : re(re), im(0.0f) {}
complex::complex(float re, float im) : re(re), im(im) {}

float complex::modulus()
{
	return sqrtf(re * re + im * im);
}

float complex::arg()
{
	return atan2f(im, re);
}


complex operator+(const complex & a, const complex & b)
{
	return complex(a.re + b.re, a.im + b.im);
}

complex operator-(const complex & a, const complex & b)
{
	return complex(a.re - b.re, a.im - b.im);
}

complex operator*(const complex & a, const complex & b)
{
	return complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

complex operator/(const complex & a, const complex & b)
{
	float r = a.re * b.re + a.im * b.im;
	float i = a.im * b.re - a.re * b.im;
	float d = b.re * b.re + b.im * b.im;
	return complex(r / d, i / d);
}

complex operator+(const complex & a, const float & b)
{
	return complex(a.re + b, a.im);
}

complex operator-(const complex & a, const float & b)
{
	return complex(a.re - b, a.im);
}

complex operator*(const complex & a, const float & b)
{
	return complex(a.re * b, a.im * b);
}

complex operator/(const complex & a, const float & b)
{
	return complex(a.re / b, a.im / b);
}

complex operator+(const float & a, const complex & b)
{
	return complex(a + b.re, b.im);
}

complex operator-(const float & a, const complex & b)
{
	return complex(a - b.re, - b.im);
}

complex operator*(const float & a, const complex & b)
{
	return complex(a * b.re, a * b.im);
}

complex operator/(const float & a, const complex & b)
{
	float d = b.re * b.re + b.im * b.im;
	return complex(a * b.re / d, a * b.im / d);
}

complex e_to_j(float re)
{
	return complex(cosf(re), sinf(re));
}

float Re(complex c) 
{
	return c.re;
}

float Im(complex c)
{
	return c.im;
}