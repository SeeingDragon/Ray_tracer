#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
	public :
		camera(point3 lf,point3 la,vec3 vp,double vfov,double aspect_tatio){
			//摄像机放置点
			point3 lookfrom=lf;
			//摄像机要指向的点
			point3 lookat=la;
			//摄像机顶部方向，即照片正面是否翻转
			vec3 vup=vp;

			//原点到camera的z轴距离
			auto focal_length = 1.0;
			//将垂直是视野角度转为弧度
			auto theta = degrees_to_radians(vfov);
			//计算摄像机长度和宽度
			auto h = tan(theta / 2)*focal_length;
			auto viewport_height = 2.0 * h;
			auto viewport_width = viewport_height * aspect_tatio;

			//计算计算机坐标系的单位向量
			auto w = unit_vector(lookfrom - lookat);
			auto u = unit_vector(cross(vup, w));
			auto v = cross(w, u);
			//计算摄像机画面长度，宽度乘以坐标系的单位向量
			origin = lookfrom;
			//horizontal = vec3(viewport_width, 0.0, 0.0);
			horizontal = viewport_width * u;
				//vertical = vec3(0.0, viewport_height, 0.0);
			vertical = viewport_height * v;
			//左下角,(0,0,0)定义正中心，变为向量，从(0,0,0)指向左下角
			//lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
		}
		ray get_ray(double s, double t)const {
			return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
		}

	private:
		point3 origin;
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
};


#endif