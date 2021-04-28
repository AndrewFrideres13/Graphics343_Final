#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float piT = 3.1415926535897932385f;

inline float degrees_to_radians(float degrees) {
	return degrees * piT / 180.0f;
}

inline float random_float() {
	return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
	return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max) {
	if (x < min) { return min; }
	if (x > max) { return max; }
	return x;
}

#include "ray.h"
#include "vec3T.h"