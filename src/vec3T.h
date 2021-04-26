#pragma once

#include <cmath>
#include <iostream>
#include <random>

using std::sqrt;
using std::fabs;

class vec3T
{
public:
	vec3T() : e() {}
	vec3T(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }

	vec3T operator-() const { return vec3T(-e[0], -e[1], -e[2]); }
	float operator[](int i) const { return e[i]; }
	float& operator[](int i) { return e[i]; }

	vec3T& operator+=(const vec3T& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3T& operator*=(const float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3T& operator/=(const float t) {
		return *this *= 1 / t;
	}

	float length() const {
		return sqrt(length_squared());
	}

	float length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	bool near_zero() const {
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	inline static float random_float_vec() {
		return rand() / (RAND_MAX + 1.0f);
	}

	inline static float random_float_vec(float min, float max) {
		return min + (max - min) * random_float_vec();
	}

	inline static vec3T random() {
		return vec3T(random_float_vec(), random_float_vec(), random_float_vec());
	}

	inline static vec3T random(float min, float max) {
		return vec3T(random_float_vec(min, max), random_float_vec(min, max), random_float_vec(min, max));
	}

	float e[3];
};

using point3 = vec3T;
using color = vec3T;

inline std::ostream& operator<<(std::ostream& out, const vec3T& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3T operator+(const vec3T& u, const vec3T& v) {
	return vec3T(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3T operator-(const vec3T& u, const vec3T& v) {
	return vec3T(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3T operator*(const vec3T& u, const vec3T& v) {
	return vec3T(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3T operator*(float t, const vec3T& v) {
	return vec3T(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3T operator*(const vec3T& v, float t) {
	return t * v;
}

inline vec3T operator/(vec3T v, float t) {
	return (1 / t) * v;
}

inline float dot(const vec3T& u, const vec3T& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3T cross(const vec3T& u, const vec3T& v) {
	return vec3T(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3T unit_vector(vec3T v) {
	return v / v.length();
}

inline vec3T random_in_unit_sphere() {
	while (true) {
		auto p = vec3T::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline vec3T random_in_hemisphere(const vec3T& normal) {
	vec3T in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0f) {
		return in_unit_sphere;
	}
	else
	{
		return -in_unit_sphere;
	}
}

inline vec3T random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline vec3T reflect(const vec3T& v, const vec3T& n) {
	return v - 2 * dot(v, n) * n;
}