#pragma once

#include "vec3T.h"

class ray 
{
public:
	ray() {}
	ray(const point3& origin, const vec3T& direction)
		: orig(origin), dir(direction)
	{}

	point3 origin() const { return orig; }
	vec3T direction() const { return dir; }
	float time() const { return tm; }

	point3 at(float t) const {
		return orig + (t * dir);
	}

public:
	point3 orig;
	vec3T dir;
	float tm;
};