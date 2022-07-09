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
			//����ɢ�䷽��
			auto scatter_direction = rec.normal + random_unit_vector();
			//���ɢ�䷽��ӽ�0�������������ͷ��߷����෴����ʱ���ط��߷���
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
			//���㷴�䷽��
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
			attenuation = albedo;
			//���䷽��ͷ��߷����˽������С�ڵ���0
			return (dot(scattered.direction(), rec.normal) > 0);
		}
		
	public:
		color albedo;//ԭ����ɫ
		double fuzz;//ģ������
};

#endif
