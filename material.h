#ifndef MATERIAL_H
#define MATHRIAL_H

#include "rtweekend.h"

struct hit_record;

class material {
	public:
		virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
	public:
		lambertian(const color& a) :albedo(a) {}

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			//计算散射方向
			auto scatter_direction = rec.normal + random_unit_vector();
			//如果散射方向接近0，即该随机方向和法线方向相反，此时返回法线方向
			if (scatter_direction.near_zero())
				scatter_direction = rec.normal;

			scattered = ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}

	public:
		color albedo;
};

class metal : public material {
	public:
		metal(const color& a,double f):albedo(a),fuzz(f<1?f:1){}

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)const override {
			//计算反射方向
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
			attenuation = albedo;
			//反射方向和法线方向点乘结果不得小于等于0
			return (dot(scattered.direction(), rec.normal) > 0);
		}
		
	public:
		color albedo;//原本颜色
		double fuzz;//模糊参数
};

#endif
