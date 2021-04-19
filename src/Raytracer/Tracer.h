#pragma once

#include "ofMain.h"
using namespace glm;

class Ray {
public:
	Ray() {}
	//Used to init the point & direction passed in
	Ray(const vec3& point, const vec3& direction) : point(point), dir(direction) {}

	vec3 origin() const { return point; }
	vec3 direction() const { return dir; }

	vec3 at(double t) const {
		return point + t * dir;
	}

	vec3 ray_color(const Ray& r) {
		vec3 unit_direction = normalize(r.direction());
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
	}

public:
	vec3 point;
	vec3 dir;
};
