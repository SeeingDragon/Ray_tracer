#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
	public :
		camera(point3 lf,point3 la,vec3 vp,double vfov,double aspect_tatio,double aperture,double focud_dist){
			//��������õ�
			point3 lookfrom=lf;
			//�����Ҫָ��ĵ�
			point3 lookat=la;
			//������������򣬼���Ƭ�����Ƿ�ת
			vec3 vup=vp;

			//ԭ�㵽camera��z�����
			//auto focal_length = 1.0;
			//����ֱ����Ұ�Ƕ�תΪ����
			auto theta = degrees_to_radians(vfov);
			//������������ȺͿ��
			auto h = tan(theta / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = viewport_height * aspect_tatio;

			//������������ϵ�ĵ�λ����
			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);
			//������������泤�ȣ���ȳ�������ϵ�ĵ�λ����
			origin = lookfrom;
			//horizontal = vec3(viewport_width, 0.0, 0.0);
			//���Խ��࣬����Խ�󣬳���Խ��
			horizontal = focud_dist*viewport_width * u;
				//vertical = vec3(0.0, viewport_height, 0.0);
			vertical = focud_dist*viewport_height * v;
			//���½�,(0,0,0)���������ģ���Ϊ��������(0,0,0)ָ�����½�
			//lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - focud_dist*w;

			//������ߵ�͸��Բ�̰뾶
			lens_radius = aperture / 2;
		}
		ray get_ray(double s, double t)const {
			
			//���㷢����ߵĵ��ƫ����
			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();


			return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin-offset);
		}

	private:
		point3 origin;
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		double lens_radius;
};


#endif