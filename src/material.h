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

public:
	color albedo;
};

class metal : public material {
public:
	metal(const color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const override;

public:
	color albedo;
	float fuzz;
};

class dielectric : public material {
public:
	dielectric(float index_of_refraction) : ir(index_of_refraction) {}

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const override;

public:
	float ir;

private:
	static float reflectance(float cosine, float ref_idx) {
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = pow(r0, 2.0f);
		return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
	}
};