#pragma once
#include<vector>

class complex {
private:
	double re, im;
public:
	double modulus();
	double arg();
	complex();
	complex(double re);
	complex(double re, double im);

	friend complex operator+(const complex & a, const complex & b);
	friend complex operator-(const complex & a, const complex & b);
	friend complex operator*(const complex & a, const complex & b);
	friend complex operator/(const complex & a, const complex & b);
	
	friend complex operator+(const complex & a, const double & b);
	friend complex operator-(const complex & a, const double & b);
	friend complex operator*(const complex & a, const double & b);
	friend complex operator/(const complex & a, const double & b);

	friend complex operator+(const double & a, const complex & b);
	friend complex operator-(const double & a, const complex & b);
	friend complex operator*(const double & a, const complex & b);
	friend complex operator/(const double & a, const complex & b);

	friend double Re(complex c);
	friend double Im(complex c);
};

std::vector<double> Re(std::vector<complex> c);
std::vector<double> Im(std::vector<complex> c);

complex complex_sqrt(double re);
complex e_to_j(double re);
