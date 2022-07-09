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
		//圆心和半径
		point3 center;
		double radius;
		//材质指针
		shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	//t(2) * b*b + 2tb*(A-C)+(A-C)*(A-C)-r*r; 
	//简化，把点乘转为向量的模长开方
	vec3 oc = r.origin() - center;
	double a = r.direction().length_squared();
	double half_b = dot(r.direction(), oc);
	double c = oc.length_squared() - radius * radius;
	//b*b-4ac 计算函数是否有解,b=2*half_b
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;
	double sqrtb = sqrt(discriminant);

	//找到可接受范围的最近根
	double root = (-half_b - sqrtb) / a;
	if (root < t_min || root >t_max)
	{
		root = (-half_b + sqrtb) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	//求解t
	rec.t = root;
	//获得交点p
	rec.p = r.at(rec.t);
	//求取法线并且单位化
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	
	return true;
}

#endif // !SPHERE_H

