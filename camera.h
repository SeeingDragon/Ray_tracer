#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
	public :
		camera(point3 lf,point3 la,vec3 vp,double vfov,double aspect_tatio){
			//��������õ�
			point3 lookfrom=lf;
			//�����Ҫָ��ĵ�
			point3 lookat=la;
			//������������򣬼���Ƭ�����Ƿ�ת
			vec3 vup=vp;

			//ԭ�㵽camera��z�����
			auto focal_length = 1.0;
			//����ֱ����Ұ�Ƕ�תΪ����
			auto theta = degrees_to_radians(vfov);
			//������������ȺͿ��
			auto h = tan(theta / 2)*focal_length;
			auto viewport_height = 2.0 * h;
			auto viewport_width = viewport_height * aspect_tatio;

			//������������ϵ�ĵ�λ����
			auto w = unit_vector(lookfrom - lookat);
			auto u = unit_vector(cross(vup, w));
			auto v = cross(w, u);
			//������������泤�ȣ���ȳ�������ϵ�ĵ�λ����
			origin = lookfrom;
			//horizontal = vec3(viewport_width, 0.0, 0.0);
			horizontal = viewport_width * u;
				//vertical = vec3(0.0, viewport_height, 0.0);
			vertical = viewport_height * v;
			//���½�,(0,0,0)���������ģ���Ϊ��������(0,0,0)ָ�����½�
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