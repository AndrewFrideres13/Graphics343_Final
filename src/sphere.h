#pragma once

#include "hittable.h"
#include "vec3T.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(point3 cen, float r, shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m) {
	};

	virtual bool hit(
		const ray& r, float t_min, float t_max, hit_record& rec) const override;

public:
	point3 center;
	float radius;
	shared_ptr<material> mat_ptr;
};

inline bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3T oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - pow(radius, 2);

	auto discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0) { return false; }
	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root) { return false; }
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3T outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;
}