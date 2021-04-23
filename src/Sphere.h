#include "Raytracer/hittable.h"
#include "Raytracer/Tracer.h"

class sphere : public hittable {
public:
	sphere() {}
	sphere(vec3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(
		const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	vec3 center;
	double radius;
};

bool sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	auto a = pow(r.direction().length(), 2);
	auto half_b = dot(oc, r.direction());
	auto c = pow(oc.length(), 2) - pow(radius, 2);

	auto discriminant = pow(half_b, 2) - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - center) / radius;

	return true;
}