#pragma once

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

complex e_to_j(float re);