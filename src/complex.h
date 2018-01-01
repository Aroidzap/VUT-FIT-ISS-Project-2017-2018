#pragma once
#include<vector>

class complex {
private:
	float re, im;
public:
	float modulus();
	float arg();
	complex();
	complex(float re);
	complex(float re, float im);

	friend complex operator+(const complex & a, const complex & b);
	friend complex operator-(const complex & a, const complex & b);
	friend complex operator*(const complex & a, const complex & b);
	friend complex operator/(const complex & a, const complex & b);
	
	friend complex operator+(const complex & a, const float & b);
	friend complex operator-(const complex & a, const float & b);
	friend complex operator*(const complex & a, const float & b);
	friend complex operator/(const complex & a, const float & b);

	friend complex operator+(const float & a, const complex & b);
	friend complex operator-(const float & a, const complex & b);
	friend complex operator*(const float & a, const complex & b);
	friend complex operator/(const float & a, const complex & b);

	friend float Re(complex c);
	friend float Im(complex c);
};

std::vector<float> Re(std::vector<complex> c);
std::vector<float> Im(std::vector<complex> c);

complex complex_sqrt(float re);
complex e_to_j(float re);