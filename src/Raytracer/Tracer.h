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

	bool hit_sphere(const vec3& center, double radius, const Ray& r) {
		vec3 oc = r.origin() - center;
		auto a = pow(r.direction().length(), 2);
		auto half_b = dot(oc, r.direction());
		auto c = pow(oc.length(), 2) - pow(radius, 2);
		auto discriminant = pow(half_b, 2) - a * c;

		if (discriminant < 0) {
			return -1.0;
		} else {
			return (-half_b - sqrt(discriminant)) / (a);
		}
	}

	vec3 ray_color(const Ray& r) {
		auto t = hit_sphere(vec3(0, 0, -1), 0.5, r);
		if (t > 0.0) {
			vec3 N = normalize(r.at(t) - vec3(0, 0, -1));
			return 0.5 * vec3(N.x + 1, N.y + 1, N.z + 1);
		}

		vec3 unit_direction = normalize(r.direction());
		t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
	}

public:
	vec3 point;
	vec3 dir;
};
