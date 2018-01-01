#include "complex.h"
#include <math.h>

complex::complex() : re(), im() {}
complex::complex(double re) : re(re), im(0.0) {}
complex::complex(double re, double im) : re(re), im(im) {}

double complex::modulus()
{
	return sqrt(re * re + im * im);
}

double complex::arg()
{
	return atan2(im, re);
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
	double r = a.re * b.re + a.im * b.im;
	double i = a.im * b.re - a.re * b.im;
	double d = b.re * b.re + b.im * b.im;
	return complex(r / d, i / d);
}

complex operator+(const complex & a, const double & b)
{
	return complex(a.re + b, a.im);
}

complex operator-(const complex & a, const double & b)
{
	return complex(a.re - b, a.im);
}

complex operator*(const complex & a, const double & b)
{
	return complex(a.re * b, a.im * b);
}

complex operator/(const complex & a, const double & b)
{
	return complex(a.re / b, a.im / b);
}

complex operator+(const double & a, const complex & b)
{
	return complex(a + b.re, b.im);
}

complex operator-(const double & a, const complex & b)
{
	return complex(a - b.re, - b.im);
}

complex operator*(const double & a, const complex & b)
{
	return complex(a * b.re, a * b.im);
}

complex operator/(const double & a, const complex & b)
{
	double d = b.re * b.re + b.im * b.im;
	return complex(a * b.re / d, a * b.im / d);
}

complex complex_sqrt(double re)
{
	if (re >= 0) {
		return complex(sqrt(re), 0);
	}
	else {
		return complex(0, sqrt(-re));
	}
}

complex e_to_j(double re)
{
	return complex(cos(re), sin(re));
}

double Re(const complex c) 
{
	return c.re;
}

double Im(const complex c)
{
	return c.im;
}

std::vector<double> Re(const std::vector<complex> c)
{
	std::vector<double> re;
	for (auto & it : c) {
		re.push_back(Re(it));
	}
	return re;
}

std::vector<double> Im(const std::vector<complex> c)
{
	std::vector<double> im;
	for (auto & it : c) {
		im.push_back(Im(it));
	}
	return im;
}
