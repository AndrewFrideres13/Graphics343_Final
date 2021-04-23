#include "Tracer.h"

struct hit_record {
	vec3 p;
	vec3 normal;
	double t;
};

class hittable {
public:
	virtual float hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
