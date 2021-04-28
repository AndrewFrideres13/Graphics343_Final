#pragma once

#include "material.h"

bool lambertian::scatter(
	const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
	auto scatter_direction = rec.normal + random_unit_vector();

	if (scatter_direction.near_zero()) {
		scatter_direction = rec.normal;
	}

	scattered = ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}

bool metal::scatter(
	const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
	vec3T reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}

bool dielectric::scatter(
	const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
	attenuation = color(1.0f, 1.0f, 1.0f);
	float refraction_ratio = rec.front_face ? (1.0f / ir) : ir;

	vec3T unit_direction = unit_vector(r_in.direction());
	float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
	float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
	vec3T direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float()) {
		direction = reflect(unit_direction, rec.normal);
	}
	else 
	{
		direction = refract(unit_direction, rec.normal, refraction_ratio);
	}

	scattered = ray(rec.p, direction);
	return true;
}