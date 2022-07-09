#ifndef HITTABLE_H
#define HITTABLE_H


#include "rtweekend.h"


class material;

struct hit_record {
	point3 p;//交点
	vec3 normal;//法线
	shared_ptr<material> mat_ptr;//材质指针
	double t;
	bool front_face;//让法线方向始终与光线相反
	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		//让光照方向和法线方向始终保持相反
		//如果光照方向和向外法线方向点乘结果小于0，则说明方向相反
		front_face = dot(r.direction(), outward_normal)<0;
		//如果front_face不为0说明光照方向和法线方向相反，结果不用发生改变。
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
	public :
		//碰撞函数
		//等于0代表是纯虚函数
		virtual bool hit(const ray& r, double t_min,double t_max, hit_record& rec) const = 0;
};





#endif // !HITTABLE_H

