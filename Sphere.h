#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere :public hittable {
	public :
		sphere(){}
		sphere(point3 cen, double r,shared_ptr<material> m) :center(cen), radius(r),mat_ptr(m) {}
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const ;
	public :
		//Բ�ĺͰ뾶
		point3 center;
		double radius;
		//����ָ��
		shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	//t(2) * b*b + 2tb*(A-C)+(A-C)*(A-C)-r*r; 
	//�򻯣��ѵ��תΪ������ģ������
	vec3 oc = r.origin() - center;
	double a = r.direction().length_squared();
	double half_b = dot(r.direction(), oc);
	double c = oc.length_squared() - radius * radius;
	//b*b-4ac ���㺯���Ƿ��н�,b=2*half_b
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;
	double sqrtb = sqrt(discriminant);

	//�ҵ��ɽ��ܷ�Χ�������
	double root = (-half_b - sqrtb) / a;
	if (root < t_min || root >t_max)
	{
		root = (-half_b + sqrtb) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	//���t
	rec.t = root;
	//��ý���p
	rec.p = r.at(rec.t);
	//��ȡ���߲��ҵ�λ��
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	
	return true;
}

#endif // !SPHERE_H

