#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"



color ray_color(const ray& r)
{
	//��ȡ��λ����
	//r=origin+t*direction
	//direction����y���ȡֵ��Χ�ǣ�-1��1��
	vec3 unit_direction = unit_vector(r.direction());
	std::cout << unit_direction << std::endl;
	//Ҫ��t��0��1�仯��unit_direction��ŷ�Χ��-0.7-0.7
	auto t = 0.5 * (unit_direction.y()+ 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main()
{
	//image
	//aspect_ratio=width/height
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/aspect_ratio);

	//Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;//camera��image��z�����

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	//���½�,(0,0,0)���������ģ���Ϊ��������(0,0,0)ָ�����½�
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	//���ϵ��£������ҽ������
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i <image_width; ++i)
		{
			//��u��v���Ƶ���0��1��
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);

			//�������
			//lower_left_corner�Ǵ�ԭ��ָ�����½ǵ�����
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			//������vec3.h����ɫ����
			color pixel_color=ray_color(r);
			//write_color(std::cout, pixel_color);
		}
	}
	
	std::cerr << "\nDone.\n";
}

