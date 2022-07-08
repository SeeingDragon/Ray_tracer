//#ifndef起到的效果是防止一个源文件两次包含同一个头文件，而不是防止两个源文件包含同一个头文件。
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>


using std::sqrt;

class vec3 {
	public:
		//构造函数
		vec3() :e{ 0,0,0 } {};
		vec3(double e0, double e1, double e2) :e{ e0,e1,e2 } {};
		//返回值
		double x() const { return e[0]; }
		double y()const { return e[1]; }
		double z() const { return e[2]; }

		//operator重定向操作符
		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		vec3& operator+=(const vec3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		vec3& operator*=(const double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}
		
		vec3& operator/=(const double t)
		{
			return *this *= 1 / t;
		}
		//获取向量模长
		double length() const {
			return sqrt(length_squared());
		}

		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		//获取随机向量
		inline static vec3 random() {
			return vec3(random_double(), random_double(), random_double());
		}
		inline static vec3 random(double min, double max) {
			return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
		}



		//定义
	public :
		double e[3];

	

};
using point3 = vec3;
using color = vec3;

//vec Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
	return (1 / t) * v;
}
//点乘
inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}
//差乘
inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//单位向量
inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		//在一个立方体随机取点
		auto p = vec3::random(-1, 1);
		//如果圆心到p的模长平方大于等于1，则超出单位圆的范围，因此该p点不要
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

//另一种散射模型
//对随机点进行归一化
vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

vec3 random_in_heimsphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0)
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}


#endif