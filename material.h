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

class dielectric :public material {
public:
	dielectric(double index_of_refraction) :ir(index_of_refraction) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		attenuation = color(1.0, 1.0, 1.0);
		//front_face为true则说明光线与法线方向相反
		double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
		//入射光线“方向”归一化
		vec3 unit_direction = unit_vector(r_in.direction());
		//计算折射方向
		//根据斯涅尔定律，如果sin(θ)>1则该定律无法求出解，因此全部反射
		//求解sin(θ)和cos(θ)值
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		bool cannot_refract = refraction_ratio * sin_theta > 1.0;

		vec3 direction;

		if (cannot_refract || reflectance(cos_theta,refraction_ratio)>random_double())
				direction = reflect(unit_direction, rec.normal);
			else
				direction = refract(unit_direction, rec.normal, refraction_ratio);

			scattered = ray(rec.p, direction);
			return true;
		}

	public:
		double ir;//折射率

	private:
		static double reflectance(double cosine,double ref_idx){
			//使用Christophe Schlick近似
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}
};


#endif
