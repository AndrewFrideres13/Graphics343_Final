#pragma once

#include "rtweekend.h"
#include "hittable.h"

struct hit_record;

class material {
public:
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const = 0;
};

class lambertian : public material {
public:
	lambertian(const color& a) : albedo(a) {}

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const override;

	//virtual bool scatter(
	//	const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	//) const override {
	//	auto scatter_direction = rec.normal + random_unit_vector();

	//	if (scatter_direction.near_zero()) {
	//		scatter_direction = rec.normal;
	//	}

	//	scattered = ray(rec.p, scatter_direction);
	//	attenuation = albedo;
	//	return true;
	//}

public:
	color albedo;
};

class metal : public material {
public:
	metal(const color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const override;

	//virtual bool scatter(
	//	const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	//) const override {
	//	vec3T reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	//	scattered = ray(rec.p, reflected);
	//	attenuation = albedo;
	//	return (dot(scattered.direction(), rec.normal) > 0);
	//}

public:
	color albedo;
	float fuzz;
};