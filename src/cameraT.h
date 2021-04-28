#pragma once

#include "rtweekend.h"

class cameraT {
public:
	cameraT(
		point3 lookfrom,
		point3 lookat,
		vec3T vup,
		float vfov,
		float aspect_ratio,
		float aperture,
		float focus_dist
	) {
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0f * h;
		auto viewport_width = aspect_ratio * viewport_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		auto focal_length = 1.0f;

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

		lens_radius = aperture / 2;
	}

	ray get_ray(float s, float t) const {
		vec3T rd = lens_radius * random_in_unit_disk();
		vec3T offset = u * rd.x() + v * rd.y();

		return ray(
			origin + offset, 
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3T horizontal;
	vec3T vertical;
	vec3T u, v, w;
	float lens_radius;
};